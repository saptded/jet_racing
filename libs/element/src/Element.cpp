#include "drawableObject.hpp"
#include <AbstractElement.h>
#include <algorithm>
#include <cmath>
#include <map>
#include <vector>

#include "Element.h"
#include "MathCalculation.h"

constexpr float eps = 3;
constexpr float lambdaMin = 0.994444444;
constexpr float lambdaMax = 1.005555556;
constexpr float straightAngle = 180;
constexpr float toRadian = M_PI / 180;
constexpr float toDegree = 180 / M_PI;
constexpr float approximationDegree = 9;
constexpr size_t defaultCenterX = 0;
constexpr size_t defaultCenterY = 0;

bool Line::isElementDynamic() { return false; }

bool Arc::isElementDynamic() { return false; }

bool Propeller::isElementDynamic() { return isDynamic; }

bool Accelerator::isElementDynamic() { return false; }

void Accelerator::collision(Racer &racer, RacerController &controller, Rotation command) {
    float extraAccelerateX = 0.06 * std::cos(racer._rotation * toRadian) * racer._speed.speedX;
    float extraAccelerateY = 0.06 * -std::sin(racer._rotation * toRadian) * racer._speed.speedY;

    controller.changeSpeed(racer, false, extraAccelerateX, extraAccelerateY);
}

bool Delayer::isElementDynamic() { return false; }

