//
// Created by Bogdan on 03-Dec-22.
//

#ifndef MPS_PROJECT_FUNCTIONS_H
#define MPS_PROJECT_FUNCTIONS_H

#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>

using namespace std;
/*
 * a, b ----> (1/(1/a + 1/b)) + (a+b)/2
 * a, b ----> harmonicMean(a,b)+ arithmeticmean(..
 *
 */



// * nod root
// * parcurge(root)
// * generateString(root)
// * (generateString (left) + generateString(right))
// *geneerateString (leftleft) + generatestringrighright) + valRight

using namespace std;

typedef double(*Function)(double, double);
//class  Opperation {
//    string operationstring;
//    double threshold;
//};        string operatie ="(" + operationstring + " + " + b +  ")/2";

class Functions {
public:
    static double arithmeticMean(double a, double b);

    static double minFunction(double a, double b);

    static double maxFunction(double a, double b);

    static double geometricMean(double a, double b);

    static double harmonicMean(double a, double b);

    vector<Function> array = {arithmeticMean, minFunction, maxFunction, geometricMean, harmonicMean};

    vector<string> names = {"arithmeticMean", "minFunction", "maxFunction", "geometricMean", "harmonicMean"};

    static void printFunction(const string &function, double a, double b, double result);
};


#endif //MPS_PROJECT_FUNCTIONS_H
