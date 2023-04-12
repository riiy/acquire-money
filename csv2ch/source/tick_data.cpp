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
