//
// Created by yhood on 31/10/2021.
//

#ifndef DEV_SIMPLEANOMALYDETECTOR_H
#define DEV_SIMPLEANOMALYDETECTOR_H

#include "AnomalyDetector.h"
#include "anomaly_detection_util.h"
#include "TimeSeries.h"
#include <vector>

using std::vector;
using std::string;

struct correlatedFeatures {
    string feature1, feature2; // names of the correlated features
    float corrlation;
    Line lin_reg;
    float threshold;
};

class SimpleAnomalyDetector : public TimeSeriesAnomalyDetector {
public:
    correlatedFeatures c;
    std::vector<correlatedFeatures> normal_model;

    explicit SimpleAnomalyDetector(correlatedFeatures c);

    vector<Point> corrlatedCreatPoints(vector<float>, vector<float>);

    SimpleAnomalyDetector();

    ~SimpleAnomalyDetector() override;

    virtual void learnNormal(const TimeSeries &ts) override;

    virtual vector<AnomalyReport> detect(const TimeSeries &ts);

    virtual vector<correlatedFeatures> getNormalModel();
};

#endif //DEV_SIMPLEANOMALYDETECTOR_H
