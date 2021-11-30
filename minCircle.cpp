#include "minCircle.h"
// C++ program to find the minimum enclosing
// circle for N integer points in a 2-D plane
#include <iostream>
#include <math.h>
#include <vector>


// Defining infinity
#define INF  1e18


// Function to return the euclidean distance
// between two points
double dist(const Point &a, const Point &b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

// Function to check whether a point lies inside
// or on the boundaries of the circle
bool is_inside(const Circle &c, const Point &p) {
    return dist(c.center, p) <= c.radius;
}


// The following two functions are the functions used
// To find the equation of the circle when three
// points are given.

// Helper method to get a circle defined by 3 points
Point get_circle_center(double bx, double by,
                        double cx, double cy) {
    double B = bx * bx + by * by;
    double C = cx * cx + cy * cy;
    double D = bx * cy - by * cx;
    return {(float) ((cy * B - by * C) / (2 * D)),
            (float) ((bx * C - cx * B) / (2 * D))};
}

// Function to return a unique circle that intersects
// three points
Circle circle_from(const Point &A, const Point &B,
                   const Point &C) {
    Point I = get_circle_center(B.x - A.x, B.y - A.y,
                                C.x - A.x, C.y - A.y);
    I.x += A.x;
    I.y += A.y;
    return {I, (float) dist(I, A)};
}

// Function to return the smallest circle
// that intersects 2 points
Circle circle_from(const Point &A, const Point &B) {
    // Set the center to be the midpoint of A and B
    Point C = {(A.x + B.x) / 2, (A.y + B.y) / 2};

    // Set the radius to be half the distance AB
    return {C, (float) (dist(A, B) / 2)};
}

// Function to check whether a circle encloses the given points
bool is_valid_circle(const Circle &c, const vector<Point> &P) {

    // Iterating through all the points to check
    // whether the points lie inside the circle or not
    for (const Point &p: P)
        if (!is_inside(c, p))
            return false;
    return true;
}

// Function to return find the minimum enclosing
// circle from the given set of points
Circle minimum_enclosing_circle(const vector<Point> &P) {

    // To find the number of points
    int n = (int) P.size();

    if (n == 0)
        return {{0, 0}, 0};
    if (n == 1)
        return {P[0], 0};

    // Set initial MEC to have infinity radius
    Circle mec = {{0, 0}, INF};

    // Go over all pair of points
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {

            // Get the smallest circle that
            // intersects P[i] and P[j]
            Circle tmp = circle_from(P[i], P[j]);

            // Update MEC if tmp encloses all points
            // and has a smaller radius
            if (tmp.radius < mec.radius && is_valid_circle(tmp, P))
                mec = tmp;
        }
    }

    // Go over all triples of points
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            for (int k = j + 1; k < n; k++) {

                // Get the circle that intersects P[i], P[j], P[k]
                Circle tmp = circle_from(P[i], P[j], P[k]);

                // Update MEC if tmp encloses all points
                // and has smaller radius
                if (tmp.radius < mec.radius && is_valid_circle(tmp, P))
                    mec = tmp;
            }
        }
    }
    return mec;
}
Circle findMinCircle(Point **points, size_t size) {
    //initialize from points' array to points' vectors
    std::vector<Point> p_vector;
    p_vector.reserve(size);
    for (int i = 0; i < size; i++) {
        p_vector.push_back(*points[i]);
    }
    return minimum_enclosing_circle(p_vector);
}

