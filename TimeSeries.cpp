//
// Created by itay2 on 31/10/2021.
//

#include "TimeSeries.h"

#include <iostream>
#include <fstream>


class TimeSeries{
    char** feature_table;

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


};