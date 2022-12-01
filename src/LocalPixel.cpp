//
// Created by Bogdan on 01-Dec-22.
//

#include "LocalPixel.h"

LocalPixel::LocalPixel(double reference, vector<double> thresholds, double pixelClass) :
        Pixel(reference, std::move(thresholds)) {
    this->pixelClass = pixelClass;
}

double LocalPixel::getPixelClass() const {
    return pixelClass;
}

void LocalPixel::setPixelClass(double value) {
    this->pixelClass = value;
}

string LocalPixel::toString() {
    string result = Pixel::toString();
    result += "C: " + to_string(pixelClass);
    return result;
}