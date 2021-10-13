//
// Created by USER on 09/10/2021.
//
#include <valarray>
#include "anomaly_detection_util.h"
#include "Test.h"

bool dif(float x, float y, float d) {
    bool r = std::abs(x - y) <= d;
    return r;
}

void testVar(float **x, float *r, int size, int *sizes) {
    for (int i = 0; i < size; ++i) {
        if (!dif(var(x[i], sizes[i]), r[i], 0.01)) {
            printf("%d ", i);
            printf("var test failed\n");
            return;
        }
    }
    printf("passed all tests for var\n");
}

void testCov(float ***x, float *r, int sizeOfX, int sizeOfInX) {
    for (int i = 0; i < sizeOfX; ++i) {
        if (!dif(cov(x[i][0], x[i][1], sizeOfInX), r[i], 0.001)) {
            printf("%d ", i);
            printf("cov test failed\n");
            return;
        }
    }
    printf("passed all tests for cov\n");
}

void testPearson(float ***x, float *r, int sizeOfX, int sizeOfInX) {
    for (int i = 0; i < sizeOfX; ++i) {
        if (!dif(pearson(x[i][0], x[i][1], sizeOfInX), r[i], 0.001)) {
            printf("%d ", i);
            printf("pearson test failed\n");
            return;
        }
    }
    printf("passed all tests for pearson\n");
}

void test_linear_reg(Point ***listOfListOfPoints, Line **r, int sizeOfList, int sizeOfSubList) {
    for (int i = 0; i < sizeOfList; ++i) {
        Line line = linear_reg(listOfListOfPoints[i], sizeOfSubList);
        if (!dif(line.a, r[i]->a, 0.1) || !dif(line.b, r[i]->b, 0.01)) {
            printf("%d ", i);
            printf("linear reg test failed\n");
            return;
        }
    }
    printf("passed all tests for linear reg\n");

}

int main() {
    float *a = new float[4]{1, 2, 3, 4};
    float *b = new float[5]{55, 885, 52, 529, 7};
    float *c = new float[6]{7, 65, 32, 0, 23, 41};
    float *d = new float[7]{8, 26, 1, 9, 9, 44, 42};
    float *e = new float[8]{562, 23, 20, 765, 323, 36, 2, 9};
    float *f = new float[9]{3, 216, 16, 62, 20, 4, 36, 6, 45};
    float *g = new float[10]{89, 416, 214, 6, 56, 56, 417, 52, 9, 10};
    int *sizes = new int[7]{4, 5, 6, 7, 8, 9, 10};
    float *r = new float[7]{1.25, 120377.44, 467.33333, 263.26531, 78657.25, 4004.6667, 23429.25};
    float **x = new float *[7]{a, b, c, d, e, f, g};
    testVar(x, r, 7, sizes);
    /*******************************************************
    float *h = new float[5]{1, 2, 3, 4, 9};
    float *i = new float[5]{55, 885, 52, 529, 7};
    float *j = new float[5]{7, 65, 32, 0, 23};
    float *k = new float[5]{8, 26, 1, 9, 9};
    float *l = new float[5]{562, 23, 20, 765, 323};
    float *m = new float[5]{3, 216, 16, 62, 20};
    float *n = new float[5]{89, 416, 214, 6, 56};
    float **z = new float *[7]{h, i, j, k, l, m, n};
    float ***y = new float **[7];
    y[0] = new float *[2]{z[0], z[1]};
    y[1] = new float *[2]{z[1], z[2]};
    y[2] = new float *[2]{z[2], z[3]};
    y[3] = new float *[2]{z[3], z[4]};
    y[4] = new float *[2]{z[4], z[5]};
    y[5] = new float *[2]{z[5], z[6]};
    y[6] = new float *[2]{z[6], z[0]};
    r = new float[7]{-329.28, 4184.76, 127.76, -607.96, -9294.44, 9104.72, -175.36};
    testCov(y, r, 7, 5);
    /*******************************************************
    r = new float[7]{-0.3407, 0.5288, 0.6781, -0.2501, -0.4006, 0.7861, -0.4284};
    testPearson(y, r, 7, 5);
    /*******************************************************
    Point **points1 = new Point *[3]{new Point(5, 8), new Point(9, 1), new Point(6, 2)};
    Point **points2 = new Point *[3]{new Point(-5, 0), new Point(5, -1), new Point(454, -2)};
    Point **points3 = new Point *[3]{new Point(16, 58), new Point(91, 11), new Point(62, 20)};
    Point **points4 = new Point *[3]{new Point(5.9, 0.5), new Point(6.1, 155), new Point(6.9, 23.7)};
    Point **points5 = new Point *[3]{new Point(7, 2), new Point(1, 1), new Point(7, 0)};
    Point **points6 = new Point *[3]{new Point(-14, 58), new Point(-7, -13), new Point(585, 74)};
    Point **points7 = new Point *[3]{new Point(175, 16), new Point(16, 17), new Point(157, 72)};
    Point ***listOfListOfPoints = new Point **[7]{points1, points2, points3, points4, points5, points6, points7};
    Line **expected = new Line *[7]{new Line(-1.4231, 13.1538), new Line(-0.003339, -0.4947),
                                    new Line(-0.6448, 65.9925),
                                    new Line(-30.3214, 250.7583), new Line(0, 1), new Line(0.08542, 23.6073),
                                    new Line(0.1448, 18.1991)};

    test_linear_reg(listOfListOfPoints, expected, 7, 3);
    /*******************************************************
    Line *line = new Line(1, 0);
    printf("%f", dev(*new Point(3, 1), *line));
    /*******************************************************
*/
}

