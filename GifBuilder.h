//
// Created by Jakub Begera on 03.01.18.
//

#ifndef GENERATOR_GIFBUILDER_H
#define GENERATOR_GIFBUILDER_H

#include <vector>
#include "gif.h"
#include "MassPoint.h"
#include "settings.h"

using namespace std;

class GifBuilder {
public:
    GifBuilder(double maxAbsXY, const char *outputFile, int iterations);
    void addFrame(const vector<MassPoint *> &points);
    void done();
private:
    double maxAbsXY;
    const char *outputFile;
    int iterations;
    GifWriter *writer;
    int imageSize;
    uint8_t* frames;
    void printPoint(int x, int y);
};


#endif //GENERATOR_GIFBUILDER_H
