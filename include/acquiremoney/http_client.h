#pragma once

#include <string>

inline size_t write_cb(char *data, size_t n, size_t l, void *userp) {
  ((std::string *)userp)->append((char *)data, n * l);
  return n * l;
}
namespace amshare {
  namespace http {
    std::string get(const std::string &url);
  }  // namespace http
}  // namespace amshare
