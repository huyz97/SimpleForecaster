//
// Created by 30299 on 2022/9/23.
//

#ifndef CSV_READER_SIMPLEFORECASTER_H
#define CSV_READER_SIMPLEFORECASTER_H
#include "CsvReader.hpp"
#include <map>
#include <cmath>
#include <memory>


namespace hyz {

struct BarData{
    int64_t timestamp_gap;
    int64_t volume_sum;
    double price_avg; // use int64_t will lose precision
    int64_t high;
    int64_t last_timestamp;
};


class SimpleForecaster : public BaseForecaster<SimpleForecaster> {
public:
    SimpleForecaster();

    ~SimpleForecaster() = default;

    SimpleForecaster(SimpleForecaster &) = delete;

    SimpleForecaster(SimpleForecaster &&) = delete;

    SimpleForecaster &operator=(SimpleForecaster &) = delete;

    void onData(std::shared_ptr<TradeData> &);

    void loadCsv(const char*);

    void getOutputToCsv(const char*);

private:
    std::unique_ptr<CsvReader<SimpleForecaster>> m_reader;

    std::map<std::string ,std::shared_ptr<BarData>> m_symbol_bar_map; // for ascending

};
}

#endif //CSV_READER_SIMPLEFORECASTER_H
