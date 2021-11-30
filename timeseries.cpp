/**
 * Name: Roei Gehassi and Itay Shwartz
 * ID: 208854754 and 318528171
 */
#include "timeseries.h"
#include <iostream>
#include <string>

using std::string;
using std::vector;
using std::getline;

/**
 * This is the main builder of TimeSeries. is creat a new table from csv file.
 * @param fileName
 */
TimeSeries::TimeSeries(const char *fileName) {
    feature_table = {};
    feature_names = {};
    feature_map = {};
    std::fstream myfile;
    //open file and read mode.
    myfile.open(fileName, std::ios::in);
    if (myfile.is_open()) {
        string line;
        int first_line = 1;
        //go through the lines.
        while (getline(myfile, line)) {
            //if it's the first line - we added the data to br the headline of the vector.
            if (first_line) {
                createNamesTable(line);
                first_line = 0;
                //if we creat before to the table vector - we just add the data to the existing vectors by order.
            } else {
                createValuesTable(line);
            }
        }
    }
    myfile.close();
    //initializing mapping between feature name and the vector of values.
    initializeMap();
}

/**
 * This function creat new vectors to the table. the first data in the vectors is the given data.
 * @param line
 */
void TimeSeries::createNamesTable(string line) {
    size_t pos = 0;
    string token;
    string delimiter = ",";

    //we split the line and add the data to the feature_name.
    while ((pos = line.find(delimiter)) != string::npos) {
        token = line.substr(0, pos);
        feature_names.push_back(token);
        line.erase(0, pos + delimiter.length());
    }
    //we add one more vector because the last token finished without ',' - so we need to add it anyway.
    feature_names.push_back(line);
}

/**
 * This function add values to the existing table by the order they been given.
 * @param line
 */
void TimeSeries::createValuesTable(string line) {

    int pos = 0;
    int counter = 0;
    float temp;
    if (feature_table.empty()) {
        while ((pos = (int) line.find(',')) != string::npos) {
            temp = std::stof(line.substr(counter, pos));
            vector<float> new_vec;
            new_vec.push_back(temp);
            feature_table.push_back(new_vec);
            line.erase(counter, pos + 1);
        }
        vector<float> new_vec;
        new_vec.push_back(std::stof(line));
        feature_table.push_back(new_vec);


    } else {
        for (auto &i: feature_table) {
            int counter = (int) line.find(',', pos);
            temp = std::stof(line.substr(pos, counter));
            i.push_back(temp);
            line.erase(pos, counter + 1);
        }
    }
}

/**
 * This function return
 * @return const vector<vector<string> >
 */
vector<vector<float> > TimeSeries::getFeatureTable() const {
    return feature_table;
}

vector<std::string> TimeSeries::getNameTable() const {
    return feature_names;
}

int TimeSeries::size() const {
    return (int) feature_table.size();
}

/**
 * Initializing the map, which maps between feature name and its vector of values.
 */
void TimeSeries::initializeMap() {
    for (int i = 0; i < feature_names.size(); i++) {
        feature_map.insert({feature_names[i], feature_table[i]});
    }
}
