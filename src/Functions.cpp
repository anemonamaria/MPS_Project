//
// Created by Bogdan on 03-Dec-22.
//

#include "Functions.h"

double Functions::arithmeticMean(double a, double b) {
    cout << __FUNCTION__ << " " << a << " " << b << '\n';
    cout << (a + b) / 2 << '\n';
    return (a + b) / 2;
}

double Functions::minFunction(double a, double b) {
    cout << __FUNCTION__ << " " << a << " " << b << '\n';
    cout << min(a, b) << '\n';
    return min(a, b);
}

double Functions::maxFunction(double a, double b) {
    cout << __FUNCTION__ << " " << a << " " << b << '\n';
    cout << max(a, b) << '\n';
    return max(a, b);
}

double Functions::geometricMean(double a, double b) {
    cout << __FUNCTION__ << " " << a << " " << b << '\n';
    cout << sqrt(a * b) << '\n';
    return sqrt(a * b);
}

double Functions::harmonicMean(double a, double b) {
    cout << __FUNCTION__ << " " << a << " " << b << '\n';
    cout << (2 * a * b) / (a + b) << '\n';
    return 2 / (1 / a + 1 / b);
}
