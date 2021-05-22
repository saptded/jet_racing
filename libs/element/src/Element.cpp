#include "drawableObject.hpp"
#include <AbstractElement.h>
#include <algorithm>
#include <cmath>
#include <map>
#include <vector>

#include "Element.h"
#include "MathCalculation.h"

constexpr float eps = 3.5;
constexpr float lambdaMin = 0.994444444;
constexpr float lambdaMax = 1.005555556;
constexpr float straightAngle = 180;
constexpr float toRadian = M_PI / 180;
constexpr float toDegree = 180 / M_PI;
constexpr float approximationDegree = 3;
constexpr size_t defaultCenterX = 0;
constexpr size_t defaultCenterY = 0;

bool Line::isElementDynamic() { return false; }

bool Arc::isElementDynamic() { return false; }

bool Propeller::isElementDynamic() { return isDynamic; }

bool Accelerator::isElementDynamic() { return false; }

void Accelerator::collision(Racer &racer, RacerController &controller, Rotation command) { controller.changeSpeed(racer, 0.5 * racer._speed.speedX, 0.5 * racer._speed.speedY); }

bool Delayer::isElementDynamic() { return false; }

void Delayer::collision(Racer &racer, RacerController &controller, Rotation command) {
//    controller.changeSpeed(racer, false, 0.5 * std::cos(pushAngle * toRadian) * std::abs(racer._speed.speedX / 5),
//                           0.5 * std::cos(pushAngle * toRadian) * std::abs(racer._speed.speedY / 5));
}

bool Portal::isElementDynamic() { return false; }

bool Finish::isElementDynamic() { return false; }

bool Line::intersect(Point &playerTopLeft, Point &playerTopRight, Point &playerBottomLeft, Point &playerBottomRight) {
    std::vector<Point> points = {playerTopLeft, playerTopRight, playerBottomLeft, playerBottomRight};

    for (auto playerPoint : points) {
        if (isPointInZone(playerPoint, _start, _end)) {

            float factorForLineEquationA = _end.y - _start.y;
            float factorForLineEquationB = _start.x - _end.x;
            float factorForLineEquationC = (_start.y * (_end.x - _start.x)) - (_start.x * (_end.y - _start.y));

            float dividendForDistance = std::abs(factorForLineEquationA * playerPoint.x + factorForLineEquationB * playerPoint.y + factorForLineEquationC);

            if (dividendForDistance == 0) {
                return true;
            }

            auto distanceFromPointToLine = dividendForDistance / std::sqrt(std::pow(factorForLineEquationA, 2) + std::pow(factorForLineEquationB, 2));

            if (distanceFromPointToLine < eps) {
                return true;
            }
        }
    }
    return false;
}

void Line::collision(Racer &racer, RacerController &controller, Rotation command) {
    std::vector<Point> points = {racer._position.first, racer._positionExtra.second, racer._positionExtra.first, racer._position.second};  // 0, 1, 2, 3
    std::map<uint8_t, double> distancesToLine;
    uint8_t k = 0;

    float factorForLineEquationA = _end.y - _start.y;
    float factorForLineEquationB = _start.x - _end.x;
    float factorForLineEquationC = (_start.y * (_end.x - _start.x)) - (_start.x * (_end.y - _start.y));
    for (auto playerPoint : points) {

        float dividendForDistance = std::abs(factorForLineEquationA * playerPoint.x + factorForLineEquationB * playerPoint.y + factorForLineEquationC);
        double distanceFromPointToLine = dividendForDistance / std::sqrt(std::pow(factorForLineEquationA, 2) + std::pow(factorForLineEquationB, 2));
        distancesToLine.insert(std::make_pair(k++, distanceFromPointToLine));
    }
    float dividendForDistance = std::abs(factorForLineEquationA * racer._center.x + factorForLineEquationB * racer._center.y + factorForLineEquationC);
    double distanceToCenter = dividendForDistance / std::sqrt(std::pow(factorForLineEquationA, 2) + std::pow(factorForLineEquationB, 2));

    std::function comp = [](const std::pair<uint8_t, double> &rhs, const std::pair<uint8_t, double> &lhs) { return rhs.second < lhs.second; };
    auto maxDistance = std::max_element(distancesToLine.begin(), distancesToLine.end(), comp);
    auto minDistance = std::min_element(distancesToLine.begin(), distancesToLine.end(), comp);

    auto lineAngle = std::atan((_end.y - _start.y) / (_end.x - _start.x)) * toDegree;
    double pushAngle = getPushAngle(racer._center, _start, _end, lineAngle);

    if (distanceToCenter <= 3) {  // critical
        double newPushAngle = getPushAngle(racer._position.second, _start, _end, lineAngle);
        controller.updatePosition(racer, {static_cast<float>(racer._center.x + 0.8 * std::cos(newPushAngle * toRadian)),
                                          static_cast<float>(racer._center.y + 0.8 * -std::sin(newPushAngle * toRadian))});
        controller.changeSpeed(racer, false, 0.7 * std::cos(racer._rotation * toRadian) * std::abs(racer._speed.speedX / 5),
                               0.7 * std::cos(racer._rotation * toRadian) * std::abs(racer._speed.speedY / 5));
        controller.changeRotationSpeed(command, racer, 0.2);
    } else if ((minDistance->first == 0 || minDistance->first == 2)) {  // bottom
        controller.changeSpeed(racer, false, 0.35 * std::cos(racer._rotation * toRadian) * std::abs(racer._speed.speedX / 5),
                               0.35 * -std::sin(racer._rotation * toRadian) * std::abs(racer._speed.speedY / 5));
        controller.changeRotationSpeed(command, racer, 0.2);
    } else if ((minDistance->first == 1 || minDistance->first == 3)) {  // front
        float extraAccelerateX = 1.4 * std::cos(pushAngle * toRadian) * std::abs(racer._speed.speedX);
        float extraAccelerateY = 1.4 * -std::sin(pushAngle * toRadian) * std::abs(racer._speed.speedY);
        controller.updatePosition(racer, {static_cast<float>(racer._center.x + 0.1 * std::cos(pushAngle * toRadian)),
                                          static_cast<float>(racer._center.y + 0.1 * -std::sin(pushAngle * toRadian))});
        controller.changeSpeed(racer, false, extraAccelerateX, extraAccelerateY);
    }
}

std::vector<Line> Arc::getApproximatedArc(int iteration, float radius, Arc &arc) {
    std::vector<Line> approximatedLines;

    for (int i = 1; i <= iteration; ++i) {
        float projectionOfAdjacentAngle = radius * std::cos(static_cast<float>(i) * approximationDegree * toRadian);
        float projectionOfOppositeAngle = radius * std::sin(static_cast<float>(i) * approximationDegree * toRadian);

        float newPointX = 0;
        float newPointY = 0;

        if (_center.x > _start.x) {
            newPointX = _center.x - projectionOfAdjacentAngle;
            newPointY = _center.y - projectionOfOppositeAngle;
        } else if (_center.x < _start.x) {
            newPointX = _center.x + projectionOfAdjacentAngle;
            newPointY = _center.y + projectionOfOppositeAngle;
        } else if (_center.y > _start.y) {
            newPointX = _center.x + projectionOfOppositeAngle;
            newPointY = _center.y - projectionOfAdjacentAngle;
        } else if (_center.y < _start.y) {
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
void Arc::collision(Racer &racer, RacerController &controller, Rotation command) {}

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

    if (playerTopPoint <= figureTopPoint && playerBottomPoint >= figureBottomPoint && playerRightPoint <= figureRightPoint &&
        playerLeftPoint >= figureLeftPoint) {
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
