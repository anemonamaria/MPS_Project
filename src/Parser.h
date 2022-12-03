//
// Created by Bogdan on 13-Nov-22.
//

#ifndef MPS_PROJECT_PARSER_H
#define MPS_PROJECT_PARSER_H

#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include "Pixel.h"
#include "LocalPixel.h"
#include "GlobalPixel.h"
#include "Node.h"

using namespace std;

class Parser {
public:
    vector<LocalPixel> localPixels;
    GlobalPixel globalPixel;
    static std::ostringstream out;

    double getFMeasure(double threshold);

    // The printing functions are only used for debugging purposes, and are therefore marked as unused
    __attribute__((unused)) void printLocal();

    __attribute__((unused)) void printGlobal();

    int parseLocal(vector<LocalPixel> &pixels, string filePath);

    int parseGlobal(GlobalPixel &globalPixel, string filePath);

    void createTreeGlobal();

    void printTree(Node *pNode);
};


#endif //MPS_PROJECT_PARSER_H
