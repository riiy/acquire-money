#include <acquiremoney/stock_feature.h>

#include <iostream>
#include <ostream>
#include <string>
#include <vector>

using namespace amshare;

stock_hist_em::zh_a_spot::zh_a_spot() {}
std::vector<stock_hist_em::zh_a_spot::row> stock_hist_em::zh_a_spot::get_data() {
  std::vector<stock_hist_em::zh_a_spot::row> _data;
  return _data;
}
void stock_hist_em::zh_a_spot::to_csv(std::string file_path) { std::cout << file_path << std::endl; };
