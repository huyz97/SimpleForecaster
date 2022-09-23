//
// Created by 30299 on 2022/9/23.
//

#ifndef CSV_READER_MDSTRUCT_HPP
#define CSV_READER_MDSTRUCT_HPP

#include <cstdint>
#include <cassert>
#include <memory>
#include <cstdlib>
#include <cstring>

namespace hyz{

struct TradeData{
    int64_t timestamp;
    char symbol[8]; // memory alignment
    int64_t quantity;
    int64_t price;


    static std::shared_ptr<TradeData> string2TradeData(std::string &row) {
        std::shared_ptr<TradeData> trade_data = std::make_shared<TradeData>();
        char split = ',';
        size_t start = 0;
        auto end = row.find(split);
        assert(end != std::string::npos); // input is illegal
        trade_data->timestamp = std::stol(row.substr(start, end - start));

        start = end + 1;
        end = row.find(split, start);
        assert(end != std::string::npos);
        strncpy(trade_data->symbol, row.substr(start, end - start).c_str(), sizeof(trade_data->symbol));

        start = end + 1;
        end = row.find(split, start);
        assert(end != std::string::npos);
        trade_data->quantity = std::stol(row.substr(start, end - start));

        start = end + 1;
        end = row.find(split, start);
        assert(end == std::string::npos); // should no more ','
        trade_data->price = std::stol(row.substr(start));

        return trade_data;
    }
};

}

#endif //CSV_READER_MDSTRUCT_HPP
