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

vector<double> Pixel::getThresholds() const {
    return thresholds;
}

void Pixel::setReference(double value) {
    this->reference = value;
}

void Pixel::setThresholds(vector<double> value) {
    this->thresholds = std::move(value);
}

string Pixel::toString() {
    string result = "R: " + to_string(reference) + " ";
    result += "Ts: ";
    for (double threshold : thresholds) {
        result += to_string(threshold) + " ";
    }
    return result;
}
