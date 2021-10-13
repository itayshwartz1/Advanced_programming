//
// Created by yhood on 13/10/2021.
//

#include <cmath>
#include "Test_Original.h"
#include "anomaly_detection_util.h"
// Function for calculating variance
float internetVariance(float a[], int n) {
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

void testVar(float** bigArr){
    for(int i = 0; i< sizeof(bigArr)/sizeof(float ); i++) {
        if(internetVariance(bigArr[i], sizeof(bigArr[i])/sizeof(float)) != ) {

        }
    }
}
int main(){
    float *a = new float[4]{1, 2, 3, 4};
    float *b = new float[5]{55, 885, 52, 529, 7};
    float *c = new float[6]{7, 65, 32, 0, 23, 41};
    float *d = new float[7]{8, 26, 1, 9, 9, 44, 42};
    float *e = new float[8]{562, 23, 20, 765, 323, 36, 2, 9};
    float *f = new float[9]{3, 216, 16, 62, 20, 4, 36, 6, 45};
    float *g = new float[10]{89, 416, 214, 6, 56, 56, 417, 52, 9, 10};
    float **bigArr = new float *[7]{a, b, c, d, e, f, g};
}
