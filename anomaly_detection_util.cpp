#include <iostream>


/**
 * calculate life expectancy
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

// returns the variance of X and Y
float var(float *x, int size) {
    float sum = 0, avg;
    for (int i = 1; i < size; i++) {
        sum += (x[i] * x[i]);
    }
    avg = sum / (float) size;
    return avg - expectancy(x, size);
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
