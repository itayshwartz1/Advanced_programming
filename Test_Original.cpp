//
// Created by yhood on 13/10/2021.
//

#include <cmath>
#include "Test_Original.h"
// Function for calculating variance
float internetVariance(int a[], int n) {
    // Compute mean (average of elements)
    int sum = 0;
    for (int i = 0; i < n; i++)
        sum += a[i];
    double mean = (double)sum /
                  (double)n;

    // Compute sum squared
    // differences with mean.
    double sqDiff = 0;
    for (int i = 0; i < n; i++)
        sqDiff += (a[i] - mean) *
                  (a[i] - mean);
    return sqDiff / n;
}

void testVar(float** bArr){


}
//