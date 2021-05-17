#include <cmath>

#include "MathCalculation.h"

constexpr float power = 2;

float findCosine(float xFirstProjection, float xSecondProjection, float yFirstProjection, float ySecondProjection) {
    float firstLength = std::sqrt(std::pow(xFirstProjection, power) + std::pow(yFirstProjection, power));
    float secondLength = std::sqrt(std::pow(xSecondProjection, power) + std::pow(ySecondProjection, power));

    float scalarProduct = xFirstProjection * xSecondProjection + yFirstProjection * ySecondProjection;

    float angleCosine = scalarProduct / (firstLength * secondLength);

    return angleCosine;
}
