//
// Created by Jakub Begera on 03.01.18.
//

#include <math.h>
#include <iostream>
#include "GifBuilder.h"


GifBuilder::GifBuilder(double maxAbsXY, const char *outputFile, int iterations) : maxAbsXY(maxAbsXY),
                                                                                  outputFile(outputFile),
                                                                                  iterations(iterations) {
    this->writer = new GifWriter();
    this->imageSize = 4 * GIF_SIZE * GIF_SIZE; // 4 bytes per pixel (RGBA)
    this->frames = new uint8_t[this->imageSize];
    #if GIF_GENERATE
        GifBegin(this->writer, outputFile, GIF_SIZE, GIF_SIZE, GIF_DELAY);
    #endif
}

void GifBuilder::addFrame(const vector<MassPoint *> &points) {
    #if GIF_GENERATE
        for (int i = 0; i < this->imageSize; ++i) {
            this->frames[i] = 0;
        }


        for (int i = 0; i < points.size(); ++i) {
            MassPoint *mp = points[i];
            // skip out of view mass points
            if (mp->x > maxAbsXY || mp->y > maxAbsXY || mp->x < -maxAbsXY || mp->y < -maxAbsXY) {
                continue;
            }
            auto x = (int) ((((mp->x + maxAbsXY) / maxAbsXY) / 2.0) * GIF_SIZE);
            auto y = (int) ((((mp->y + maxAbsXY) / maxAbsXY) / 2.0) * GIF_SIZE);

            if (mp->weight > 1e35) {
                // sun
                for (int j = x - GIF_SUN_DIAMETER; j <= x + GIF_SUN_DIAMETER; ++j) {
                    for (int k = y - GIF_SUN_DIAMETER; k <= y + GIF_SUN_DIAMETER; ++k) {
                        if (sqrt((x-j)*(x-j) + (y-k)*(y-k)) <= GIF_SUN_DIAMETER) {
                            printPoint(j, k);
                        }
                    }
                }
            } else {
                printPoint(x, y);
            }
        }
        GifWriteFrame(writer, frames, GIF_SIZE, GIF_SIZE, GIF_DELAY, 8, true);
    #endif
}

void GifBuilder::done() {
    #if GIF_GENERATE
        GifEnd(writer);
    #endif
}

void GifBuilder::printPoint(int x, int y) {
    uint32_t index = static_cast<uint32_t>(4 * (x + y * GIF_SIZE));
    if (index + 3 <= imageSize) {
        frames[index] = 255;
        frames[index + 1] = 255;
        frames[index + 2] = 255;
        frames[index + 3] = 0;
    }
}
