//
// Created by yhood on 31/10/2021.
//
#include "SimpleAnomalyDetector.h"

SimpleAnomalyDetector::SimpleAnomalyDetector(correlatedFeatures c) : TimeSeriesAnomalyDetector(), c(c) {}

SimpleAnomalyDetector::~SimpleAnomalyDetector() {
}


vector <AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries &ts) {}

std::vector <correlatedFeatures> SimpleAnomalyDetector::getNormalModel() {
    return normalModel;
}

SimpleAnomalyDetector::SimpleAnomalyDetector() {

}

/**
 * Assisted function to creat new points vector for corrlation vectors X and Y
 * @param x-- first feature vector
 * @param y second feature vector
 * @return new points' vector
 */
std::vector <Point> SimpleAnomalyDetector::corrlationCreatPoints(std::vector<float> x, vector<float> y) {
    std::vector <Point> v_point;
    for (int i = 0; i < x.capacity(); i++) {
        auto* p = new Point(x[i], y[i]);
        v_point[i] = *p;
    }
    return v_point;
}

void SimpleAnomalyDetector::learnNormal(const TimeSeries &ts) {
    const vector <vector<string>> feature_table = ts.getFeatureTable();



}

vector<Point> SimpleAnomalyDetector::corrlatedCreatPoints(vector<float>, vector<float>) {
    return vector<Point>();
}
