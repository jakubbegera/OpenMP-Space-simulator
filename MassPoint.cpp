//
// Created by Jakub Begera on 03.01.18.
//

#include "MassPoint.h"

MassPoint::MassPoint(double x, double y, const double weight) : x(x), y(y), weight(weight) {

}

double MassPoint::dist(MassPoint *mp) {
    return std::sqrt((x - mp->x) * (x - mp->x) + (y - mp->y) * (y - mp->y));
}

double MassPoint::distX(MassPoint *mp) {
    return mp->x - x;
}

double MassPoint::distY(MassPoint *mp) {
    return mp->y - y;
}

double MassPoint::force(MassPoint *mp) {
    double d = dist(mp);
    return (GRAVITATIONAL_CONSTANT * this->weight * mp->weight) / (d * d);
}

void MassPoint::doMove() {
    x+=moveX * TIME_CONSTANT;
    y+=moveY * TIME_CONSTANT;
}
