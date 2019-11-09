<<<<<<< HEAD
#include <iomanip>
#include <iostream>
#include <math.h>
#include <vector>
using namespace std;

// This is only necessary in the Southern California qualifiers.
// Kattis online judge did not require rounding. 
double round(double value) {
    return (double)((int)(value * 100 + 0.5)) / 100;
}

// Derivations done at the bottom, to save some commenting space. :)
//
// For every side of our "coin" polygon:
// - Make this our "axis" by finding an equation for the line, L, made by this pair.
// - Slope-intercept involves solving, so we have to use Ax + By + C = 0.
// - For every other point, P:
// --- Get the maximum distance from P to L.
// ----- [Context] This is how wide the slot must be to fit the coin if it is laying on this side.
// ----- If you are confused, draw it! An isosceles triangle is the easiest example.
// --- Store the minimum of these distances.
// ----- [Context] This is the smallest width of the slot.
// - Return the minimum distance.
int main() {
    int sides;
    cin >> sides;

    vector<pair<double, double>> vertices;

    for (int i = 0; i < sides; i++) {
        double x;
        double y;
        cin >> x >> y;
        vertices.push_back(make_pair(x, y));
    }

    // Some number larger than what the answer actually is, as a placeholder
    double minOfMaxDistances = 69420.5318008;

    // Get the slot width based on if the coin was laying on this side.
    // Then, adjust our answer if it is the smallest width.
    for (int i = 0; i < sides; i++) {
        double x0 = vertices[i].first;
        double y0 = vertices[i].second;
        double x1 = vertices[(i + 1) % sides].first;
        double y1 = vertices[(i + 1) % sides].second;

        double A = y0 - y1;
        double B = x1 - x0;
        double C = x0 * y1 - x1 * y0;

        double denominator = sqrt(A * A + B * B);

        double maxDistance = 0;

        // Iterate all other points and determine what the slot width has to be.
        for (int j = (i + 2) % sides; j != i; j = (j + 1) % sides) {
            double x2 = vertices[j].first;
            double y2 = vertices[j].second;
            double currentDistance = abs(A * x2 + B * y2 + C) / denominator;

            if (currentDistance > maxDistance)
                maxDistance = currentDistance;
        }

        if (maxDistance < minOfMaxDistances)
            minOfMaxDistances = maxDistance;
    }

    cout << minOfMaxDistances << endl;

    return 0;
}

// STEP 1
// Geometrically represent a side on a given polygon.
//
// For two arbitrary points P0 (x0, y0) and P1 (y0, y1) on the polygon:
// (y - y0) = (y1 - y0) / (x1 - x0) * (x - x0).
// 
// Expanding, simplifying, and moving all to one side yields:
// (y0 - y1)x + (x1 - x0)y + x0y1 - x1y0 = 0.
//
// Matching the form Ax + By + C = 0 (Standard form of a line):
// A = y0 - y1
// B = x1 - x0
// C = x0y1 - x1y0
//
// 
// STEP 2
// Get the maximum distance [slot width] from each point to this side.
// https://en.wikipedia.org/wiki/Distance_from_a_point_to_a_line
// 
// Any proof would work out if you were deriving from scratch.
// The formula runs into an issue if sqrt(A*A + B*B) is 0.
// If we ever got an error with the judge after submission, we should check this first.
=======
#include <iomanip>
#include <iostream>
#include <math.h>
#include <vector>
using namespace std;

// Only needed for the Southern California qualifiers version, where the answer needs to be rounded.
double round(double value) {
    return (double)((int)(value * 100 + 0.5)) / 100;
}

// For every side of our "coin" polygon:
// - Make this our "axis" by finding an equation for the line, L, made by this pair.
// - Slope-intercept involves solving, so we have to use Ax + By + C = 0.
// - For every other point, P:
// --- Get the maximum distance from P to L.
// ----- [Context] This is how wide the slot must be to fit the coin if it is laying on this side.
// ----- If you are confused, draw it! An isosceles triangle is the easiest example.
// --- Store the minimum of these distances.
// ----- [Context] This is the smallest width of the slot.
// - Return the minimum distance.
int main() {
    int sides;
    cin >> sides;

    vector<pair<double, double>> vertices;

    for (int i = 0; i < sides; i++) {
        double x;
        double y;
        cin >> x >> y;
        vertices.push_back(make_pair(x, y));
    }

    // Some number larger than what the answer actually is, as a placeholder
    double minOfMaxDistances = 69420;

    for (int i = 0; i < sides; i++) {
        double x0 = vertices[i].first;
        double y0 = vertices[i].second;
        double x1 = vertices[(i + 1) % sides].first;
        double y1 = vertices[(i + 1) % sides].second;

        double A = y0 - y1;
        double B = x1 - x0;
        double C = x0 * y1 - x1 * y0;

        double denominator = sqrt(A * A + B * B);

        double maxDistance = 0;

        for (int j = (i + 2) % sides; j != i; j = (j + 1) % sides) {
            double x2 = vertices[j].first;
            double y2 = vertices[j].second;
            double currentDistance = abs(A * x2 + B * y2 + C) / denominator;

            if (currentDistance > maxDistance)
                maxDistance = currentDistance;
        }

        if (maxDistance < minOfMaxDistances)
            minOfMaxDistances = maxDistance;
    }

    cout << minOfMaxDistances << endl;

    return 0;
}
>>>>>>> 8017de3cbe7acfb1489a6e0a5d2238ca100bf4bb
