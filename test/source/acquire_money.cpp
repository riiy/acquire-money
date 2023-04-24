#include <acquiremoney/greeter.h>
#include <acquiremoney/stock_feature.h>
#include <acquiremoney/version.h>
#include <doctest/doctest.h>

#include <string>

TEST_CASE("Greeter") {
  using namespace greeter;
  Greeter greeter("测试");

  CHECK(greeter.greet(LanguageCode::EN) == "Hello, 测试!");
  CHECK(greeter.greet(LanguageCode::DE) == "Hallo 测试!");
  CHECK(greeter.greet(LanguageCode::ES) == "¡Hola 测试!");
  CHECK(greeter.greet(LanguageCode::FR) == "Bonjour 测试!");
}

TEST_CASE("AcquireMoney version") {
  static_assert(std::string_view(ACQUIREMONEY_VERSION) == std::string_view("1.0"));
  CHECK(std::string(ACQUIREMONEY_VERSION) == std::string("1.0"));
}

TEST_CASE("stock_zh_a_spot_em") {
  auto ret = amshare::stock_feature::stock_zh_a_spot_em();
}
