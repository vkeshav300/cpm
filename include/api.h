/**
 * @file api.h
 * @brief Contains code pertaining to usage of libcurl
 * @version 0.1
 * @date 2025-02-26
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include "logger.h"

#include <cstdint>
#include <memory>

#include <curl/curl.h>
#include <rapidjson/document.h>

size_t write_callback(void *contents, const size_t size, const size_t nmemb,
                      std::string *output);

class API {
private:
  static Logger &logger;

  // CURL *curl;
  static std::unique_ptr<CURL, decltype(&curl_easy_cleanup)> curl;
  CURLcode res;
  std::string response;
  std::string url;

  API() {}

public:
  API(const API &obj) = delete;

  uint8_t CURL_init();

  void set_url(const std::string &_url);

  bool fetch();

  rapidjson::Document get_response();

  static API &get();
};