//
// Created by Jakub Begera on 03.01.18.
//

#include <math.h>
#include "GifBuilder.h"


GifBuilder::GifBuilder(double maxAbsXY, const char *outputFile, int iterations) : maxAbsXY(maxAbsXY),
                                                                                  outputFile(outputFile),
                                                                                  iterations(iterations) {
    this->writer = new GifWriter();
    this->imageSize = 4 * GIF_SIZE * GIF_SIZE; // 4 bytes per pixel (RGBA)
    this->frames = new uint8_t[this->imageSize];
    GifBegin(this->writer, outputFile, GIF_SIZE, GIF_SIZE, GIF_DELAY);
}

void GifBuilder::addFrame(const vector<MassPoint *> &points) {

    for (int i = 0; i < this->imageSize; ++i) {
        this->frames[i] = 0;
    }


    for (int i = 0; i < points.size(); ++i) {
        MassPoint *mp = points[i];
        // skip out of view mass points
        if (mp->x > maxAbsXY || mp->y > maxAbsXY || mp->x < -maxAbsXY || mp->y < -maxAbsXY) continue;
        auto x = (int) ((((mp->x / maxAbsXY) + 1.0) / 2.0) * GIF_SIZE);
        auto y = (int) ((((mp->y / maxAbsXY) + 1.0) / 2.0) * GIF_SIZE);

        if (mp->weight > 1e35) {
            // sun
            for (int j = -GIF_SUN_DIAMETER; j <= GIF_SUN_DIAMETER; ++j) {
                for (int k = -GIF_SUN_DIAMETER; k <= GIF_SUN_DIAMETER; ++k) {
                    if (sqrt(j*j + k*k) <= GIF_SUN_DIAMETER) {
                        printPoint(j, k, 250, 250, 5, 0);
                    }
                }
            }
        } else{
            printPoint(x, y, 255, 255, 255, 0);
        }
    }
    GifWriteFrame(writer, frames, GIF_SIZE, GIF_SIZE, GIF_DELAY, 8, true);
}

void GifBuilder::done() {
    GifEnd(writer);
}

void GifBuilder::printPoint(int x, int y, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    uint32_t index = static_cast<uint32_t>(4 * (x + y * GIF_SIZE));

    if (index + 3 <= imageSize) {
        frames[index] = r;
        frames[index + 1] = g;
        frames[index + 2] = b;
        frames[index + 3] = a;
    }
}
