//
// Created by Bogdan on 03-Dec-22.
//

#include "Functions.h"
#include <fstream>

void Functions::printFunction(const string &function, double a, double b, double result) {
    fstream file;
    file.open("output/output.txt", ios::app);

    if (!file) {
        exit(1);
    }
    file << function << "(" << a << ", " << b << ") = " << result << '\n';
}

double Functions::arithmeticMean(double a, double b) {
    double result = (a + b) / 2;
//    printFunction(__FUNCTION__, a, b, result);
//    cout << __FUNCTION__ << " " << a << " " << b << '\n';
//    cout << result << '\n';
    return result;
}

double Functions::minFunction(double a, double b) {
    double result = min(a, b);
    printFunction(__FUNCTION__, a, b, result);
    cout << __FUNCTION__ << " " << a << " " << b << '\n';
    cout << result << '\n';
    return result;
}

double Functions::maxFunction(double a, double b) {
    double result = max(a, b);
    printFunction(__FUNCTION__, a, b, result);
    cout << __FUNCTION__ << " " << a << " " << b << '\n';
    cout << result << '\n';
    return result;
}

double Functions::geometricMean(double a, double b) {
    double result = sqrt(a * b);
    printFunction(__FUNCTION__, a, b, result);
    cout << __FUNCTION__ << " " << a << " " << b << '\n';
    cout << result << '\n';
    return result;
}

double Functions::harmonicMean(double a, double b) {
    double result = 2 / (1 / a + 1 / b);
//    printFunction(__FUNCTION__, a, b, result);
//    cout << __FUNCTION__ << " " << a << " " << b << '\n';
//    cout << result << '\n';
    return result;
}

