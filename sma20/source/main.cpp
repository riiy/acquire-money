#include <cxxopts.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>

#include "acquiremoney/version.h"
using namespace std;
int read_csv(string fname) {
  vector<vector<string>> content;
  vector<string> row;
  string line, word;

  fstream file(fname, ios::in);
  if (file.is_open()) {
    while (getline(file, line)) {
      row.clear();

      stringstream str(line);

      while (getline(str, word, ',')) row.push_back(word);
      content.push_back(row);
    }
  } else
    cout << "Could not open the file\n";

  for (int i = 0; i < content.size(); i++) {
    for (int j = 0; j < content[i].size(); j++) {
      cout << content[i][j] << " ";
    }
    cout << "\n";
  }

  return 0;
}
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
    std::cout << "Greeter, version " << ACQUIREMONEY_VERSION << std::endl;
    return 0;
  }
  read_csv("/data/stock/index/sh510050.csv");

  return 0;
}
