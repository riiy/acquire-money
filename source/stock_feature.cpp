#include <acquiremoney/stock_feature.h>
#include <curl/curl.h>
#include <spdlog/spdlog.h>

#include <iostream>
#include <map>
#include <ostream>
#include <string>
#include <vector>

using namespace amshare;
static size_t write_cb(char *data, size_t n, size_t l, void *userp) {
  /* take care of the data here, ignored in this example */
  (void)data;
  ((std::string *)userp)->append((char *)data, n * l);
  (void)userp;
  return n * l;
}
stock_hist_em::zh_a_spot::zh_a_spot() {
  using namespace std;

  CURL *curl;
  CURLcode res;
  string read_buf;
  curl_global_init(CURL_GLOBAL_ALL);

  curl = curl_easy_init();
  if (curl) {
    // url = "http://82.push2.eastmoney.com/api/qt/clist/get"
    string url
        = "https://82.push2.eastmoney.com/api/qt/clist/"
          "get?pn=1&pz=60&po=1&np=1&ut=bd1d9ddb04089700cf9c27f6f7426281&fltt=2&invt=2&fid=f3&fs=m:0+t:6,m:0+t:80,m:1+t:2,m:1+t:23,m:0+t:81+s:2048&fields=f1,f2,f3,f4,f5,f6,f7,f8,f9,f10,f12,f13,f14,"
          "f15,"
          "f16,"
          "f17,f18,f20,f21,f23,f24,f25,f22,f11,f62,f128,f136,f115,f152&_=1681781731653";
    // string url = "http://httpbin.org/get";
    // string params = "name=John&age=30";
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    // curl_easy_setopt(curl, CURLOPT_, params.c_str());

    // struct curl_slist *headers = NULL;
    // headers = curl_slist_append(headers, "Accept: */*");
    // headers = curl_slist_append(headers, "Accept-Language: en-US,en;q=0.9,zh-CN;q=0.8,zh;q=0.7");
    // curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_cb);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &read_buf);
#ifdef SKIP_PEER_VERIFICATION
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
#endif
#ifdef SKIP_HOSTNAME_VERIFICATION
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
#endif

    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    if (res != CURLE_OK) {
      fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
    } else {
      // 使用readBuffer获取响应内容
      // spdlog::info(read_buf);
      cout << read_buf << endl;
    }
  }

  curl_global_cleanup();
}
std::vector<stock_hist_em::zh_a_spot::row> stock_hist_em::zh_a_spot::get_data() { return _data; }
int stock_hist_em::zh_a_spot::to_csv(std::string file_path) {
  std::cout << file_path << std::endl;
  return 0;
};
