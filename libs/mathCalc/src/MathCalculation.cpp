#include <cmath>

#include "MathCalculation.h"

constexpr double power = 2;

double findCosine(double xFirstProjection,
                  double xSecondProjection,
                  double yFirstProjection,
                  double ySecondProjection) {
    double firstLength = sqrt(pow(xFirstProjection, power) + pow(yFirstProjection, power));
    double secondLength = sqrt(pow(xSecondProjection, power) + pow(ySecondProjection, power));

    double scalarProduct = std::abs(xFirstProjection * xSecondProjection + yFirstProjection * ySecondProjection);

    double angleCosine = scalarProduct / (firstLength * secondLength);

    return angleCosine;
}
