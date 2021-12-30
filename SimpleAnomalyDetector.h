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
#include "minCircle.h"
#include <cmath>
using std::vector;
using std::string;

struct correlatedFeatures {
    string feature1, feature2; // names of the correlated features
    float corrlation;
    Line lin_reg;
    float threshold;
    Circle circle;

};

class SimpleAnomalyDetector : public TimeSeriesAnomalyDetector {
public:

    std::vector<correlatedFeatures> normal_model;

    SimpleAnomalyDetector();

    SimpleAnomalyDetector(float init_threshold) : init_threshold(init_threshold){};

    virtual vector<Point *> corrlatedCreatPoints(vector<float>, vector<float>);


    ~SimpleAnomalyDetector() override;

    virtual void learnNormal(const TimeSeries &ts) override;

    virtual vector<AnomalyReport> detect(const TimeSeries &ts) override;

    virtual vector<correlatedFeatures> getNormalModel();

    /**
     * check terms of threshold
     * @param p point
     * @return true or false
     */
    virtual bool isInTerms(float p);

    /**
     * Function initialize correlated struct under terms of different threshold, depends on the inherit class
     * @param v1 first vector
     * @param v2 second vector
     * @param feature1 string name of the first feature
     * @param feature2 string name of the second feature
     * @param corr the correlation
     */
    virtual void initCorrelatedFeatures(const vector<float> &v1, const vector<float> &v2,
                                        const string &feature1, const string &feature2, float corr);

    static float detectThreshold(const vector<Point *> &points, Line line);

    virtual correlatedFeatures initializeCor(const string &feature1, const string &feature2, float corrlated,
                                             Line line_reg, float threshold, Circle c);

    virtual bool detectReportTerms(float threshold, const Point &p, const correlatedFeatures &c);


    float init_threshold = 0.9;
};

#endif //DEV_SIMPLEANOMALYDETECTOR_H
