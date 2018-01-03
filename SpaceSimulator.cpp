//
// Created by Jakub Begera on 03.01.18.
//

#include "SpaceSimulator.h"

SpaceSimulator::SpaceSimulator(const vector<MassPoint *> &massPoints, const char *outputPath,
                               const int numberOfIterations) : massPoints(massPoints), outputPath(outputPath),
                                                               numberOfIterations(numberOfIterations) {}

void SpaceSimulator::execute() {
    for (int i = 0; i < numberOfIterations; ++i) {
        doIteration();
    }
}

void SpaceSimulator::doIteration() {
    for (int i = 0; i < massPoints.size(); ++i) {
        MassPoint *&mp = massPoints[i];
        mp->x = mp->x/2;
        mp->y = mp->y/2;
    }

}


