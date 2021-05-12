#include "Element.h"
#include "MathCalculation.h"

#include <vector>
#include <cmath>
#include <algorithm>

#include <iostream>

constexpr double power = 2;
constexpr double eps = 1e-7;
constexpr double lambdaMin = 0.994444444;
constexpr double lambdaMax = 1.005555556;
constexpr double straightAngle = 180;
constexpr double rightAngle = 90;
constexpr double toRadian = M_PI / 180;
constexpr double toDegree = 180 / M_PI;
constexpr int approximationDegree = 30;
constexpr size_t defaultCenterX = 0;
constexpr size_t defaultCenterY = 0;

bool Idle::intersect(Point playerTopLeft, Point playerTopRight, Point playerBottomLeft, Point playerBottomRight) {
    return false;
}

bool Idle::isElementDynamic() {
    return false;
}

bool Line::isElementDynamic() {
    return false;
}

bool Arc::isElementDynamic() {
    return false;
}

bool Propeller::isElementDynamic() {
    return isDynamic;
}

bool Accelerator::isElementDynamic() {
    return false;
}

bool Delayer::isElementDynamic() {
    return false;
}

bool Portal::isElementDynamic() {
    return false;
}

bool Finish::isElementDynamic() {
    return false;
}

bool Line::intersect(Point playerTopLeft, Point playerTopRight, Point playerBottomLeft, Point playerBottomRight) {
    std::vector<Point> points = {playerTopLeft, playerTopRight, playerBottomLeft, playerBottomRight};

    for (auto it : points) {
        if ((it.x == this->_start.x && it.y == this->_start.y) || (it.x == this->_end.x && it.y == this->_end.y)) {
            return true;
        }

        //TODO переисменовать переменные
        double xFirstProjection = (double) this->_start.x - (double) it.x;
        double yFirstProjection = (double) this->_start.y - (double) it.y;
        double xSecondProjection = (double) this->_end.x - (double) it.x;
        double ySecondProjection = (double) this->_end.y - (double) it.y;

        double angleCosine = cosineAngle(xFirstProjection, xSecondProjection, yFirstProjection, ySecondProjection);



        if (angleCosine == 1) {
            return false;
        }

        if (1 - angleCosine < eps) {
            if ((acos(angleCosine) * toDegree > straightAngle * lambdaMin
                && acos(angleCosine) * toDegree < straightAngle * lambdaMax) ||
                (acos(angleCosine) * toDegree > -(straightAngle * lambdaMax)
                    && acos(angleCosine) * toDegree > -(straightAngle * lambdaMin))) {
                return true;
            }
        }
    }

    return false;
}
bool Arc::intersect(Point playerTopLeft, Point playerTopRight, Point playerBottomLeft, Point playerBottomRight) {
    double xProjectionCenterStart = (double) this->_center.x - (double) this->_start.x;
    double yProjectionCenterStart = (double) this->_center.y - (double) this->_start.y;
    double xProjectionCenterEnd = (double) this->_center.x - (double) this->_end.x;
    double yProjectionCenterEnd = (double) this->_center.y - (double) this->_end.y;

    double cosineOfAngleStartEnd =
        cosineAngle(xProjectionCenterStart, xProjectionCenterEnd, yProjectionCenterStart, yProjectionCenterEnd);
    if (cosineOfAngleStartEnd > 1 || cosineOfAngleStartEnd < -1) {
        return false;
    }

    double degree = acos(cosineOfAngleStartEnd) * toDegree;

    double radius;
    if (this->_center.x != this->_start.x) {
        radius = std::abs((double) this->_center.x - (double) this->_start.x);
    } else {
        radius = std::abs((double) this->_center.y - (double) this->_start.y);
    }

    std::vector<Line> approximatedLines;

    for (int i = approximationDegree; i <= degree; i += approximationDegree) {
        double radiusProjectionX = radius * cos(i * toRadian);
        double radiusProjectionY = radius * sin(i * toRadian);

        double newPointX = 0;
        double newPointY = 0;

        if (degree <= rightAngle) {
            if (this->_center.x >= this->_start.x) {
                newPointX = (double) this->_center.x - radiusProjectionX;
            } else {
                newPointX = (double) this->_center.x + radiusProjectionX;
            }

            if (this->_center.y >= this->_start.y) {
                newPointY = (double) this->_center.y - radiusProjectionY;
            } else {
                newPointY = (double) this->_center.y + radiusProjectionY;
            }
        }

        Point newEnd = {(size_t) round(newPointX), (size_t) round(newPointY)};
        Point center = {defaultCenterX, defaultCenterY};

        Line line(this->_start, newEnd, center);

        approximatedLines.push_back(line);

        std::swap(this->_start, newEnd);
    }

    for (auto it : approximatedLines) {
        if (it.intersect(playerTopLeft, playerTopRight, playerBottomLeft, playerBottomRight)) {
            std::cout << "пересечение" << std::endl;
            return true;
        }
    }

    std::cout << "нет пересечения" << std::endl;
    return false;
}

bool Rectangle::intersect(Point playerTopLeft, Point playerTopRight, Point playerBottomLeft, Point playerBottomRight) {
    std::vector<Point> points = {playerTopLeft, playerTopRight, playerBottomLeft, playerBottomRight};

    auto minmaxHeight = std::minmax_element(points.begin(),
                                            points.end(),
                                            [](Point const &lhs, Point const &rhs) { return lhs.y < rhs.y; });

    auto minmaxWidth = std::minmax_element(points.begin(),
                                           points.end(),
                                           [](Point const &lhs, Point const &rhs) { return lhs.x < rhs.x; });

    size_t playerTop = minmaxHeight.second->y;
    size_t playerBottom = minmaxHeight.first->y;
    size_t playerRight = minmaxWidth.second->x;
    size_t playerLeft = minmaxWidth.first->x;

    size_t figureTop = std::max(this->_start.y, this->_end.y);
    size_t figureBottom = std::min(this->_start.y, this->_end.y);
    size_t figureRight = std::max(this->_start.x, this->_end.x);
    size_t figureLeft = std::min(this->_start.x, this->_end.x);

    if ((playerTop <= figureTop || playerBottom >= figureBottom)
        && (playerRight <= figureRight || playerLeft >= figureLeft)) {
        return true;
    }

    return false;
}
