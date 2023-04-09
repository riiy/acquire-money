#include <assert.h>
#include <clickhouse/columns/date.h>
#include <clickhouse/columns/decimal.h>
#include <clickhouse/columns/numeric.h>
#include <clickhouse/columns/string.h>
#include <locale.h>
#include <time.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <iostream>
#include <ostream>
#include <string>

namespace fs = std::filesystem;

#include <clickhouse/client.h>

#include "csv.hpp"

std::string get_stem(const fs::path& p) { return p.stem().string(); }

auto main() -> int {
  clickhouse::Client client(clickhouse::ClientOptions().SetHost("localhost").SetPort(19000));

  std::string path = "/data/stock/daily_data_qfq";
  for (const auto& entry : fs::directory_iterator(path)) {
    break;
    clickhouse::Block block;

    auto symbol = std::make_shared<clickhouse::ColumnString>();
    auto date = std::make_shared<clickhouse::ColumnString>();
    auto open = std::make_shared<clickhouse::ColumnFloat64>();
    auto high = std::make_shared<clickhouse::ColumnFloat64>();
    auto low = std::make_shared<clickhouse::ColumnFloat64>();
    auto close = std::make_shared<clickhouse::ColumnFloat64>();
    auto volume = std::make_shared<clickhouse::ColumnFloat64>();
    auto outstanding_share = std::make_shared<clickhouse::ColumnFloat64>();
    auto turnover = std::make_shared<clickhouse::ColumnFloat64>();

    csv::CSVReader reader(entry.path().c_str());
    for (auto& row : reader) {
      symbol->Append(get_stem(entry));
      date->Append(row["date"].get());
      open->Append(row["open"].get<long double>());
      high->Append(row["high"].get<long double>());
      low->Append(row["low"].get<long double>());
      close->Append(row["close"].get<long double>());
      volume->Append(row["volume"].get<long double>());
      outstanding_share->Append(row["outstanding_share"].get<long double>());
      turnover->Append(row["turnover"].get<long double>());
    }
    block.AppendColumn("symbol", symbol);
    block.AppendColumn("date", date);
    block.AppendColumn("open", open);
    block.AppendColumn("high", high);
    block.AppendColumn("low", low);
    block.AppendColumn("close", close);
    block.AppendColumn("volume", volume);
    block.AppendColumn("outstanding_share", outstanding_share);
    block.AppendColumn("turnover", turnover);
    client.Insert("default.daily_data", block);
  }
  return 0;
}
