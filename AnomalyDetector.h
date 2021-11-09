
#ifndef DEV_ANOMALYDETECTOR_H
#define DEV_ANOMALYDETECTOR_H

#include "timeseries.h"
#include <vector>
#include <string>

using std::string;
using std::vector;

class AnomalyReport {
public:
    const string description;
    const long timeStep;

    AnomalyReport(string description, long timeStep) :
            description(description), timeStep(timeStep) {}
};

class TimeSeriesAnomalyDetector {
public:
    virtual void learnNormal(const timeseries &ts) = 0;

    virtual vector<AnomalyReport> detect(const timeseries &ts) = 0;

    virtual ~TimeSeriesAnomalyDetector() {}
};

#endif //DEV_ANOMALYDETECTOR_H
