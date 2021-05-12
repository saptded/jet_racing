#include <algorithm>
#include <cmath>
#include <vector>
#include <AbstractElement.h>
#include "drawableObject.hpp"


#include "Element.h"
#include "MathCalculation.h"

constexpr double eps = 1e-7;
constexpr double lambdaMin = 0.994444444;
constexpr double lambdaMax = 1.005555556;
constexpr double straightAngle = 180;
constexpr double toRadian = M_PI / 180;
constexpr double toDegree = 180 / M_PI;
constexpr int approximationDegree = 30;
constexpr float defaultCenterX = 0;
constexpr float defaultCenterY = 0;

bool Idle::intersect(PointM playerTopLeft, PointM playerTopRight, PointM playerBottomLeft, PointM playerBottomRight) {
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

bool Line::intersect(PointM playerTopLeft, PointM playerTopRight, PointM playerBottomLeft, PointM playerBottomRight) {
    std::vector<PointM> points = {playerTopLeft, playerTopRight, playerBottomLeft, playerBottomRight};

    for (auto it : points) {
        if ((it.x == this->_start.x && it.y == this->_start.y) || (it.x == this->_end.x && it.y == this->_end.y)) {
            return true;
        }

        double projectionPlayerFigureStartX = (double) this->_start.x - (double) it.x;
        double projectionPlayerFigureEndX = (double) this->_end.x - (double) it.x;
        double projectionPlayerFigureStartY = (double) this->_start.y - (double) it.y;
        double projectionPlayerFigureEndY = (double) this->_end.y - (double) it.y;

        double cosinePlayerFigure = findCosine(projectionPlayerFigureStartX,
                                               projectionPlayerFigureEndX,
                                               projectionPlayerFigureStartY,
                                               projectionPlayerFigureEndY);

        if (cosinePlayerFigure == 1) {
            return false;
        }

        if (1 - cosinePlayerFigure < eps) {
            if ((acos(cosinePlayerFigure) * toDegree > straightAngle * lambdaMin
                && acos(cosinePlayerFigure) * toDegree < straightAngle * lambdaMax) ||
                (acos(cosinePlayerFigure) * toDegree > -(straightAngle * lambdaMax)
                    && acos(cosinePlayerFigure) * toDegree > -(straightAngle * lambdaMin))) {
                return true;
            }
        }
    }

    return false;
}
bool Arc::intersect(PointM playerTopLeft, PointM playerTopRight, PointM playerBottomLeft, PointM playerBottomRight) {
    double xProjectionCenterStart = (double) this->_center.x - (double) this->_start.x;
    double yProjectionCenterStart = (double) this->_center.y - (double) this->_start.y;
    double xProjectionCenterEnd = (double) this->_center.x - (double) this->_end.x;
    double yProjectionCenterEnd = (double) this->_center.y - (double) this->_end.y;

    double cosineOfAngleStartEnd =
        findCosine(xProjectionCenterStart, xProjectionCenterEnd, yProjectionCenterStart, yProjectionCenterEnd);

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
        double projectionOfAdjacentAngle = radius * cos(i * toRadian);
        double projectionOfOppositeAngle = radius * sin(i * toRadian);

        double newPointX;
        double newPointY;

        if (i < degree) {
            if (this->_center.x > this->_start.x) {
                newPointX = (double) this->_center.x - projectionOfAdjacentAngle;
                newPointY = (double) this->_center.y - projectionOfOppositeAngle;
            }

            if (this->_center.x < this->_start.x) {
                newPointX = (double) this->_center.x + projectionOfAdjacentAngle;
                newPointY = (double) this->_center.y + projectionOfOppositeAngle;
            }

            if (this->_center.y > this->_start.y) {
                newPointX = (double) this->_center.x + projectionOfOppositeAngle;
                newPointY = (double) this->_center.y - projectionOfAdjacentAngle;
            }

            if (this->_center.y < this->_start.y) {
                newPointX = (double) this->_center.x - projectionOfOppositeAngle;
                newPointY = (double) this->_center.y + projectionOfAdjacentAngle;
            }
        }

        if (i == degree) {
            newPointX = (double) this->_end.x;
            newPointY = (double) this->_end.y;
        }

        PointM newEnd = {(float) round(newPointX), (float) round(newPointY)};
        PointM center = {defaultCenterX, defaultCenterY};

        Line line(this->_start, newEnd, center);

        approximatedLines.push_back(line);

        std::swap(this->_start, newEnd);
    }

    for (auto it : approximatedLines) {
        if (it.intersect(playerTopLeft, playerTopRight, playerBottomLeft, playerBottomRight)) {
            return true;
        }
    }

    return false;
}

bool Rectangle::intersect(PointM playerTopLeft, PointM playerTopRight, PointM playerBottomLeft, PointM playerBottomRight) {
    std::vector<PointM> points = {playerTopLeft, playerTopRight, playerBottomLeft, playerBottomRight};

    auto minmaxHeight = std::minmax_element(points.begin(),
                                            points.end(),
                                            [](PointM const &lhs, PointM const &rhs) { return lhs.y < rhs.y; });

    auto minmaxWidth = std::minmax_element(points.begin(),
                                           points.end(),
                                           [](PointM const &lhs, PointM const &rhs) { return lhs.x < rhs.x; });

    float playerTop = minmaxHeight.second->y;
    float playerBottom = minmaxHeight.first->y;
    float playerRight = minmaxWidth.second->x;
    float playerLeft = minmaxWidth.first->x;

    float figureTop = std::max(this->_start.y, this->_end.y);
    float figureBottom = std::min(this->_start.y, this->_end.y);
    float figureRight = std::max(this->_start.x, this->_end.x);
    float figureLeft = std::min(this->_start.x, this->_end.x);

    if ((playerTop <= figureTop || playerBottom >= figureBottom)
        && (playerRight <= figureRight || playerLeft >= figureLeft)) {
        return true;
    }

    return false;
}

void AbstractElement::createDrawable(int stage) {
    drObj->create(*this, stage);
}

void AbstractElement::draw(sf::RenderWindow &window) {
    drObj->draw(window);
}
