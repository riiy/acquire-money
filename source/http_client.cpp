#include <acquiremoney/http_client.h>
#include <curl/curl.h>
#include <curl/multi.h>

#include <cstring>

using namespace amshare;

CURLcode http::get(const std::string &url, std::string &response) {
  CURL *curl;
  CURLcode res = CURLE_OK;
  curl_global_init(CURL_GLOBAL_ALL);

  curl = curl_easy_init();
  if (curl) {
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_cb);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
  }
  curl_global_cleanup();
  return res;
}
