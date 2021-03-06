/**
 * Name: Roei Gehassi and Itay Shwartz
 * ID: 208854754 and 318528171
 */
#include <cmath>
#include <iostream>
#include <cmath>
#include "anomaly_detection_util.h"
#include <exception>


/**
 * calculate life expectancy
 * @date 11/10/21 18:39
 * @param x, size
 * @return expectancy
 */
float expectancy(float *x, int size) {
    if (size <= 0) {
        throw "size = 0 ";
    }
    if (x == nullptr) {
        throw "nullptr Exception";
    }
    // this loop sums the values of the array.
    float sum = 0;
    for (int i = 0; i < size; i++) {
        sum += x[i];
    }
    //preventing deviding by 0.
    if (size == 0)
        return 0;
    return sum / (float) size;
}

/**
 * This function return the variance.
 * @date 11/10/21 18:39
 * @param x, size
 * @return the variance of X and Y
 */
float var(float *x, int size) {
    if (size <= 0) {
        throw "size = 0 ";
    }
    if (x == nullptr) {
        throw "nullptr Exception";
    }
    float sum = 0;
    for (int i = 0; i < size; i++) {
        sum += (x[i] * x[i]);
    }
    float avg = sum / (float) size;
    float exp = expectancy(x, size);
    float temp = powf(exp, 2);
    float res = avg - temp;
    return res;
}

/**
 * The cov function return the covariance of variables X and Y. 𝑐𝑜𝑣(𝑋, 𝑌) = 𝐸((𝑋 − 𝐸(𝑋))(𝑌 − 𝐸(𝑌)).
 * @date 11/10
 * @param x, y, size
 * @return the covariance.
 **/
float cov(float *x, float *y, int size) {
    if (size <= 0) {
        throw "size = 0 ";
    }
    if (x == nullptr || y == nullptr) {
        throw "nullptr Exception";
    }
    //This loop creat a new array from x and y, means xy...
    auto *xy = new float[size];
    for (int i = 0; i < size; i++) {
        float a = x[i];
        float b = y[i];
        float ab = a*b;
        xy[i] =  ab;
    }
    float *ptr_xy = xy;
    double result = expectancy(ptr_xy, size);
    delete[]xy;
    //Return the covariance.
    float a = expectancy(x, size);
    float b = expectancy(y, size);
    float ab = a*b;
    float return_resurl = result - ab;
    return return_resurl;
}

/**
 * returns the Pearson correlation coefficient of X and Y
 * @date 17/10
 * @param x, y, size
 * @return float
 */
float pearson(float *x, float *y, int size) {
    if (size <= 0) {
        throw "size = 0 ";
    }
    if (x == nullptr || y == nullptr) {
        throw "nullptr Exception";
    }
    double cov_res, sqrt_res;
    cov_res = cov(x, y, size);
    sqrt_res = sqrt((double) var(x, size)) * sqrt((double) var(y, size));
    //avoiding deviding by zero.
    if (sqrt_res == 0)
        return 0;
    return (float) (cov_res / sqrt_res);
}

/**
 * performs a linear regression and return s the line equation
 * @date 12/10/21
 * @param points, size
 * @return Line.
 */
Line linear_reg(Point **points, int size) {
    if (size <= 0) {
        throw "size = 0 ";
    }
    if (points == nullptr) {
        throw "nullptr Exception";
    }
    float *xArr = new float[size];
    float *yArr = new float[size];
    for (int i = 0; i < size; i++) {
        xArr[i] = points[i]->x;
        yArr[i] = points[i]->y;
    }

    float covariance = cov(xArr, yArr, size);
    float variance = var(xArr, size);
    if (covariance ==0|| variance == 0) {
        return {0, var(yArr, size)};
    }
    float a = covariance / variance;
    float b = expectancy(yArr, size) - a * expectancy(xArr, size);
    delete[]xArr;
    delete[]yArr;
   return {a, b};
}

/**
 * returns the deviation between point p and the line.
 * @date19:55 11/10/21
 * @param p, l
 * @return float
 */
float dev(Point p, Line l) {
    return fabsf(p.y - l.f(p.x));
}

/**
 * returns the deviation between point p and the line equation of the points
 * @date 17/10
 * @param p, points, size
 * @return float
 */
float dev(Point p, Point **points, int size) {
    if (size <= 0) {
        throw "size = 0 ";
    }
    if (points == nullptr) {
        throw "empty points Exception";
    }
    return dev(p, linear_reg(points, size));
}
