#include "drawableObject.hpp"
#include <AbstractElement.h>
#include <algorithm>
#include <cmath>
#include <vector>

#include "Element.h"
#include "MathCalculation.h"

constexpr float eps = 3;
constexpr float lambdaMin = 0.994444444;
constexpr float lambdaMax = 1.005555556;
constexpr float straightAngle = 180;
constexpr float toRadian = M_PI / 180;
constexpr float toDegree = 180 / M_PI;
constexpr float approximationDegree = 5;
constexpr size_t defaultCenterX = 0;
constexpr size_t defaultCenterY = 0;

bool Line::isElementDynamic() { return false; }

bool Arc::isElementDynamic() { return false; }

bool Propeller::isElementDynamic() { return isDynamic; }

bool Accelerator::isElementDynamic() { return false; }

bool Delayer::isElementDynamic() { return false; }

bool Portal::isElementDynamic() { return false; }

bool Finish::isElementDynamic() { return false; }

bool Line::intersect(Point &playerTopLeft, Point &playerTopRight, Point &playerBottomLeft, Point &playerBottomRight) {
    std::vector<Point> points = {playerTopLeft, playerTopRight, playerBottomLeft, playerBottomRight};

    for (auto playerPoint : points) {
        if (((playerPoint.x <= _start.x && playerPoint.x >= _end.x) || (playerPoint.x >= _start.x && playerPoint.x <= _end.x)) &&
            ((playerPoint.y <= _start.y && playerPoint.y >= _end.y) || (playerPoint.y >= _start.y && playerPoint.y <= _end.y))) {

            float factorForLineEquationA = _end.y - _start.y;
            float factorForLineEquationB = _start.x - _end.x;
            float factorForLineEquationC = (_start.y * (_end.x - _start.x)) - (_start.x * (_end.y - _start.y));

            float dividendForDistance = std::abs(factorForLineEquationA * playerPoint.x + factorForLineEquationB * playerPoint.y + factorForLineEquationC);

            if (dividendForDistance == 0) {
                return true;
            }

            auto distanceFromPointToLine = dividendForDistance / std::sqrt(std::pow(factorForLineEquationA, 2) + std::pow(factorForLineEquationB, 2));

            if (std::abs(1 - distanceFromPointToLine) < eps) {
                return true;
            }
        }
    }
    return false;
}
void Line::collision(Racer &racer, const RacerController &controller) { controller.changeSpeed(racer, -2 * racer._speed.speedX, -2 * racer._speed.speedY); }

std::vector<Line> Arc::getApproximatedArc(int iteration, float radius, Arc &arc) {
    std::vector<Line> approximatedLines;

    for (int i = 1; i <= iteration; i++) {
        float projectionOfAdjacentAngle = radius * std::cos(static_cast<float>(i) * approximationDegree * toRadian);
        float projectionOfOppositeAngle = radius * std::sin(static_cast<float>(i) * approximationDegree * toRadian);

        float newPointX;
        float newPointY;

        if (arc._center.x > arc._start.x) {
            newPointX = _center.x - projectionOfAdjacentAngle;
            newPointY = _center.y - projectionOfOppositeAngle;
        } else if (arc._center.x < arc._start.x) {
            newPointX = _center.x + projectionOfAdjacentAngle;
            newPointY = _center.y + projectionOfOppositeAngle;
        } else if (arc._center.y > arc._start.y) {
            newPointX = _center.x + projectionOfOppositeAngle;
            newPointY = _center.y - projectionOfAdjacentAngle;
        } else if (arc._center.y < arc._start.y) {
            newPointX = _center.x - projectionOfOppositeAngle;
            newPointY = _center.y + projectionOfAdjacentAngle;
        }

        if (i == iteration) {
            newPointX = arc._end.x;
            newPointY = arc._end.y;
        }

        Point newEnd = {newPointX, newPointY};
        Point center = {defaultCenterX, defaultCenterY};

        Line line(arc._start, newEnd, center);

        approximatedLines.push_back(line);

        std::swap(arc._start, newEnd);
    }

    return approximatedLines;
}

bool Arc::intersect(Point &playerTopLeft, Point &playerTopRight, Point &playerBottomLeft, Point &playerBottomRight) {
    float xProjectionCenterStart = _center.x - _start.x;
    float yProjectionCenterStart = _center.y - _start.y;
    float xProjectionCenterEnd = _center.x - _end.x;
    float yProjectionCenterEnd = _center.y - _end.y;

    float cosineOfAngleStartEnd = findCosine(xProjectionCenterStart, xProjectionCenterEnd, yProjectionCenterStart, yProjectionCenterEnd);

    float degree = std::acos(cosineOfAngleStartEnd) * toDegree;

    float radius;
    if (_center.x != _start.x) {
        radius = std::abs(_center.x - _start.x);
    } else {
        radius = std::abs(_center.y - _start.y);
    }

    int iteration = std::ceil(degree / approximationDegree);

    Arc initArc(_start, _end, _center);
    std::vector<Line> approximatedLines = this->getApproximatedArc(iteration, radius, initArc);

    for (auto &line : approximatedLines) {
        if (line.intersect(playerTopLeft, playerTopRight, playerBottomLeft, playerBottomRight)) {
            return true;
        }
    }

    return false;
}
void Arc::collision(Racer &racer, const RacerController &controller) { controller.changeSpeed(racer, -2 * racer._speed.speedX, -2 * racer._speed.speedY); }

bool Rectangle::intersect(Point &playerTopLeft, Point &playerTopRight, Point &playerBottomLeft, Point &playerBottomRight) {
    std::vector<Point> points = {playerTopLeft, playerTopRight, playerBottomLeft, playerBottomRight};

    auto minmaxHeight = std::minmax_element(points.begin(), points.end(), [](Point const &lhs, Point const &rhs) { return lhs.y < rhs.y; });

    auto minmaxWidth = std::minmax_element(points.begin(), points.end(), [](Point const &lhs, Point const &rhs) { return lhs.x < rhs.x; });

    float playerTopPoint = minmaxHeight.second->y;
    float playerBottomPoint = minmaxHeight.first->y;
    float playerRightPoint = minmaxWidth.second->x;
    float playerLeftPoint = minmaxWidth.first->x;

    float figureTopPoint = std::max(_start.y, _end.y);
    float figureBottomPoint = std::min(_start.y, _end.y);
    float figureRightPoint = std::max(_start.x, _end.x);
    float figureLeftPoint = std::min(_start.x, _end.x);

    if ((playerTopPoint <= figureTopPoint || playerBottomPoint >= figureBottomPoint) &&
        (playerRightPoint <= figureRightPoint || playerLeftPoint >= figureLeftPoint)) {
        return true;
    }

    return false;
}

void AbstractElement::draw(sf::RenderWindow &window) {
    if (!isElementDynamic()) {
        _drObj->draw(window);
    } else {
        _drObj->drawDynamic(window, _start, _end, _center);
    }
}

void AbstractElement::changeDrawableObject(int stage) { _drObj->change(stage); }
