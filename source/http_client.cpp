#include <acquiremoney/http_client.h>
#include <curl/curl.h>

#include <cstring>

using namespace amshare;

std::string http::get(const std::string &url) {
  std::string _raw_data;
  CURL *curl;
  CURLcode res;
  curl_global_init(CURL_GLOBAL_ALL);

  curl = curl_easy_init();
  if (curl) {
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_cb);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &_raw_data);

    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    if (res != CURLE_OK) {
      throw;
    }
  }

  curl_global_cleanup();
  return _raw_data;
}
