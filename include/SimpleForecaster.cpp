//
// Created by 30299 on 2022/9/23.
//

#include "SimpleForecaster.h"

namespace hyz {

SimpleForecaster::SimpleForecaster() : m_reader(std::make_unique<CsvReader<SimpleForecaster>>()) {
    m_reader->setListener(this);
}

void SimpleForecaster::onData(std::shared_ptr<TradeData> &tradeData) {
    std::string symbol = std::string(tradeData->symbol);
    if (m_symbol_bar_map.find(symbol) == m_symbol_bar_map.end()) { // new symbol data
        m_symbol_bar_map[symbol] = std::make_shared<BarData>(BarData{0, tradeData->quantity,
                                                                     double(tradeData->price), tradeData->price,
                                                                     tradeData->timestamp});
    } else { // update bar data
        auto &bar = m_symbol_bar_map[symbol];
        bar->timestamp_gap = std::max(bar->timestamp_gap, tradeData->timestamp - bar->last_timestamp);
        bar->high = std::max(bar->high, tradeData->price);
        bar->last_timestamp = tradeData->timestamp;
        bar->price_avg = (bar->price_avg * double(bar->volume_sum) + double(tradeData->price) * double(tradeData->quantity)) /
                         double(bar->volume_sum + tradeData->quantity);
        bar->volume_sum += tradeData->quantity;
    }
}

void SimpleForecaster::loadCsv(const char *file_path) {
    if (m_reader->readFile(file_path)){
        std::cout<<"load csv file failed"<<std::endl;
    }
}

void SimpleForecaster::getOutputToCsv(const char *file_path) {
    std::ofstream fileOut(file_path, std::ios::out);
    if (!fileOut.is_open()) {
        std::cout << "open outfile failed " << file_path << " not exists" << std::endl;
    }
    for (auto &iter: m_symbol_bar_map) {
        fileOut << iter.first << ','
                << iter.second->timestamp_gap << ','
                << iter.second->volume_sum << ','
                << round(iter.second->price_avg) << ','
                << iter.second->high << std::endl;
    }
    std::cout<<"finish! please check "<< file_path<<std::endl;
}

}