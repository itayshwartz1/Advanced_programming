#include <iostream>
#include <cmath>
#include "anomaly_detection_util.h"


/**
 * @date 11/10/21 18:39
 * calculate life expectancy
 * return expectancy
 */
float expectancy(float *x, int size) {
    if (size <= 0) {
        return 0;
    }
    // this loop sums the values of the array.
    float sum = 0;
    for (int i = 1; i <= size; i++) {
        sum += x[i];
    }
    return (float) sum / (float) size;
}

/**
 * @date 11/10/21 18:39
 * @param x
 * @param size
 * @return the variance of X and Y
 */
float var(float *x, int size) {
    if (size <= 0) {
        return 0;
    }
    float sum = 0;
    for (int i = 0; i < size; i++) {
        sum += (x[i] * x[i]);
    }
    float avg = sum / (float) size;
    return avg - powf(expectancy(x, size), 2);
}

/**
 * @date 11/10
 * @param x, y, size
 * The cov function return the covariance of variables X and Y. 𝑐𝑜𝑣(𝑋, 𝑌) = 𝐸((𝑋 − 𝐸(𝑋))(𝑌 − 𝐸(𝑌)).
 * @return the covariance.
 **/
float cov(float *x, float *y, int size) {
    //This loop creat a new array from x and y, means xy...
    float xy[size];
    for (int i = 0; i < size; i++) {
        xy[i] = x[i] * y[i];
    }
    float *ptr_xy = xy;
    //Return the covariance.
    return expectancy(ptr_xy, size) - expectancy(x, size) * expectancy(y, size);
}

/**
 * returns the Pearson correlation coefficient of X and Y
 * @param x
 * @param y
 * @param size
 */
float pearson(float *x, float *y, int size) {
    if (size <= 0) {
        return 0;
    }
    return cov(x, y, size) / (sqrtf(var(x, size)) * sqrtf(var(y, size)));
}

/**
 * performs a linear regression and return s the line equation
 * @date 12/10/21 13:10
 * @param points, size
 * @return Line.
 */
Line linear_reg(Point **points, int size) {
    if (size <= 0) {
        return // what we should return???
    }
    float xArr[size], yArr[size];
    for (int i = 0; i < size; i++) {
        xArr[i] = points[i]->getX();
        yArr[i] = points[i]->getY();
    }
    float covariance = cov(xArr, yArr, size);
    float variance = var(xArr, size);
    if ((covariance || variance) == 0) {
        return Line(0, var(yArr, size));
    }
    float a = covariance / variance;
    float b = var(yArr, size) - a * variance;
    return Line(a, b);
}


/**
 * returns the deviation between point p and the line.
 * @author Roei and Itay
 * @date19:55 11/10/21
 * @param p
 * @param l
 * @return
 */
float dev(Point p, Line l) {
    return fabsf(p.getY() - l.f(p.getX()));
}

/**
 * returns the deviation between point p and the line equation of the points
 * @param p
 * @param points
 * @param size
 * @return
 */
float dev(Point p, Point **points, int size) {
    return dev(p, linear_reg(points, size));
}