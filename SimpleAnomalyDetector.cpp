//
// Created by yhood on 31/10/2021.
//
#include "SimpleAnomalyDetector.h"

SimpleAnomalyDetector::SimpleAnomalyDetector(correlatedFeatures cor) : TimeSeriesAnomalyDetector(), cor(cor) {}

SimpleAnomalyDetector::~SimpleAnomalyDetector() {
}


vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries &ts) {}

std::vector<correlatedFeatures> SimpleAnomalyDetector::getNormalModel() {
    return normal_model;
}

SimpleAnomalyDetector::SimpleAnomalyDetector() {

}

/**
 * Assisted function to creat new points vector for corrlation vectors X and Y
 * @param x-- first feature vector
 * @param y second feature vector
 * @return new points' vector
 */
std::vector<Point> SimpleAnomalyDetector::corrlatedCreatPoints(std::vector<double> x, vector<double> y) {
    std::vector<Point> v_point;
    for (int i = 0; i < x.size(); i++) {
        auto *p = new Point(x[i], y[i]);
        v_point[i] = *p;
    }
    return v_point;
}

void SimpleAnomalyDetector::learnNormal(const TimeSeries &ts) {
    const vector<vector<string>> feature_table = ts.getFeatureTable();
    float p;
    float m;
    int c;
    for (int i = 0; i < feature_table.size(); i++) {
        m = 0;
        c = -1;
        for (int j = i + 1; j < feature_table.size(); j++) {
            vector<double> v1 = (const vector<double> &) feature_table[i];
            vector<double> v_temp2 = (const vector<double> &) feature_table[j];
            float temp = pearson(reinterpret_cast<float *>(v1.data()), reinterpret_cast<float *>(v_temp2.data()),
                                 (signed) feature_table[i].size());
            p = fabsf(temp);
            if ((p) > 0) {
                m = p;
                c = j;
            }
            if (c != (-1)) {
                // corolation=m.
                //feature1= A[i] feature2 =A[c]
                //line = line_reg(
                vector<double> v2 = (const vector<double> &) feature_table[c];
                std::vector<Point> v_point = corrlatedCreatPoints(v1, v2);
                //find threshold
            }
        }
    }

}
