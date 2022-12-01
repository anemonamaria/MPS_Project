//
// Created by Bogdan on 01-Dec-22.
//

#ifndef MPS_PROJECT_PIXEL_H
#define MPS_PROJECT_PIXEL_H

#include <cstring>
#include <vector>
#include <iostream>

using namespace std;

// Abstract class for a generic globalPixel
class Pixel {
public:
    double reference;
    vector<double> thresholds;

    double getReference() const;

    vector<double> getThresholds() const;

    void setReference(double value);

    void setThresholds(vector<double> value);

public:
    Pixel();

    Pixel(double reference, vector<double> thresholds);

    virtual string toString();
};



#endif //MPS_PROJECT_PIXEL_H
