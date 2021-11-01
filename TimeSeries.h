//
// Created by itay2 on 31/10/2021.
//

#ifndef DEV_TIMESERIES_H
#define DEV_TIMESERIES_H


#include <iostream>
#include <fstream>
#include <vector>

using std::string;
using std::vector;


class TimeSeries {
    const vector<vector<string>> feature_table;

    TimeSeries(char *fileName) {
        std::ifstream myFile;
        myFile.open(fileName);
        //while there is something in the file keep reading it.
        string line;
        while (myFile.good())
            //read the text until the comma and store it to line.
            myFile.(fileName, line, ',');
    }

//    ~TimeSeries(){
//
//    }
//    double getValueInFeature(int i, int j){
//
//    }

    const vector<vector<string>>*  getFeatureTable() const{
        return &feature_table;
    }


};

#endif //DEV_TIMESERIES_H
