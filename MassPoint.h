//
// Created by Jakub Begera on 03.01.18.
//

#ifndef GENERATOR_POINTMASS_H
#define GENERATOR_POINTMASS_H

#include <cmath>
#include "settings.h"
#if PARALLEL
#include <omp.h>
#endif


class MassPoint {
public:
    double x;
    double y;
    const double weight;
    double moveX;
    double moveY;

    MassPoint(double x, double y, const double weight);
    double dist(MassPoint *mp);
    double distX(MassPoint *mp);
    double distY(MassPoint *mp);
    double force(MassPoint *mp);

    void doMove();
    void initInitialMove(const double maxAbsXY);
};


#endif //GENERATOR_POINTMASS_H
