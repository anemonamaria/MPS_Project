//
// Created by Bogdan on 13-Nov-22.
//

#ifndef MPS_PROJECT_MAIN_H
#define MPS_PROJECT_MAIN_H

#include <sstream>
#include "iostream"
#include "Pixel.h"

using namespace std;

class Main {
public:
    vector<LocalPixel> pixels;
    GlobalPixel globalPixel;
    static std::ostringstream out;

    int parseLocal();
    int parseGlobal();
    double getFMeasure(double threshold);

    void printLocal();

    void printGlobal();
};


#endif //MPS_PROJECT_MAIN_H
