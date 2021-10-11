#include <iostream>

// returns the variance of X and Y
float var(float *x, int size) {

}

/**
 * calculate life expectancy
 */
float expectancy(float *x, int size) {
    float sum = 0;
    for (int i = 1; i <= size; i++) {
        sum += x[i];
    }
    return (sum) / (float) size;
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}

/**
 * @author Itay Shwartz
 * @date 18:06
The cov function return the covariance of variables X and Y.
 **/
float cov(float *x, float *y, int size) {
    //This loop creat a new array from x and y, means xy.
    float xy[size];
    for (int i = 0; i < size; i++) {
        xy[i] = x[i] * y[i];
    }
    float * ptr_xy = xy;
    //Return the covariance.
    return expectancy(ptr_xy , size) - expectancy(x, size) * expectancy(y, size);
}
