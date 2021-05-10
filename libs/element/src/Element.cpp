#include "Element.h"

#include <vector>
#include <cmath>
#include <algorithm>

constexpr double pi = M_PI;
constexpr double power = 2;
constexpr double eps = 1e-7;
constexpr double lambdaMin = 0.994444444;
constexpr double lambdaMax = 1.005555556;
constexpr double straightAngle = 180;

bool Idle::intersect(Point playerA, Point playerB, Point playerC, Point playerD) {
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

bool Line::intersect(Point playerA, Point playerB, Point playerC, Point playerD) {
    std::vector<Point> points = {playerA, playerB, playerC, playerD};

    double angleCosine;

    for (auto it : points) {
        double xFirstProjection = (double) this->_start.x - (double) it.x;
        double yFirstProjection = (double) this->_start.y - (double) it.y;
        double xSecondProjection = (double) this->_end.x - (double) it.x;
        double ySecondProjection = (double) this->_end.y - (double) it.y;

        double firstLength = sqrt(pow(xFirstProjection, power) + pow(yFirstProjection, power));
        double secondLength = sqrt(pow(xSecondProjection, power) + pow(ySecondProjection, power));

        double scalarProduct = std::abs(xFirstProjection * xSecondProjection + yFirstProjection * ySecondProjection);

        angleCosine = scalarProduct / (firstLength * secondLength);

        if (angleCosine > 1 || angleCosine < -1) {
            return false;
        }

        if (1 - angleCosine < eps) {
            if (((acos(angleCosine) * straightAngle) / pi > straightAngle * lambdaMin
                && (acos(angleCosine) * straightAngle) / pi < straightAngle * lambdaMax) ||
                ((acos(angleCosine) * straightAngle) / pi > -(straightAngle * lambdaMax)
                    && (acos(angleCosine) * straightAngle) / pi > -(straightAngle * lambdaMin))) {
                return true;
            }
        }
    }

    return false;
}
bool Arc::intersect(Point playerA, Point playerB, Point playerC, Point playerD) {
    std::vector<Point> points = {playerA, playerB, playerC, playerD};

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

    size_t figureNormalX;
    size_t figureNormalY;

    if (this->_start.x == this->_end.x) {
        figureNormalY = this->_center.y;
        if (this->_start.y > this->_end.y) {
            figureNormalX = this->_center.x + (this->_start.y - this->_end.y) / 2;
        } else if (this->_start.y < this->_end.y) {
            figureNormalX = this->_center.x - (this->_end.y - this->_start.y) / 2;
        }
    } else if (this->_start.y == this->_end.y) {
        figureNormalX = this->_center.x;
        if (this->_start.x > this->_end.x) {
            figureNormalY = this->_center.y + (this->_start.x - this->_end.x) / 2;
        } else if (this->_start.x < this->_end.x) {
            figureNormalY = this->_center.y - (this->_end.x - this->_start.x) / 2;
        }
    }

    size_t figureTop = 0;
    size_t figureBottom = 0;
    size_t figureRight = 0;
    size_t figureLeft = 0;

    if (this->_start.x == this->_end.x) {
        figureTop = std::max(this->_start.y, this->_end.y);
        figureBottom = std::min(this->_start.y, this->_end.y);
        figureRight = std::max(this->_center.x, figureNormalX);
        figureLeft = std::min(this->_center.x, figureNormalX);
    } else if (this->_start.y == this->_end.y) {
        figureTop = std::max(this->_center.y, figureNormalY);
        figureBottom = std::min(this->_center.y, figureNormalY);
        figureRight = std::max(this->_start.x, this->_end.x);
        figureLeft = std::min(this->_start.x, this->_end.x);
    }

    if ((playerTop <= figureTop || playerBottom >= figureBottom)
        && (playerRight <= figureRight || playerLeft >= figureLeft)) {
        return true;
    }

    return false;
}

bool Rectangle::intersect(Point playerA, Point playerB, Point playerC, Point playerD) {
    std::vector<Point> points = {playerA, playerB, playerC, playerD};

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
