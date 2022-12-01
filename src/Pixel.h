//
// Created by Bogdan on 01-Dec-22.
//

#ifndef MPS_PROJECT_PIXEL_H
#define MPS_PROJECT_PIXEL_H

#include <vector>

using namespace std;

// Abstract class for a generic pixel
class Pixel {
public:
    double reference;
    vector<double> thresholds;

    double getReference() const;

    vector<double> getThresholds();

    void setReference(double value);

    void setThresholds(vector<double> value);

public:
    Pixel();

    Pixel(double reference, vector<double> thresholds);
};

class GlobalPixel : public Pixel {
private:
    vector<double> fMeasures;
public:
    GlobalPixel();

    GlobalPixel(double reference, const vector<double> &thresholds, vector<double> fMeasures);

    vector<double> getFMeasures();

    void setFMeasures(vector<double> value);
};

class LocalPixel : public Pixel {
private:
    double pixelClass;

public:
    LocalPixel(double reference, vector<double> thresholds, double pixelClass);

    double getPixelClass() const;

    void setPixelClass(double value);
};


#endif //MPS_PROJECT_PIXEL_H
