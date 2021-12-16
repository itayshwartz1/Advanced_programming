

#ifndef HYBRIDANOMALYDETECTOR_H_
#define HYBRIDANOMALYDETECTOR_H_

#include "SimpleAnomalyDetector.h"
#include "minCircle.h"
#include <array>


using std::vector;

class HybridAnomalyDetector : public SimpleAnomalyDetector {
public:
    float min_threshold = 0.5;

    HybridAnomalyDetector();
    HybridAnomalyDetector(float init_threshold):SimpleAnomalyDetector(init_threshold){};


    virtual ~HybridAnomalyDetector();

    static Point **hybridCreatPoints(vector<float> x, vector<float> y);

    virtual void initCorrelatedFeatures(const vector<float> &v1, const vector<float> &v2,
                                        const string &feature1, const string &feature2, float corr) override;

    virtual bool detectReportTerms(float threshold, const Point &p, const correlatedFeatures &c) override;
    virtual correlatedFeatures initializeCor(const string &feature1, const string &feature2, float corrlated,
                                            Line line_reg, float threshold,Circle c) override;

    bool isInTerms(float p) override;


};

#endif /* HYBRIDANOMALYDETECTOR_H_ */
