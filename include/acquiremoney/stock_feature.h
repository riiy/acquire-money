#pragma once

#include <string>
#include <unordered_map>
#include <vector>

namespace amshare {

  namespace stock_hist_em {
    /**
     * @brief 东方财富网-沪深京 A 股-实时行情 https://quote.eastmoney.com/center/gridlist.html#hs_a_board
     */
    class stock_zh_a_spot_em {
      /**
       * @brief 数据
            "序号", "代码", "名称", "最新价", "涨跌幅", "涨跌额", "成交量", "成交额", "振幅", "最高", "最低", "今开", "昨收",
            "量比", "换手率", "市盈率-动态", "市净率", "总市值", "流通市值", "涨速", "5分钟涨跌", "60日涨跌幅", "年初至今涨跌幅",
       * */
      struct row {
        std::string 序号;
        std::string 代码;
        std::string 名称;
        double 最新价;
        double 涨跌幅;
        double 涨跌额;
        double 成交量;
        double 成交额;
        double 振幅;
        double 最高;
        double 最低;
        double 今开;
        double 昨收;
        double 量比;
        double 换手率;
        double 市盈率_动态;
        double 市净率;
        double 总市值;
        double 流通市值;
        double 涨速;
        double 五分钟涨跌;
        double 六十日涨跌;
        double 年初至今涨跌幅;
      };

    public:
      /**
       * @brief 创建东方财富网-沪深京 A 股-实时行情
       */
      stock_zh_a_spot_em();
      /**
       * @brief 写入结果到csv文件
       * @param file_path 文件路径
       */
      void to_csv();
      /**
       * @brief 取数据
       * */
      std::vector<row> get_data();
    };
  }  // namespace stock_hist_em
}  // namespace amshare
