//
// Created by Jakub Begera on 03.01.18.
//

#ifndef GENERATOR_SPACESIMULATOR_H
#define GENERATOR_SPACESIMULATOR_H

#include <vector>
#include "MassPoint.h"

using namespace std;

class SpaceSimulator {
public:
    SpaceSimulator(const vector<MassPoint *> &massPoints, const char *outputPath, const int numberOfIterations);

    void execute();
private:
    vector<MassPoint*> massPoints;
    const char *outputPath;
    const int numberOfIterations;
    void doIteration();
};


#endif //GENERATOR_SPACESIMULATOR_H
