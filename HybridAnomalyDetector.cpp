
#include "HybridAnomalyDetector.h"


HybridAnomalyDetector::HybridAnomalyDetector() {
    // TODO Auto-generated constructor stub


}

HybridAnomalyDetector::~HybridAnomalyDetector() {
    // TODO Auto-generated destructor stub
}

void
HybridAnomalyDetector::initCorrelatedFeatures(const vector<float> &v1, const vector<float> &v2, const string &feature1,
                                              const string &feature2, float corr) {
    if (corr >= init_threshold) {
        SimpleAnomalyDetector::initCorrelatedFeatures(v1, v2, feature1, feature2, corr);
    } else {
        Point **points = hybridCreatPoints(v1, v2);
        Circle min_circle = findMinCircle(points, v1.size());
        normal_model.push_back(initializeCor(feature1, feature2, corr, {}, 0.0, min_circle));
        //Delete all allocations
        for (int i = 0; i < v1.size(); i++) {
            delete[]points[i];
        }
        delete[]points;
    }
}

bool HybridAnomalyDetector::isInTerms(float p) {
    if (p >= min_threshold)
        return true;
    return false;
}

Point **HybridAnomalyDetector::hybridCreatPoints(vector<float> x, vector<float> y) {
    int size = int(x.size());
    /**
     * NEED TO DELETE
     */
    auto **points = new Point *[size];
    /**
     * NEED TO DELETE NEW POINT
     */
    for (int i = 0; i < size; i++) {
        points[i] = new Point(x[i], y[i]);
    }
    return points;
}

bool HybridAnomalyDetector::detectReportTerms(float threshold, const Point &p, const correlatedFeatures &c) {
    if(c.corrlation>=init_threshold){
        return SimpleAnomalyDetector::detectReportTerms(threshold,p,c);
    }
    Point circle_point = c.circle.center;
    double d = sqrt(pow((circle_point.x - p.x), 2) + pow((circle_point.y - p.y), 2));
    if (d > (c.circle.radius*1.1))
        return true;
    return false;
}

correlatedFeatures
HybridAnomalyDetector::initializeCor(const string &feature1, const string &feature2, float corrlated, Line line_reg,
                                     float threshold, Circle c) {
    correlatedFeatures cor = {feature1, feature2, corrlated, line_reg, threshold,
                              c};
    return cor;
}



