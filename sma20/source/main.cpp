#include <cxxopts.hpp>
#include <fstream>
#include <iostream>
#include <ss/parser.hpp>
#include <string>
#include <unordered_map>

#include "acquiremoney/version.h"

auto main(int argc, char** argv) -> int {
  cxxopts::Options options(*argv, "A program to welcome the world!");

  // clang-format off
  options.add_options()
    ("h,help", "Show help")
    ("v,version", "Print the current version number")
  ;
  // clang-format on

  auto result = options.parse(argc, argv);

  if (result["help"].as<bool>()) {
    std::cout << options.help() << std::endl;
    return 0;
  }

  if (result["version"].as<bool>()) {
    std::cout << "AcquireMoney, version " << ACQUIREMONEY_VERSION << std::endl;
    return 0;
  }
  ss::parser p{"/data/stock/index/sh510050.csv", ","};
  for (const auto& [seq, date, open, close, high, low, volume, amount, sma20] :
       p.iterate<int, std::string, float, float, float, float, float, float, float>())
    std::cout << open << " " << close << " " << sma20 << std::endl;

  return 0;
}
