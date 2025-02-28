/**
 * @file updates.cpp
 * @brief Implements CPM update managing
 * @version 0.1
 * @date 2025-02-26
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "updates.h"
#include "api.h"
#include "config.h"
#include "logger.h"
#include "misc.h"

#include <cstdint>
#include <string>
#include <vector>

#include <rapidjson/document.h>

namespace updates {
API &api = API::get();
Logger &logger = Logger::get();

bool scanned = false;

/**
 * @brief Scan for updates to CPM
 * 
 * @return uint8_t
 */
uint8_t scan() {
  /* Limit to 1 scan / activation */
  if (scanned == true)
    return true;

  scanned = true;

  /* Get latest version from github repo */
  api.set_url(repo_link);
  const uint8_t status = api.fetch();

  if (!status) // error message handled by fetch function
    return 2;

  /* Parse response */
  rapidjson::Document doc(api.get_response());

  if (!doc.HasMember("tag_name") || !doc["tag_name"].IsString()) {
    logger.error("failed to scan for updates (response parsing error)");
    return 2;
  }

  /* Compare versions */
  std::string tag(doc["tag_name"].GetString());
  std::string current_version(version_string);

  /* Remove 'v' from 'vX.X.X' */
  tag = tag.substr(1, tag.size() - 1);

  /* Split into major.minor.patch */
  std::vector<std::string> split_tag = misc::split_string(tag, ".");
  std::vector<std::string> split_current_version =
      misc::split_string(current_version, ".");

  for (uint8_t i = 0; i < 3; i++) {
    if (std::stoi(split_tag[i]) > std::stoi(split_current_version[i])) {
      logger.warn("newer version of CPM availible (v" + tag + ")");
      return 1;
    }
  }

  return 0;
}
} // namespace updates