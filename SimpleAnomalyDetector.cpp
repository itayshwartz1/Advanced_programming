//
// Created by yhood on 31/10/2021.
//
#include "SimpleAnomalyDetector.h"

SimpleAnomalyDetector::SimpleAnomalyDetector(correlatedFeatures c) : TimeSeriesAnomalyDetector(), c(c) {}

SimpleAnomalyDetector::~SimpleAnomalyDetector() {
}


vector <AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries &ts) {}

vector <correlatedFeatures> SimpleAnomalyDetector::getNormalModel() {
}

SimpleAnomalyDetector::SimpleAnomalyDetector() {

}

void SimpleAnomalyDetector::learnNormal(const TimeSeries &ts) {
    

}
