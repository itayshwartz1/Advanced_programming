//
// Created by itay2 on 31/10/2021.
//

#include "TimeSeries.h"
#include <iostream>
#include <string>


/**
 * This is the main builder of TimeSeries. is creat a new table from csv file.
 * @param fileName
 */
TimeSeries::TimeSeries(char *fileName) {
    std::fstream myfile;
    //open file and read mode.
    myfile.open(fileName, std::ios::in);
    if (myfile.is_open()) {
        std::string line;
        int first_line = 1;
        //go through the lines.
        while (std::getline(myfile, line)) {
            //if it's the first line - we added the data to br the headline of the vector.
            if (first_line) {
                createKeysFromLine(line);
                first_line = 0;
            //if we creat before to the table vector - we just add the data to the existing vectors by order.
            } else {
                addValuesFromLine(line);
            }
        }
    }
    myfile.close();
}

/**
 * This function creat new vectors to the table. the first data in the vectors is the given data.
 * @param line
 */
void TimeSeries::createKeysFromLine(std::string line) {
    size_t pos = 0;
    std::string token;
    std::string delimiter = ",";

    //we split the line and add the data to new vectors and push them into the feature_table.
    while ((pos = line.find(delimiter)) != std::string::npos) {
        token = line.substr(0, pos);
        std::vector<std::string> temp;
        temp.push_back(token);
        feature_table.push_back(temp);
        line.erase(0, pos + delimiter.length());
    }

    //we add one more vector because the last token finished without ',' - so we need to add it anyway.
    std::vector<std::string> temp;
    temp.push_back(line);
    feature_table.push_back(temp);


}

/**
 * This function add values to the existing table by the order they been given.
 * @param line
 */
void TimeSeries::addValuesFromLine(std::string line) {
    int pos = 0;
    for (auto & i : feature_table) {
        int counter = line.find(',',pos);
        std::string temp = line.substr(pos, counter);
        i.push_back(temp);
        line.erase(pos, counter + 1);
    }
}

/**
 * This function return
 * @return const std::vector<std::vector<std::string> >
 */
const std::vector<std::vector<std::string> > TimeSeries::getFeatureTable() const{
    return feature_table;
}