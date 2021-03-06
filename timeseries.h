/**
 * Name: Roei Gehassi and Itay Shwartz
 * ID: 208854754 and 318528171
 */
#ifndef DEV_TIMESERIES_H
#define DEV_TIMESERIES_H


#include <iostream>
#include <fstream>

#include <string>
#include <vector>
#include <map>

class TimeSeries {

public:
    TimeSeries(const char *fileName);

    std::vector<std::vector<float> > feature_table;
    std::vector<std::string> feature_names;
    std::map<std::string, std::vector<float>> feature_map;

    void initializeMap();

    void createNamesTable(std::string basicString);

    void createValuesTable(std::string basicString);

    int size() const;

    std::vector<std::vector<float>> getFeatureTable() const;

    std::vector<std::string> getNameTable() const;
};

#endif //DEV_TIMESERIES_H
