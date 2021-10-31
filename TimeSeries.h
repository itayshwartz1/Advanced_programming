//
// Created by itay2 on 31/10/2021.
//

#ifndef DEV_TIMESERIES_H
#define DEV_TIMESERIES_H


#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class TimeSeries{
    char** feature_table;
    TimeSeries();

public:TimeSeries(char *fileName);
};

#endif //DEV_TIMESERIES_H
