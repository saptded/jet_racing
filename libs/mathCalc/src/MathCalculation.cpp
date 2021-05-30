#include <cmath>
#include <map>

#include "MathCalculation.h"

constexpr float power = 2;

float findCosine(float xFirstProjection, float xSecondProjection, float yFirstProjection, float ySecondProjection) {
    float firstLength = std::sqrt(std::pow(xFirstProjection, power) + std::pow(yFirstProjection, power));
    float secondLength = std::sqrt(std::pow(xSecondProjection, power) + std::pow(ySecondProjection, power));

    float scalarProduct = xFirstProjection * xSecondProjection + yFirstProjection * ySecondProjection;

    float angleCosine = scalarProduct / (firstLength * secondLength);

    return angleCosine;
}

bool isPointOnTheLeftSideFromLine(const Point &point, const Point &start, const Point &end) {
    if (start.y == end.y) {
        return point.y <= start.y;
    }
    float d = (point.x - start.x) * (end.y - start.y) - (point.y - start.y) * (end.x - start.x);
    return (d <= 0);
}

bool isPointInZone(Point &playerPoint, Point &start, Point &end) {
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

float getPushAngle(Point &playerPoint, Point &start, Point &end, float lineAngle) {
    bool left = isPointOnTheLeftSideFromLine(playerPoint, start, end);
    float pushAngle = 0;
    if (left) {
        pushAngle = 90 + lineAngle;
    } else {
        pushAngle = -90 + lineAngle;
    }
    return pushAngle;
}

float getArcRadius(const Point &center, const Point &start) {
    if (center.x != start.x) {
        return std::abs(center.x - start.x);
    } else {
        return std::abs(center.y - start.y);
    }
}

std::pair<float, bool> getArcPushAngle(std::map<uint8_t, float> &distancesToArcCenter, float radius, Point &center, std::vector<Point> &points) {
    float toDegree = 180 / M_PI;
    uint8_t insidePoints = 0;
    uint8_t outsidePoints = 0;
    Point inPoint{0, 0};
    Point outPoint{0, 0};

    for (auto distance : distancesToArcCenter) {
        if (distance.second > radius) {
            if (distance.first != 0 && distance.first != 2) {
                ++outsidePoints;
                outPoint = points[distance.first];
            }
        } else {
            if (distance.first != 0 && distance.first != 2) {
                inPoint = points[distance.first];
                ++insidePoints;
            }
        }
    }

    bool isInside = true;
    float pushAngle = 0;
    if (outsidePoints > insidePoints) {
        pushAngle = (-std::atan((center.y - outPoint.y) / (center.x - outPoint.x)) * toDegree);
        if (pushAngle >= 0 && center.y < outPoint.y && center.x >= outPoint.x) {
            pushAngle += 180;
        }
        if (pushAngle <= 0 && center.y > outPoint.y && center.x >= outPoint.x) {
            pushAngle += 180;
        }
        isInside = false;
    } else {
        pushAngle = (-std::atan((center.y - inPoint.y) / (center.x - inPoint.x)) * toDegree);
        if (pushAngle >= 0 && center.y > inPoint.y && center.x <= inPoint.x) {
            pushAngle += 180;
        }
        if (pushAngle <= 0 && center.y < inPoint.y && center.x <= inPoint.x) {
            pushAngle += 180;
        }
    }

    return std::make_pair(pushAngle, isInside);
}
