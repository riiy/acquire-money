#pragma once

#include <string>
#include <unordered_map>
#include <vector>

namespace am {
  /**
   * @brief  东方财富网-行情首页-沪深京 A 股
   */
  namespace stock_feature {

    /**
     * @brief   "序号", "代码", "名称", "最新价", "涨跌幅", "涨跌额", "成交量", "成交额", "振幅", "最高", "最低", "今开", "昨收",  "量比", "换手率", "市盈率-动态", "市净率", "总市值", "流通市值",
     * "涨速", "5分钟涨跌", "60日涨跌幅", "年初至今涨跌幅",
     */

    struct row {
      std::string 序号;
      std::string 代码;
      std::string 名称;
      double 最新价 = 0;
      double 涨跌幅 = 0;
      double 涨跌额 = 0;
      double 成交量 = 0;
      double 成交额 = 0;
      double 振幅 = 0;
      double 最高 = 0;
      double 最低 = 0;
      double 今开 = 0;
      double 昨收 = 0;
      double 量比 = 0;
      double 换手率 = 0;
      double 市盈率_动态 = 0;
      double 市净率 = 0;
      double 总市值 = 0;
      double 流通市值 = 0;
      double 涨速 = 0;
      double 五分钟涨跌 = 0;
      double 六十日涨跌 = 0;
      double 年初至今涨跌幅 = 0;
    };
    /**
     * @brief 东方财富网-沪深京A股-实时行情
     * https://quote.eastmoney.com/center/gridlist.html#hs_a_board
     * @return A股实时行情列表
     */
    std::vector<row> stock_zh_a_spot_em();
  }  // namespace stock_feature
}  // namespace am
