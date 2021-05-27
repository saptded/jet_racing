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

bool isPointInZone(Point &playerPoint, Point &start, Point &end)  {
    auto minX = std::min(start.x, end.x);
    auto maxX = std::max(start.x, end.x);
    auto minY = std::min(start.y, end.y);
    auto maxY = std::max(start.y, end.y);

    if ((playerPoint.x <= maxX && playerPoint.x >= minX) && (playerPoint.y <= maxY && playerPoint.y >= minY)) {
        return true;
    }

    if (start.x == end.x) {
        if (playerPoint.y <= maxY && playerPoint.y >= minY && playerPoint.x <= end.x + 100 && playerPoint.x >= end.x - 100) {
            return true;
        }
    }
    if (start.y == end.y) {
        if (playerPoint.x <= maxX && playerPoint.x >= minX && playerPoint.y <= end.y + 100 && playerPoint.y >= end.y - 100) {
            return true;
        }
    }

    return false;
}