void Delayer::collision(Racer &racer, RacerController &controller, Rotation command) {
    float extraAccelerateX = 0.15 * -std::cos(racer._rotation * toRadian) * std::abs(racer._speed.speedX);
    float extraAccelerateY = 0.15 * std::sin(racer._rotation * toRadian) * std::abs(racer._speed.speedY);

    controller.changeSpeed(racer, false, extraAccelerateX, extraAccelerateY);
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
    std::map<uint8_t, float> distancesToLine;
    uint8_t k = 0;

    float factorForLineEquationA = _end.y - _start.y;
    float factorForLineEquationB = _start.x - _end.x;
    float factorForLineEquationC = (_start.y * (_end.x - _start.x)) - (_start.x * (_end.y - _start.y));
    for (auto playerPoint : points) {

        float dividendForDistance = std::abs(factorForLineEquationA * playerPoint.x + factorForLineEquationB * playerPoint.y + factorForLineEquationC);
        float distanceFromPointToLine = dividendForDistance / std::sqrt(std::pow(factorForLineEquationA, 2) + std::pow(factorForLineEquationB, 2));
        distancesToLine.insert(std::make_pair(k++, distanceFromPointToLine));
    }
    float dividendForDistance = std::abs(factorForLineEquationA * racer._center.x + factorForLineEquationB * racer._center.y + factorForLineEquationC);
    float distanceToCenter = dividendForDistance / std::sqrt(std::pow(factorForLineEquationA, 2) + std::pow(factorForLineEquationB, 2));

    std::function comp = [](const std::pair<uint8_t, float> &rhs, const std::pair<uint8_t, float> &lhs) { return rhs.second < lhs.second; };
    auto minDistance = std::min_element(distancesToLine.begin(), distancesToLine.end(), comp);

    auto lineAngle = std::atan((_end.y - _start.y) / (_end.x - _start.x)) * toDegree;
    float pushAngle = getPushAngle(racer._center, _start, _end, lineAngle);
    float kSpeedX = std::abs(racer._speed.speedX / 2);
    float kSpeedY = std::abs(racer._speed.speedY / 2);
    float kDistanceToCenter = (4 / distanceToCenter);

    if ((minDistance->first == 1 || minDistance->first == 3)) {  // front
        if ((isPointOnTheLeftSideFromLine(racer._position.second, _start, _end) != isPointOnTheLeftSideFromLine(racer._center, _start, _end)) ||
            (isPointOnTheLeftSideFromLine(racer._positionExtra.second, _start, _end) != isPointOnTheLeftSideFromLine(racer._center, _start, _end))) {
            pushAngle = getPushAngle(racer._position.first, _start, _end, lineAngle) - 180;
        }
        float extraAccelerateX = 1.2 * std::cos(pushAngle * toRadian) * std::abs(racer._speed.speedX);
        float extraAccelerateY = 1.2 * -std::sin(pushAngle * toRadian) * std::abs(racer._speed.speedY);
        controller.updatePosition(racer, {static_cast<float>(racer._center.x + 0.2 * std::cos(pushAngle * toRadian)),
                                          static_cast<float>(racer._center.y + 0.2 * -std::sin(pushAngle * toRadian))});
        controller.changeSpeed(racer, false, extraAccelerateX, extraAccelerateY);
    } else if ((minDistance->first == 0 || minDistance->first == 2) || (isPointOnTheLeftSideFromLine(racer._position.first, _start, _end) !=
                                                                        isPointOnTheLeftSideFromLine(racer._position.second, _start, _end))) {  // bottom
        controller.changeSpeed(racer, false, 0.35 * std::cos(racer._rotation * toRadian) * kSpeedX * kDistanceToCenter,
                               0.35 * -std::sin(racer._rotation * toRadian) * kSpeedY * kDistanceToCenter);
        controller.changeRotationSpeed(command, racer, 0.15);
    }

    //    if (distanceToCenter < minDistance->second) {  // critical
    //        float newPushAngle = getPushAngle(racer._position.first, _start, _end, lineAngle) - 180;
    //        controller.updatePosition(racer, {static_cast<float>(racer._center.x + 1 * std::cos(newPushAngle * toRadian)),
    //                                          static_cast<float>(racer._center.y + 1 * -std::sin(newPushAngle * toRadian))});
    //        controller.changeSpeed(racer, false, 2 * std::cos(racer._rotation * toRadian) * kSpeedX * kDistanceToCenter,
    //                               2 * std::cos(racer._rotation * toRadian) * kSpeedY * kDistanceToCenter);
    //        controller.changeRotationSpeed(command, racer, 0.15);
    //    } else if ((minDistance->first == 0 || minDistance->first == 2) || (isPointOnTheLeftSideFromLine(racer._position.first, _start, _end) !=
    //                                                                        isPointOnTheLeftSideFromLine(racer._position.second, _start, _end))) {  // bottom
    //        controller.changeSpeed(racer, false, 0.3 * std::cos(racer._rotation * toRadian) * kSpeedX * kDistanceToCenter,
    //                               0.3 * -std::sin(racer._rotation * toRadian) * kSpeedY * kDistanceToCenter);
    //        controller.changeRotationSpeed(command, racer, 0.15);
    //    } else if ((minDistance->first == 1 || minDistance->first == 3) || (isPointOnTheLeftSideFromLine(racer._position.first, _start, _end) ==
    //                                                                        isPointOnTheLeftSideFromLine(racer._position.second, _start, _end))) {  // front
    //        float extraAccelerateX = 1.2 * std::cos(pushAngle * toRadian) * std::abs(racer._speed.speedX);
    //        float extraAccelerateY = 1.2 * -std::sin(pushAngle * toRadian) * std::abs(racer._speed.speedY);
    //        controller.updatePosition(racer, {static_cast<float>(racer._center.x + 0.2 * std::cos(pushAngle * toRadian)),
    //                                          static_cast<float>(racer._center.y + 0.2 * -std::sin(pushAngle * toRadian))});
    //        controller.changeSpeed(racer, false, extraAccelerateX, extraAccelerateY);
    //    }
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

float getArcPushAngle(float distToArcCenter, float radius, const Point &center, const Point &racerPoint) {
    float pushAngle = 0;
    if (distToArcCenter > radius) {
        pushAngle = (-std::atan((center.y - racerPoint.y) / (center.x - racerPoint.x)) * toDegree);
        if (pushAngle >= 0 && center.y < racerPoint.y && center.x >= racerPoint.x) {
            pushAngle += 180;
        }
        if (pushAngle <= 0 && center.y > racerPoint.y && center.x >= racerPoint.x) {
            pushAngle += 180;
        }
    } else {
        pushAngle = (-std::atan((center.y - racerPoint.y) / (center.x - racerPoint.x)) * toDegree);
        if (pushAngle >= 0 && center.y > racerPoint.y && center.x <= racerPoint.x) {
            pushAngle += 180;
        }
        if (pushAngle <= 0 && center.y < racerPoint.y && center.x <= racerPoint.x) {
            pushAngle += 180;
        }
    }
    return pushAngle;
}

void Arc::collision(Racer &racer, RacerController &controller, Rotation command) {
    std::vector<Point> points = {racer._position.first, racer._positionExtra.second, racer._positionExtra.first, racer._position.second};  // 0, 1, 2, 3
    std::map<uint8_t, float> distancesToArcCenter;
    uint8_t k = 0;
    float radius = getArcRadius(_center, _start);
    for (auto playerPoint : points) {
        float distanceFromPointToArc = std::sqrt(std::pow(_center.x - playerPoint.x, 2) + std::pow(_center.y - playerPoint.y, 2));
        distancesToArcCenter.insert(std::make_pair(k++, distanceFromPointToArc));
    }
    float distanceFromCenterToArcCenter = std::sqrt(std::pow(_center.x - racer._center.x, 2) + std::pow(_center.y - racer._center.y, 2));
    std::function comp = [](const std::pair<uint8_t, float> &rhs, const std::pair<uint8_t, float> &lhs) { return rhs.second < lhs.second; };
    std::_Rb_tree_iterator<std::pair<const uint8_t, float>> maxDistance;
    float pushAngle = 0;
    if (distanceFromCenterToArcCenter > radius) {
        maxDistance = std::min_element(distancesToArcCenter.begin(), distancesToArcCenter.end(), comp);
        pushAngle = (-std::atan((_center.y - racer._center.y) / (_center.x - racer._center.x)) * toDegree);
        if (pushAngle >= 0 && _center.y < racer._center.y && _center.x >= racer._center.x) {
            pushAngle += 180;
        } else if (pushAngle <= 0 && _center.y > racer._center.y && _center.x >= racer._center.x) {
            pushAngle += 180;
        }
    } else {
        maxDistance = std::max_element(distancesToArcCenter.begin(), distancesToArcCenter.end(), comp);
        pushAngle = (-std::atan((_center.y - racer._center.y) / (_center.x - racer._center.x)) * toDegree);
        if (pushAngle >= 0 && _center.y > racer._center.y && _center.x <= racer._center.x) {
            pushAngle += 180;
        } else if (pushAngle <= 0 && _center.y < racer._center.y && _center.x <= racer._center.x) {
            pushAngle += 180;
        }
    }

    if ((maxDistance->first == 1 || maxDistance->first == 3)) {                                   // front
        if ((distanceFromCenterToArcCenter > radius && distancesToArcCenter[1] + 2 <= radius) ||  // critical
            (distanceFromCenterToArcCenter < radius && distancesToArcCenter[1] - 2 >= radius)) {
            pushAngle = getArcPushAngle(distancesToArcCenter[1], radius, _center, points[1]);
        } else if ((distanceFromCenterToArcCenter > radius && distancesToArcCenter[3] + 2 <= radius) ||
                   (distanceFromCenterToArcCenter < radius && distancesToArcCenter[3] - 2 >= radius)) {
            pushAngle = getArcPushAngle(distancesToArcCenter[3], radius, _center, points[3]);
        }
        float extraAccelerateX = 1.2 * std::cos(pushAngle * toRadian) * std::abs(racer._speed.speedX);
        float extraAccelerateY = 1.2 * -std::sin(pushAngle * toRadian) * std::abs(racer._speed.speedY);
        controller.updatePosition(racer, {static_cast<float>(racer._center.x + 0.3 * std::cos(pushAngle * toRadian)),
                                          static_cast<float>(racer._center.y + 0.3 * -std::sin(pushAngle * toRadian))});
        controller.changeSpeed(racer, false, extraAccelerateX, extraAccelerateY);
    } else if ((maxDistance->first == 0 || maxDistance->first == 2)) {  // bottom
        float kSpeedX = std::abs(racer._speed.speedX / 3);
        float kSpeedY = std::abs(racer._speed.speedY / 3);
        controller.changeSpeed(racer, false, 0.15 * std::cos(racer._rotation * toRadian) * kSpeedX, 0.15 * -std::sin(racer._rotation * toRadian) * kSpeedY);
        controller.changeRotationSpeed(command, racer, 0.15);
    }
}

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
