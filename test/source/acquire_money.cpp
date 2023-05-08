#include <acquiremoney/http_client.h>
#include <acquiremoney/stock_feature.h>
#include <acquiremoney/version.h>
#include <doctest/doctest.h>

#include <iostream>
#include <string>
TEST_CASE("AcquireMoney version") {
  static_assert(std::string_view(ACQUIREMONEY_VERSION) == std::string_view("1.0"));
  CHECK(std::string(ACQUIREMONEY_VERSION) == std::string("1.0"));
}

TEST_CASE("http client") {
  auto uri = "";
  std::string resp = "https://www.baidu.com";
  auto res = am::http::get(uri, resp);
  std::cout << res << std::endl;
  std::cout << resp << std::endl;
}
TEST_CASE("stock_zh_a_spot_em") { auto ret = am::stock_feature::stock_zh_a_spot_em(); }
