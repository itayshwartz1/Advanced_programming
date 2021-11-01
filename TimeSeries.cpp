//
// Created by itay2 on 31/10/2021.
//

#include "TimeSeries.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

TimeSeries::TimeSeries(char *fileName) {
    std::fstream myfile;
    //open file and read mode.
    myfile.open(fileName, std::ios::in);
    if (myfile.is_open()) {
        std::string line;
        int first_line = 1;
        //go through the lines.
        while (std::getline(myfile, line)) {
            if (first_line) {
                createKeysFromLine(line);
                first_line = 0;
            } else {
                addValuesFromLine(line);
            }
        }
    }
    myfile.close();
}

void TimeSeries::createKeysFromLine(std::string line) {
    size_t pos = 0;
    std::string token;
    std::string delimiter = ",";
    while ((pos = line.find(delimiter)) != std::string::npos) {
        token = line.substr(0, pos);
        std::vector<std::string> temp;
        temp.push_back(token);
        feature_table.push_back(temp);
        line.erase(0, pos + delimiter.length());
    }
    //we add onw more vector because the last token finished without ',' - so we need to add it anyway.
    std::vector<std::string> temp;
    temp.push_back(line);
    feature_table.push_back(temp);


}

void TimeSeries::addValuesFromLine(std::string line) {
    int pos = 0;
    //not working!!!
    for (int i = 0; i < feature_table.size(); i++) {
        int counter = line.find(',',pos);
        std::string temp = line.substr(pos, counter);
        feature_table[i].push_back(temp);
        line.erase(pos, counter);
    }
}



