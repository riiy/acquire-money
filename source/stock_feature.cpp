#include <acquiremoney/stock_feature.h>
#include <curl/curl.h>
#include <json.h>
#include <spdlog/spdlog.h>

#include <fstream>
#include <iostream>
#include <map>
#include <ostream>
#include <string>
#include <vector>

using namespace amshare;
using json = nlohmann::json;
static size_t write_cb(char *data, size_t n, size_t l, void *userp) {
  ((std::string *)userp)->append((char *)data, n * l);
  return n * l;
}
stock_hist_em::zh_a_spot::zh_a_spot() {
  using namespace std;

  CURL *curl;
  CURLcode res;
  curl_global_init(CURL_GLOBAL_ALL);

  curl = curl_easy_init();
  if (curl) {
    string url
        = "http://82.push2.eastmoney.com/api/qt/clist/"
          "get?pn=1&pz=50000&po=1&np=1&ut=bd1d9ddb04089700cf9c27f6f7426281&fltt=2&invt=2&fid=f3&fs=m:0+t:6,m:0+t:80,m:1+t:2,m:1+t:23,m:0+t:81+s:2048&fields=f1,f2,f3,f4,f5,f6,f7,f8,f9,f10,f12,f13,f14,"
          "f15,"
          "f16,"
          "f17,f18,f20,f21,f23,f24,f25,f22,f11,f62,f128,f136,f115,f152&_=1681781731653";

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_cb);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &_raw_data);

    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    if (res == CURLE_OK) {
      if (!_raw_data.empty()) {
        auto data = json::parse(_raw_data);
        cout << data["rt"] << endl;
      }
    }
  }

  curl_global_cleanup();
}
std::vector<stock_hist_em::zh_a_spot::row> stock_hist_em::zh_a_spot::get_data() { return _data; }
int stock_hist_em::zh_a_spot::to_csv(std::string file_path) {
  std::ofstream out(file_path.c_str());
  out << _raw_data;
  out.close();
  return 0;
};
