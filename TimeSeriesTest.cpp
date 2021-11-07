//
// Created by itay2 on 31/10/2021.
//

#include "TimeSeries.h"
#include "SimpleAnomalyDetector.h"

int main(int argc, char **argv) {
    auto *timeSeries = new TimeSeries(argv[1]);
    auto *detector = new SimpleAnomalyDetector();
    detector->learnNormal(*timeSeries);
}
