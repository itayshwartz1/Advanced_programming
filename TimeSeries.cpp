//
// Created by itay2 on 31/10/2021.
//

#include "TimeSeries.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

TimeSeries::TimeSeries(char* fileName) {
    const std::vector<std::vector<std::string>>feature_table;
    std::ifstream my_File(fileName);

    if (!my_File.is_open()) {
        std::cout << "ERROR" << std::endl;
        exit(1);
    }

    std::string line;
    std::string word;
    while (my_File.good()) {
        std::getline(my_File, line, '\n');
        std::stringstream ss(line);
        std::string word;

        int start = 0;
       std::string del =  ",";
        int end = line.find(',');
        while (end != -1) {
            //add the data.
            //feature_table.push_back()
            start = end + del.size();
            end = line.find(del, start);
        }
    }
    my_File.close();
}


