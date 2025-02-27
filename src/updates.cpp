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
#include "config.h"
#include "api.h"
#include "logger.h"
#include "misc.h"

#include <vector>
#include <string>
#include <cstdint>

#include <rapidjson/document.h>

namespace updates {
API &api = API::get();
Logger &logger = Logger::get();

void scan() {
    /* Get latest version from github repo */
    api.set_url(repo_link);
    api.fetch();

    rapidjson::Document doc(api.get_response());

    if (!doc.HasMember("tag_name") || !doc["tag_name"].IsString())
        logger.error("failed to scan for updates");

    /* Compare versions */
    std::string tag(doc["tag_name"].GetString());
    std::string current_version(version_string);

    /* Remove 'v' from 'vX.X.X' */
    tag = tag.substr(1, tag.size() - 1);

    /* Split into major.minor.patch */
    std::vector<std::string> split_tag = misc::split_string(tag, ".");
    std::vector<std::string> split_current_version = misc::split_string(current_version, ".");

    for (uint8_t i = 0; i < 3; i++) {
        if (std::stoi(split_tag[i]) > std::stoi(split_current_version[i])) {
            logger.warn("newer version of CPM availible");
            break;
        }
    }
}
} // namespace updates