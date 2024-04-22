/**
 * @file misc.cpp
 * @brief Contains useful tools that don't have a specific category.
 * @version 0.1
 * @date 2023-11-23
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "misc.h"
#include "logger.h"
#include <algorithm>
#include <cctype>
#include <fstream>

namespace misc
{
  /**
   * @brief Checks if a file has specific contents.
   *
   * @param text Text to search in.
   * @param contents Contents to search for.
   * @return true
   * @return false
   */
  bool has_contents(std::string text, std::string contents)
  {
    return (text.find(contents) != std::string::npos);
  }

  /**
   * @brief Creates sub-vector from a std::vector
   *
   * @param main_vector Initial vector.
   * @param begin_index Start index.
   * @param end_index End index.
   * @return std::vector<std::string>
   */
  std::vector<std::string> sub_vector(const std::vector<std::string> &main_vector,
                                      int begin_index, int end_index)
  {
    if (begin_index < 0 || end_index > static_cast<int>(main_vector.size()) ||
        begin_index > end_index)
    {
      logger::error("invalid indicies for misc::sub_vector");
      return {};
    }

    return std::vector<std::string>(main_vector.begin() + begin_index,
                                    main_vector.begin() + end_index);
  }

  /**
   * @brief Checks if a string exists in a std::vector.
   *
   * @param main_vector Initial vector.
   * @param content Search for.
   * @return true
   * @return false
   */
  bool find_in_vector(const std::vector<std::string> &main_vector,
                      std::string content)
  {
    return (std::find(main_vector.begin(), main_vector.end(), content) !=
            main_vector.end());
  }

  /**
   * @brief Removes whitespaces at the beginning and end of strings.
   *
   * @param str Content.
   */
  void trim(std::string &str)
  {
    std::size_t start = str.find_first_not_of(' ');
    if (start != std::string::npos)
      str = str.substr(start);

    std::size_t end = str.find_last_not_of(' ');
    if (end != std::string::npos)
      str = str.substr(0, end + 1);
  }

  /**
   * @brief Removes character(s) from string.
   *
   * @param str
   * @param delimiter
   */
  void remove_ch(std::string &str, const char &delimiter)
  {
    str.erase(std::remove(str.begin(), str.end(), delimiter), str.end());
  }

  /**
   * @brief Erases contents from std::vector.
   *
   * @param main_vector Initial vector.
   * @param contents Contents to remove.
   * @return int
   */
  void erase_from_vector(std::vector<std::string> &main_vector,
                         const std::vector<std::string> &contents)
  {
    for (auto &_content : contents)
    {
      std::string content = _content;

      auto location = std::find(main_vector.begin(), main_vector.end(), content);

      if (location == main_vector.end())
        continue;

      main_vector.erase(location);
    }
  }

  /**
   * @brief Check if flags contains a flag with specific content, then removes
   * content from flag and returns it.
   *
   * @param flags Command flags.
   * @param content
   * @return std::string
   */
  std::string get_flag_defined(const std::vector<std::string> &flags,
                               const std::string &content)
  {
    for (auto &flag : flags)
      if (has_contents(flag, content))
        return flag.substr(content.size(), flag.size() - 1);

    return "";
  }

  /**
   * @brief Replaces all occurances of a with b in text.
   *
   * @param text
   * @param a To replace
   * @param b Replace with
   */
  void replace(std::string &text, const std::string &a, const std::string &b)
  {
    std::size_t start_pos = 0;

    while ((start_pos = text.find(a, start_pos)) != std::string::npos)
    {
      text.replace(start_pos, a.length(), b);
      start_pos += b.length();
    }
  }

  /**
   * @brief Splits string based on inputted delimiter.
   *
   * @param str
   * @param delimiter
   * @return std::vector<std::string>
   */
  std::vector<std::string> split(const std::string &str,
                                 const std::string &delimiter)
  {
    std::vector<std::string> tokens;
    size_t start = 0;
    size_t end = str.find(delimiter);

    while (end != std::string::npos)
    {
      tokens.push_back(str.substr(start, end - start));
      start = end + delimiter.length();
      end = str.find(delimiter, start);
    }

    tokens.push_back(str.substr(start, end));

    return tokens;
  }

  /**
   * @brief Writes CURL callback to string.
   *
   * @param contents
   * @param size
   * @param nmemb
   * @param output
   * @return size_t
   */
  size_t write_callback(void *contents, size_t size, size_t nmemb,
                        std::string *output)
  {
    size_t total_size = size * nmemb;
    output->append(static_cast<char *>(contents), total_size);
    return total_size;
  }

  /**
   * @brief Writes CURL callback to file.
   *
   * @param contents
   * @param size
   * @param nmemb
   * @param outputFile
   * @return size_t
   */
  size_t write_file_callback(void *contents, size_t size, size_t nmemb,
                             std::ofstream *output_file)
  {
    size_t total_size = size * nmemb;
    output_file->write(static_cast<char *>(contents), total_size);
    return total_size;
  }

  /**
   * @brief CURL --> Validates URL, return true if URL is invalid.
   *
   * @param curl
   * @param target_url
   * @return true
   * @return false
   */
  bool validate_url(
      const std::unique_ptr<CURL, decltype(&curl_easy_cleanup)> &curl,
      const std::string &target_url)
  {
    long http_code(0);

    curl_easy_getinfo(curl.get(), CURLINFO_RESPONSE_CODE, &http_code);

    if (http_code >= 200 && http_code < 300)
      logger::success_q("passed validation with http code " +
                            std::to_string(http_code),
                        target_url);
    else
    {
      logger::error_q("failed validation with http code " +
                          std::to_string(http_code),
                      target_url);
      return true;
    }

    return false;
  }

  /**
   * @brief CURL --> Uses curl_easy_perform() on a provided link.
   *
   * @param curl
   * @param url
   * @return true
   * @return false
   */
  bool curl_perform(const std::unique_ptr<CURL, decltype(&curl_easy_cleanup)> &curl, const std::string &url)
  {
    // ! --> Double free of object
    curl_easy_setopt(curl.get(), CURLOPT_URL, url.c_str());
    CURLcode res = curl_easy_perform(curl.get());

    if (res != CURLE_OK)
    {
      logger::error_q(": curl_easy_perform() failed : " + url, curl_easy_strerror(res));
      return true;
    }

    return false;
  };
} // namespace misc
