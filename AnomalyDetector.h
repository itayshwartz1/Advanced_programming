/**
 * Name: Roei Gehassi and Itay Shwartz
 * ID: 208854754 and 318528171
 */
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
    virtual void learnNormal(const TimeSeries &ts) = 0;

    virtual vector<AnomalyReport> detect(const TimeSeries &ts) = 0;

    virtual ~TimeSeriesAnomalyDetector() {}
};

#endif //DEV_ANOMALYDETECTOR_H
