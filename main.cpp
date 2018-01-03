#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include "MassPoint.h"
#include "SpaceSimulator.h"

using namespace std;

#define DEBUG true
#define GRAVITATIONAL_CONSTANT 6.67408e-11
#define GIF_STEP 5
#define GIF_DELAY 5

vector<MassPoint *> massPoints;
double maxX = 0;
double maxY = 0;
double minX = 0;
double minY = 0;

void readInput(const string &file) {
    ifstream inputStream;
    inputStream.open(file);
    string s;
    getline(inputStream, s);
    const int numberOfPoints = stoi(s);
    cout << "Number of mass points: " << numberOfPoints << endl;
    for (int i = 0; i < numberOfPoints; ++i) {
        getline(inputStream, s, ' ');
        double x = stod(s);
        if (x > maxX) {
            maxX = x;
        } else if (x < minX) {
            minX = x;
        }
        getline(inputStream, s, ' ');
        double y = stod(s);
        if (y > maxY) {
            maxY = y;
        } else if (y < minY) {
            minY = y;
        }
        getline(inputStream, s, (char)'\n');
        double weight = stod(s);
        MassPoint *point = new MassPoint(x, y, weight);
        massPoints.push_back(point);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        cerr << "Not enough arguments given! Expected:\n[0] input file\n[1] output file\n[2] number of iterations"
             << endl;
        return 1;
    }
    const char *inputPath = argv[1];
    const char *outputPath = argv[2];
    const int numberOfIterations = stoi(argv[3]);

    readInput(inputPath);
    SpaceSimulator spaceSimulator(massPoints, outputPath, numberOfIterations);
    chrono::high_resolution_clock::time_point startTimestamp = chrono::high_resolution_clock::now();
    spaceSimulator.execute();
    chrono::high_resolution_clock::time_point endTimestamp = chrono::high_resolution_clock::now();
    cout << "Elapsed time: " << chrono::duration_cast<chrono::duration<double>>(endTimestamp - startTimestamp).count()
         << " s" << endl;
    return 0;
}