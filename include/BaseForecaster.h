//
// Created by 30299 on 2022/9/23.
//

#ifndef CSV_READER_BASEFORECASTER_H
#define CSV_READER_BASEFORECASTER_H
#include "MdStruct.hpp"

namespace hyz{

template <typename Impl>
class BaseForecaster{
public:
    inline Impl &derived(){
        return static_cast<Impl&>(*this);
    }

    void onData(std::shared_ptr<TradeData> &data){
        return derived().onData(data);
    }
};
}
#endif //CSV_READER_BASEFORECASTER_H
