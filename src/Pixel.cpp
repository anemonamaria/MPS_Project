//
// Created by Bogdan on 01-Dec-22.
//

#include "Pixel.h"

using namespace std;

#include <vector>

Pixel::Pixel() {
    reference = 0;
    thresholds = vector<double>();
}

Pixel::Pixel(double reference, vector<double> thresholds) {
    this->reference = reference;
    this->thresholds = std::move(thresholds);
}

double Pixel::getReference() const {
    return reference;
}

vector<double> Pixel::getThresholds() {
    return thresholds;
}

void Pixel::setReference(double value) {
    this->reference = value;
}

void Pixel::setThresholds(vector<double> value) {
    this->thresholds = std::move(value);
}

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
