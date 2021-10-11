#include <iostream>
#include <cmath>
#include "anomaly_detection_util.h"


/**
 * @author Roei Gehassi
 * @date 11/10/21 18:39
 * calculate life expectancy
 * return expectancy
 */
float expectancy(float *x, int size) {
    float sum = 0;
    /*
     * this loop sums the values of the array.
     */
    for (int i = 1; i <= size; i++) {
        sum += x[i];
    }
    return (sum) / (float) size;
}

/**
 *  * @author Roei Gehassi
 * @date 11/10/21 18:39
 * @param x
 * @param size
 * @return the variance of X and Y
 */
float var(float *x, int size) {
    float sum = 0, avg;
    for (int i = 1; i < size; i++) {
        sum += (x[i] * x[i]);
    }
    avg = sum / (float) size;
    return avg - expectancy(x, size);
}

/**
 * @author Itay Shwartz
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
    return cov(x, y, size) / (sqrtf(var(x, size)) * sqrtf(var(y, size)));
}

/**
 *  performs a linear regression and return s the line equation
 *  @author Roei Gehassi
 *  @date 11/10/21 19:47
 * @param points
 * @param size
 * @return
 */
Line linear_reg(Point **points, int size) {
    float xArr[size], yArr[size];
    for (int i = 0; i < size; i++) {
        xArr[i] = points[i]->getX();
        yArr[i] = points[i]->getY();
    }
    float a, b;
    a = cov(xArr, yArr, size) / var(xArr, size);
    b = var(yArr, size) - a * var(xArr, size);
    return Line(a, b);
}