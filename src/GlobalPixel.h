//
// Created by Bogdan on 01-Dec-22.
//

#ifndef MPS_PROJECT_GLOBALPIXEL_H
#define MPS_PROJECT_GLOBALPIXEL_H

#include "Pixel.h"

class GlobalPixel : public Pixel {
private:
    vector<double> fMeasures;
public:
    GlobalPixel();

    GlobalPixel(double reference, const vector<double> &thresholds, vector<double> fMeasures);

    vector<double> getFMeasures();

    void setFMeasures(vector<double> value);

    string toString() override;
};


#endif //MPS_PROJECT_GLOBALPIXEL_H
