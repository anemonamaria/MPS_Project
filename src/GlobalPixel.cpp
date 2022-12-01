//
// Created by Bogdan on 01-Dec-22.
//

#include "GlobalPixel.h"

GlobalPixel::GlobalPixel() : Pixel() {
    fMeasures = vector<double>();
}

GlobalPixel::GlobalPixel(double reference, const vector<double> &thresholds, vector<double> fMeasures) :
        Pixel(reference, thresholds) {
    this->fMeasures = std::move(fMeasures);
}

vector<double> GlobalPixel::getFMeasures() {
    return fMeasures;
}

void GlobalPixel::setFMeasures(vector<double> value) {
    this->fMeasures = std::move(value);
}

string GlobalPixel::toString() {
    string result = Pixel::toString();
    result += "\n\nFs:";
    for (double fMeasure: fMeasures) {
        result += to_string(fMeasure) + " ";
    }
    return result;
}
