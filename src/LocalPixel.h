//
// Created by Bogdan on 01-Dec-22.
//

#ifndef MPS_PROJECT_LOCALPIXEL_H
#define MPS_PROJECT_LOCALPIXEL_H

#include "Pixel.h"

class LocalPixel : public Pixel {
private:
    double pixelClass;

public:
    LocalPixel(double reference, vector<double> thresholds, double pixelClass);

    double getPixelClass() const;

    void setPixelClass(double value);

    string toString() override;
};

#endif //MPS_PROJECT_LOCALPIXEL_H
