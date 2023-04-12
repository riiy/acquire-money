#include <acquiremoney/csv2ch.h>
#include <clickhouse/client.h>
#include <clickhouse/columns/decimal.h>
#include <clickhouse/columns/numeric.h>
#include <clickhouse/columns/string.h>
#include <csv.h>

#include <iostream>
#include <ostream>
#include <string>

auto daily_data() -> int {
  clickhouse::Client client(clickhouse::ClientOptions().SetHost("localhost").SetPort(19000));
  std::string path = "/data/stock/daily_data_qfq";
  for (const auto& entry : fs::directory_iterator(path)) {
    clickhouse::Block block;

    auto symbol = std::make_shared<clickhouse::ColumnFixedString>(8);
    auto _date = std::make_shared<clickhouse::ColumnInt32>();
    auto _open = std::make_shared<clickhouse::ColumnFloat64>();
    auto _high = std::make_shared<clickhouse::ColumnFloat64>();
    auto _low = std::make_shared<clickhouse::ColumnFloat64>();
    auto _close = std::make_shared<clickhouse::ColumnFloat64>();
    auto _volume = std::make_shared<clickhouse::ColumnFloat64>();
    auto _outstanding_share = std::make_shared<clickhouse::ColumnFloat64>();
    auto _turnover = std::make_shared<clickhouse::ColumnFloat64>();

    io::CSVReader<8> in(entry.path().c_str());
    in.read_header(io::ignore_extra_column, "date", "open", "high", "low", "close", "volume",
                   "outstanding_share", "turnover");
    std::string date_str;
    long double open;
    long double high;
    long double low;
    long double close;
    long double volume;
    long double outstanding_share;
    long double turnover;
    while (in.read_row(date_str, open, high, low, close, volume, outstanding_share, turnover)) {
      std::string x = "-", y = "";
      size_t pos;
      while ((pos = date_str.find(x)) != std::string::npos) {
        date_str.replace(pos, 1, y);
      }
      auto date = std::stoi(date_str);
      symbol->Append(get_stem(entry));
      _date->Append(date);
      _open->Append(open);
      _high->Append(high);
      _low->Append(low);
      _close->Append(close);
      _volume->Append(volume);
      _outstanding_share->Append(outstanding_share);
      _turnover->Append(turnover);
    }
    block.AppendColumn("symbol", symbol);
    block.AppendColumn("date", _date);
    block.AppendColumn("open", _open);
    block.AppendColumn("high", _high);
    block.AppendColumn("low", _low);
    block.AppendColumn("close", _close);
    block.AppendColumn("volume", _volume);
    block.AppendColumn("outstanding_share", _outstanding_share);
    block.AppendColumn("turnover", _turnover);
    client.Insert("default.daily_data", block);
  }
  return 0;
}
