//////
// Created by itay2 on 31/10/2021.
//

#ifndef DEV_TIMESERIES_H
#define DEV_TIMESERIES_H


#include <iostream>
#include <fstream>

#include <string>
#include <vector>

class TimeSeries{

public:TimeSeries(char *fileName);

    std::vector<std::vector<float> > feature_table;
    std::vector<std::string> feature_names;

    void createNamesTable(std::string basicString);

    void createValuesTable(std::string basicString);

    int size() const;

    std::vector<std::vector< float>> getFeatureTable() const;

    std::vector<std::string> getNameTable() const;
};

#endif //DEV_TIMESERIES_H
