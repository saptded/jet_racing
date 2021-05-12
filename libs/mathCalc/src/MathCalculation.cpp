#include <cmath>

#include "MathCalculation.h"

constexpr float power = 2;

float findCosine(float xFirstProjection, float xSecondProjection, float yFirstProjection, float ySecondProjection) {
    float firstLength = sqrt(pow(xFirstProjection, power) + pow(yFirstProjection, power));
    float secondLength = sqrt(pow(xSecondProjection, power) + pow(ySecondProjection, power));

    float scalarProduct = std::abs(xFirstProjection * xSecondProjection + yFirstProjection * ySecondProjection);

    float angleCosine = scalarProduct / (firstLength * secondLength);

    return angleCosine;
}
