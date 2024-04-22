/**
 * @file misc.h
 * @brief Outlines misc.cpp.
 * @version 0.1
 * @date 2023-11-23
 *
 * @copyright Copyright (c) 2023
 *
 */
#pragma once

#include <curl/curl.h>
#include <memory>
#include <string>
#include <vector>

namespace misc
{
    std::vector<std::string> sub_vector(const std::vector<std::string> &main_vector, const int begin_index, const int end_index);

    bool has_contents(std::string text, std::string contents);

    bool find_in_vector(const std::vector<std::string> &main_vector, std::string content);

    void trim(std::string &str);

    void remove_ch(std::string &str, const char &delimiter);

    void erase_from_vector(std::vector<std::string> &main_vector, const std::vector<std::string> &contents);

    void replace(std::string &text, const std::string &a, const std::string &b);

    std::vector<std::string> split(const std::string &str, const std::string &delimiter);

    std::string get_flag_defined(const std::vector<std::string> &flags, const std::string &content);

    size_t write_callback(void *contents, size_t size, size_t nmemb, std::string *output);

    size_t write_file_callback(void *contents, size_t size, size_t nmemb, std::ofstream *output_file);

    bool validate_url(
        const std::unique_ptr<CURL, decltype(&curl_easy_cleanup)> &curl,
        const std::string &target_url);

    bool curl_perform(
        const std::unique_ptr<CURL, decltype(&curl_easy_cleanup)> &curl,
        const std::string &url);
} // namespace misc
