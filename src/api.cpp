/**
 * @file api.cpp
 * @brief Adds functionality to api.h
 * @version 0.1
 * @date 2025-02-26
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "api.h"
#include "config.h"

/**
 * @brief Writes CURL callback
 * 
 * @param contents Contents to write
 * @param size Size of contents
 * @param nmemb Size of element
 * @param output Output to append to
 * @return size_t 
 */
size_t write_callback(void *contents, const size_t size, const size_t nmemb, std::string *output) {
	const size_t total_size = size * nmemb;
	output->append((char *)contents, total_size);

	return total_size;
}

/**
 * @brief Initializes libcurl
 * 
 * @return uint8_t 
 */
uint8_t API::CURL_init() {
	curl.reset(curl_easy_init());
	
	if (!curl) {
		logger.error("failed to initialize libcurl");
		return 1;
	}
	
	curl_easy_setopt(curl.get(), CURLOPT_WRITEFUNCTION, write_callback);
	curl_easy_setopt(curl.get(), CURLOPT_WRITEDATA, &response);
	curl_easy_setopt(curl.get(), CURLOPT_USERAGENT, updates_useragent);

	return 0;
}

/**
 * @brief Set CURL url
 * 
 * @param url 
 */
void API::set_url(const std::string &url) {
	curl_easy_setopt(curl.get(), CURLOPT_URL, url.c_str());
}

/**
 * @brief Calls curl_easy_perform to get data from API
 * 
 * @return true 
 * @return false 
 */
bool API::fetch() {
	res = curl_easy_perform(curl.get());

	if (res != CURLE_OK) {
		logger.error("failed to fetch data from url");
		return false;
	}

	return true;
}

/**
 * @brief Returns parsed response from API
 * 
 * @return rapidjson::Document 
 */
rapidjson::Document API::get_response() {
	rapidjson::Document doc;
	doc.Parse(response.c_str());
	return doc;
}

/**
 * @brief Get API singleton
 * 
 * @return API& 
 */
API &API::get() {
	static API obj;
	return obj;
}

Logger &API::logger = Logger::get();
std::unique_ptr<CURL, decltype(&curl_easy_cleanup)> API::curl(nullptr, curl_easy_cleanup);