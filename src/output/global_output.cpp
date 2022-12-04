#include <algorithm>
#include <cmath>
#define arithmeticMean(x, y) ((x + y) / 2)
#define geometricMean(x, y) (sqrt(x * y))
#define harmonicMean(x, y) (2 / ((1 / x) + (1 / y)))
#define minFunction(x, y) (min(x, y))
#define maxFunction(x, y) (max(x, y))
using namespace std;

double binarization(double* thresholds){
	return minFunction(geometricMean(thresholds[14], thresholds[11]), thresholds[3]);
}
