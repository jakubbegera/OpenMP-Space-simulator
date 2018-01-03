//
// Created by Jakub Begera on 03.01.18.
//

#ifndef GENERATOR_SPACESIMULATOR_H
#define GENERATOR_SPACESIMULATOR_H

#include <vector>
#include "MassPoint.h"
#include "GifBuilder.h"

using namespace std;

class SpaceSimulator {
public:
    SpaceSimulator(const int numberOfIterations, const vector<MassPoint *> &massPoints, GifBuilder &gifBuilder,
                   const char *outputPath, const double maxAbsXY);

    void execute();
private:
    const int numberOfIterations;
    vector<MassPoint*> massPoints;
    GifBuilder gifBuilder;
    const char *outputPath;
    const double maxAbsXY;
    void doIteration();
};


#endif //GENERATOR_SPACESIMULATOR_H
