//
// Created by 30299 on 2022/9/23.
//

#ifndef CSV_READER_CSVREADER_HPP
#define CSV_READER_CSVREADER_HPP

#include <string>
#include <fstream>
#include <iostream>
#include "BaseForecaster.h"


namespace hyz {

template<typename ForecasterType>
class CsvReader {
public:
    CsvReader() = default;

    ~CsvReader() = default;

    CsvReader(CsvReader &) = delete;

    CsvReader(CsvReader &&) = delete;

    CsvReader &operator=(CsvReader &) = delete;

    int readFile(const char *file_path) {
        std::ifstream fileIn(file_path);
        if (!fileIn.is_open()) {
            std::cout << "open infile failed " << file_path << " not exists" << std::endl;
            return -1;
        }
        std::string row;
        while (std::getline(fileIn, row)) {
            auto tradeData = TradeData::string2TradeData(row);
            m_listener->onData(tradeData);
        }
        return 0;
    }

    inline void setListener(BaseForecaster<ForecasterType> *t_listener) {
        m_listener = t_listener;
    }

private:
    BaseForecaster<ForecasterType> *m_listener;
};

} // hyz

#endif //CSV_READER_CSVREADER_HPP
