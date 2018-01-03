//
// Created by Jakub Begera on 03.01.18.
//

#ifndef GENERATOR_POINTMASS_H
#define GENERATOR_POINTMASS_H


class MassPoint {
public:
    double x;
    double y;
    const double weight;

    MassPoint(double x, double y, const double weight);

};


#endif //GENERATOR_POINTMASS_H
