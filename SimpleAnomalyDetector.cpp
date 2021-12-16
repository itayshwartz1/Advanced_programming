/**
 * Name: Roei Gehassi and Itay Shwartz
 * ID: 208854754 and 318528171
 */
#include "SimpleAnomalyDetector.h"
#include "AnomalyDetector.h"

SimpleAnomalyDetector::SimpleAnomalyDetector() : TimeSeriesAnomalyDetector() {
    normal_model = {};
}


SimpleAnomalyDetector::~SimpleAnomalyDetector() = default;


vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries &ts) {
    std::vector<Point *> v_points;
    std::vector<float> feature1_x;
    std::vector<float> feature2_y;
    std::vector<AnomalyReport> report_vec = {};
    cout << ("size of report:" + to_string(report_vec.size())+"\n");
    cout<<("Come on\n");
    for (auto &i: normal_model) {
        //define vector X and vector Y to make corrlated point to test later.
        feature1_x = ts.feature_map.at(i.feature1);
        feature2_y = ts.feature_map.at(i.feature2);
        v_points = corrlatedCreatPoints(feature1_x, feature2_y);
        // run over the points and check if there is an exception.
        for (int j = 0; j < v_points.size(); j++) {
            if (detectReportTerms(i.threshold, *v_points[j], i)) {
                std::string description;
                description.append(i.feature1 + "-" + i.feature2);
                AnomalyReport report = {description, j + 1};
                report_vec.push_back(report);
            }
        }
        for (auto &k: v_points) {
            delete k;
        }
    }
    return report_vec;
}

std::vector<correlatedFeatures> SimpleAnomalyDetector::getNormalModel() {
    return normal_model;
}

/**
 * Assisted function to creat new points vector for corrlation vectors X and Y
 * @param x-- first feature vector
 * @param y second feature vector
 * @return new points' vector
 */
std::vector<Point *> SimpleAnomalyDetector::corrlatedCreatPoints(std::vector<float> x, vector<float> y) {
    std::vector<Point *> v_point;
    for (int i = 0; i < x.size(); i++) {
        /***************
         * need to delete the new!
         *****************/
        auto *p = new Point(x[i], y[i]);
        v_point.push_back(p);
    }
    return v_point;
}

void SimpleAnomalyDetector::learnNormal(const TimeSeries &ts) {
    const vector<vector<float>> feature_table = ts.getFeatureTable();
    float p = 0;
    float m = 0;
    int c;
    vector<float> v1, v2;
    for (int i = 0; i < feature_table.size(); i++) {
        m = 0;
        c = -1;
        for (int j = i + 1; j < feature_table.size(); j++) {
            v1 = feature_table[i];
            v2 = feature_table[j];
            float temp = pearson((v1.data()), (v2.data()),
                                 (signed) v1.size());
            p = fabsf(temp);
            if (p > m && isInTerms(p)) {
                m = p;
                c = j;
            }
        }
        //initialize struct
        if (c != (-1)) {
            std::string feature1 = ts.feature_names[i];
            std::string feature2 = ts.feature_names[c];
            v2 = feature_table[c];
            initCorrelatedFeatures(v1, v2, feature1, feature2, m);
        }
    }
}


float SimpleAnomalyDetector::detectThreshold(const vector<Point *> &points, Line line) {
    float max_threshold = 0;
    for (auto i: points) {
        max_threshold = std::max(max_threshold, dev(*i, line));
    }
    // we return the threshold*1.1 as recommended.
    return (float) 1.2 * max_threshold;
}

bool SimpleAnomalyDetector::isInTerms(float p) {
    if (p >= init_threshold)
        return true;
    return false;
}

void
SimpleAnomalyDetector::initCorrelatedFeatures(const vector<float> &v1, const vector<float> &v2, const string &feature1,
                                              const string &feature2, float corr) {
    std::vector<Point *> v_point = corrlatedCreatPoints(v1, v2);
    Line line = linear_reg(v_point.data(), (signed) v_point.size());
    float thershold = detectThreshold(v_point, line);
    normal_model.push_back(initializeCor(feature1, feature2, corr, line,
                                         thershold, {{0, 0}, 0}));
    for (auto &k: v_point) {
        delete k;
    }

}

correlatedFeatures
SimpleAnomalyDetector::initializeCor(const string &feature1, const string &feature2, float corrlated, Line line_reg,
                                     float threshold, Circle c) {
    correlatedFeatures cor = {feature1, feature2, corrlated, line_reg, threshold,
                              {{0, 0}, 0}};
    return cor;
}

bool SimpleAnomalyDetector::detectReportTerms(float threshold, const Point &p, const correlatedFeatures &c) {
    if (threshold < dev(p, c.lin_reg))
        return true;
    return false;
}





