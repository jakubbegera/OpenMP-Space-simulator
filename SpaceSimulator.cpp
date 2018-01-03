//
// Created by Jakub Begera on 03.01.18.
//

#include "SpaceSimulator.h"

SpaceSimulator::SpaceSimulator(const int numberOfIterations, const vector<MassPoint *> &massPoints,
                               GifBuilder &gifBuilder, const char *outputPath) : numberOfIterations(
        numberOfIterations), massPoints(massPoints), gifBuilder(gifBuilder), outputPath(outputPath) {}

void SpaceSimulator::execute() {
    for (int i = 0; i < numberOfIterations; ++i) {
        doIteration();
        gifBuilder.addFrame(massPoints, i);
    }
    gifBuilder.done();
}

void SpaceSimulator::doIteration() {
    for (int i = 0; i < massPoints.size(); ++i) {
        MassPoint *&mp = massPoints[i];
        mp->x = mp->x/2;
        mp->y = mp->y/2;
    }

}


