#include <assert.h>
#include <time.h>

#include <cstdio>
#include <cstdlib>
#include <cxxopts.hpp>
#include <iostream>
#include <ostream>
#include <string>

#include "acquiremoney/version.h"
#include "ta-lib/ta_libc.h"

auto main(int argc, char** argv) -> int {
  cxxopts::Options options(*argv, "A program to welcome the world!");

  // clang-format off
  options.add_options()
    ("h,help", "Show help")
    ("v,version", "Print the current version number")
    ("f,file", "文件路径")
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

  TA_Real close_price_array[5000] = {0};

  std::cout << "ta-lib test" << std::endl;

  // init ta-lib context
  TA_RetCode retcode;
  retcode = TA_Initialize();
  assert(retcode == TA_SUCCESS);

  TA_Real out[5000] = {0};
  TA_Integer out_begin = 0;
  TA_Integer out_nb_element = 0;

  retcode = TA_MA(0, 500, &close_price_array[0], 20, TA_MAType_SMA, &out_begin, &out_nb_element,
                  &out[0]);

  assert(retcode == TA_SUCCESS);

  std::cout << "---- compute output ----" << std::endl;
  std::cout << "out_begin_index: " << out_begin << std::endl;
  std::cout << "out_nb_element: " << out_nb_element << std::endl;
  std::cout << "out price array: " << std::endl;
  for (auto& price : out) std::cout << price << " ";

  // std::cout << close_price_array[0] << std::endl;
  std::cout << close_price_array[1] << std::endl;
  std::cout << close_price_array[4405] << std::endl;
  retcode = TA_Shutdown();
  assert(retcode == TA_SUCCESS);

  return 0;
}
