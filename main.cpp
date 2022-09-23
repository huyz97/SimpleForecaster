#include <iostream>
#include "include/SimpleForecaster.h"

int main(int argc, char** argv) {
    if(argc < 3){
        std::cout<<"should have 2 parameters"<<std::endl;
        return -1;
    }
    hyz::SimpleForecaster forecaster;
    forecaster.loadCsv(argv[1]);
    forecaster.getOutputToCsv(argv[2]);

    return 0;
}
