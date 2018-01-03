//
// Created by Jakub Begera on 03.01.18.
//

#include "GifBuilder.h"


GifBuilder::GifBuilder(double maxAbsXY, const char *outputFile, int iterations) : maxAbsXY(maxAbsXY),
                                                                                  outputFile(outputFile),
                                                                                  iterations(iterations) {
    this->writer = new GifWriter();
    this->imageSize = 4 * GIF_SIZE * GIF_SIZE; // 4 bytes per pixel (RGBA)
    this->frames = new uint8_t[this->imageSize];
    GifBegin(this->writer, outputFile, GIF_SIZE, GIF_SIZE, GIF_DELAY);
}

void GifBuilder::addFrame(const vector<MassPoint *> &points, int iteration) {

    for (int i = 0; i < this->imageSize; ++i) {
        this->frames[i] = 0;
    }


    for (int i = 0; i < points.size(); ++i) {
        MassPoint *mp = points[i];
        // skip out of view mass points
        if (mp->x > maxAbsXY || mp->y > maxAbsXY || mp->x < -maxAbsXY || mp->y < -maxAbsXY) continue;
        auto x = (int) ((((mp->x / maxAbsXY) + 1.0) / 2.0) * GIF_SIZE);
        auto y = (int) ((((mp->y / maxAbsXY) + 1.0) / 2.0) * GIF_SIZE);
        printPoint(x, y);
    }
    GifWriteFrame(writer, frames, GIF_SIZE, GIF_SIZE, GIF_DELAY, 8, true);
}

void GifBuilder::done() {
    GifEnd(writer);
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
