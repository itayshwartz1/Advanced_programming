//
// Created by itay2 on 31/10/2021.
//

#ifndef DEV_TIMESERIES_H
#define DEV_TIMESERIES_H


#include <iostream>
#include <fstream>
using namespace std;

class TimeSeries{
    const char **featureTable;

    TimeSeries(char* fileName){
        std::ifstream myFile;
        myFile.open(fileName);
        //while there is something in the file keep reading it.
        string line;
        while(myFile.good())
            //read the text until the comma and store it to line.
            myFile.(fileName, line, ',');
    }

//    ~TimeSeries(){
//
//    }
//    double getValueInFeature(int i, int j){
//
//    }

    const char** getFeatureTable(){
        return featureTable;
    }


};

#endif //DEV_TIMESERIES_H
