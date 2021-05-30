#include <cmath>
#include <map>

#include "MathCalculation.h"

bool isPointOnTheLeftSideFromLine(const Point &point, const Point &start, const Point &end) {
    if (start.y == end.y) {
        return point.y <= start.y;
    }
    float d = (point.x - start.x) * (end.y - start.y) - (point.y - start.y) * (end.x - start.x);
    return (d <= 0);
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

std::pair<float, bool> getArcPushAngle(std::map<uint8_t, float> &distancesToArcCenter, float radius, Point &center,
                                       std::vector<Point> &points) {  // PushAngle, isInside
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
