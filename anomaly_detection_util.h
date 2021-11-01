//
// Created by itay2 on 11/10/2021.
//

#ifndef DEV_ANOMALY_DETECTION_UTIL_H
#define DEV_ANOMALY_DETECTION_UTIL_H

#include <cmath>

/**
 * calculate life expectancy
 */
float expectancy(float *x, int size);

// returns the variance of X and Y
float var(float *x, int size);

// returns the covariance of X and Y
float cov(float *x, float *y, int size);

// returns the Pearson correlation coefficient of X and Y
float pearson(float *x, float *y, int size);

class Line {
public:
    float a, b;

    Line() : a(0), b(0) {}

    Line(float a, float b) : a(a), b(b) {}

    float f(float x) {
        return a * x + b;
    }
};

class Point {
public:
    float x, y;

    Point(float x, float y) : x(x), y(y) {}

};

// performs a linear regression and return s the line equation
Line linear_reg(vector<Point>, int size);

// returns the deviation between point p and the line equation of the points
float dev(Point p, Point **points, int size);

// returns the deviation between point p and the line
float dev(Point p, Line l);

#endif //DEV_ANOMALY_DETECTION_UTIL_H
