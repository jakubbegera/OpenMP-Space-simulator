#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <cmath>
#include "MassPoint.h"
#include "SpaceSimulator.h"
#if PARALLEL
#include <omp.h>
#endif

using namespace std;


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

double getMaxXY() {
    double max = 0;

    if (abs(minX) > max) {
        max = abs(minX);
    }
    if (abs(minY) > max) {
        max = abs(minY);
    }
    if (abs(maxX) > max) {
        max = abs(maxX);
    }
    if (abs(maxY) > max) {
        max = abs(maxY);
    }

    return max;
}

int main(int argc, char *argv[]) {
    if (argc != 5) {
        cerr << "Not enough arguments given! Expected:\n[0] input file\n[1] output file\n[2] number of iterations\n"
                "[3] initial speed (double <0,1>)"
             << endl;
        return 1;
    }
    const char *inputPath = argv[1];
    const char *outputPath = argv[2];
    const int numberOfIterations = stoi(argv[3]);
    const double initialSpeed = stod(argv[4]);
    if (initialSpeed < 0 || initialSpeed > 1) {
        cerr << "Initial speed is not in interval <0,1>" << endl;
        return 2;
    }

    readInput(inputPath);

    double maxAbsXY = getMaxXY();
    GifBuilder gifBuilder(maxAbsXY, outputPath, numberOfIterations);
    SpaceSimulator spaceSimulator(numberOfIterations, massPoints, gifBuilder, outputPath, maxAbsXY, initialSpeed);

    chrono::high_resolution_clock::time_point startTimestamp = chrono::high_resolution_clock::now();
    spaceSimulator.execute();
    chrono::high_resolution_clock::time_point endTimestamp = chrono::high_resolution_clock::now();

    cout << "Elapsed time: " << chrono::duration_cast<chrono::duration<double>>(endTimestamp - startTimestamp).count()
         << " s" << endl;
    cout << "Input path: " << inputPath << endl;
    cout << "iterations: " << numberOfIterations << endl;
    #if PARALLEL
        cout << "CPUs: " << omp_get_num_procs() << endl;
    #endif
    return 0;
}