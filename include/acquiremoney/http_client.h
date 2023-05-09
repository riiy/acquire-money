#pragma once

#include <curl/curl.h>

#include <string>

namespace am {
  namespace http {
    CURLcode get(const std::string &url, std::string &response);
  }  // namespace http
}  // namespace am
