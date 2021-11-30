/**
 * Name: Roei Gehassi and Itay Shwartz
 * ID: 208854754 and 318528171
 */
#ifndef DEV_SIMPLEANOMALYDETECTOR_H
#define DEV_SIMPLEANOMALYDETECTOR_H

#include "AnomalyDetector.h"
#include "anomaly_detection_util.h"
#include "timeseries.h"
#include <vector>
#include <algorithm>

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

    std::vector<correlatedFeatures> normal_model;

    SimpleAnomalyDetector();

    static vector<Point *> corrlatedCreatPoints(vector<float>, vector<float>);


    ~SimpleAnomalyDetector() override;

    virtual void learnNormal(const TimeSeries &ts) override;

    virtual vector<AnomalyReport> detect(const TimeSeries &ts) override;

    virtual vector<correlatedFeatures> getNormalModel();

    static float detectThreshold(const vector<Point *> &points, Line line);
};

#endif //DEV_SIMPLEANOMALYDETECTOR_H
