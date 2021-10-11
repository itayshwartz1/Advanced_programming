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
