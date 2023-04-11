#include <acquiremoney/csv2ch.h>
#include <acquiremoney/greeter.h>
#include <acquiremoney/version.h>

#include <cxxopts.hpp>
#include <iostream>
#include <string>
#include <unordered_map>

auto main(int argc, char** argv) -> int {
  cxxopts::Options options(*argv, "A program to import data to clickhouse from csv files!");
  // clang-format off
  options.add_options()
    ("h,help", "Show help")
    ("v,version", "Print the current version number")
    ("d,daily", "导入daily data", cxxopts::value<bool>()->default_value("false"))
    ("t,tick", "导入tick data", cxxopts::value<bool>()->default_value("false"))
  ;
  // clang-format on

  auto result = options.parse(argc, argv);

  if (result["help"].as<bool>()) {
    std::cout << options.help() << std::endl;
    return 0;
  }

  if (result["version"].as<bool>()) {
    std::cout << "Greeter, version " << ACQUIREMONEY_VERSION << std::endl;
    return 0;
  }
  bool daily = result["daily"].as<bool>();
  if (daily) {
    daily_data();
  }
  if (result["tick"].as<bool>()) {
    tick_data();
  }

  return 0;
}
