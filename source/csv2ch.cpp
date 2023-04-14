#include <acquiremoney/csv2ch.h>
#include <clickhouse/client.h>
#include <clickhouse/columns/decimal.h>
#include <clickhouse/columns/numeric.h>
#include <clickhouse/columns/string.h>
#include <csv.h>

#include <iostream>
#include <ostream>
#include <string>

auto tick_data() -> int {
  clickhouse::Client client(clickhouse::ClientOptions().SetHost("localhost").SetPort(19000));
  std::string path = "/data/stock/tick_data";
  for (const auto& entry : fs::directory_iterator(path)) {
    if (entry.is_directory()) {
      clickhouse::Block block;
      auto _symbol = std::make_shared<clickhouse::ColumnFixedString>(8);
      auto _date = std::make_shared<clickhouse::ColumnInt32>();
      auto _time = std::make_shared<clickhouse::ColumnFixedString>(8);
      auto _price = std::make_shared<clickhouse::ColumnFloat64>();
      auto _change = std::make_shared<clickhouse::ColumnFloat64>();
      auto _volume = std::make_shared<clickhouse::ColumnFloat64>();
      auto _turnover = std::make_shared<clickhouse::ColumnFloat64>();
      auto _kind = std::make_shared<clickhouse::ColumnFixedString>(1);
      auto symbol = get_stem(entry.path());
      for (const auto& subentry : fs::directory_iterator(entry)) {
        if (subentry.is_directory()) continue;
        auto date_str = get_stem(subentry.path());
        auto postion = date_str.find("2023");
        if (postion == std::string::npos) {
          std::cout << subentry.path() << std::endl;
          continue;
        }
        auto date = std::stoi(date_str);
        io::CSVReader<7> in(subentry.path().c_str());
        in.set_header("seq", "time", "price", "change", "volume", "turnover", "kind");
        std::string seq;
        std::string time;
        long double price;
        long double change;
        long double volume;
        long double turnover;
        std::string kind;
        while (in.read_row(seq, time, price, change, volume, turnover, kind)) {
          _symbol->Append(symbol);
          _date->Append(date);
          _time->Append(time);
          _price->Append(price);
          _change->Append(change);
          _volume->Append(volume);
          _turnover->Append(turnover);
          _kind->Append(kind);
        }
      }
      block.AppendColumn("symbol", _symbol);
      block.AppendColumn("date", _date);
      block.AppendColumn("time", _time);
      block.AppendColumn("price", _price);
      block.AppendColumn("change", _change);
      block.AppendColumn("volume", _volume);
      block.AppendColumn("turnover", _turnover);
      block.AppendColumn("kind", _kind);
      client.Insert("default.tick_data", block);
    }
  }
  return 0;
}

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
