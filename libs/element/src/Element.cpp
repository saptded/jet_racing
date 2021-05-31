#include <AbstractElement.h>
#include <algorithm>
#include <cmath>
#include <map>
#include <vector>

#include "Element.h"
#include "MathCalculation.h"

constexpr float kEps = 3.5;
constexpr float toRadian = M_PI / 180;
constexpr float toDegree = 180 / M_PI;
constexpr float approximationDegree = 10;
constexpr size_t defaultCenterX = 0;
constexpr size_t defaultCenterY = 0;

void Accelerator::collision(Racer &racer, RacerController &controller, Command command) {
    float extraAccelerateX = static_cast<float>(0.1) * std::cos(racer._rotation * toRadian);
    float extraAccelerateY = static_cast<float>(0.1) * -std::sin(racer._rotation * toRadian);
    if (std::abs(racer._speed.speedY) >= 4) {
        extraAccelerateY = 0;
    }
    if (std::abs(racer._speed.speedX) >= 4) {
        extraAccelerateX = 0;
    }

    controller.changeSpeed(racer, false, std::copysignf(extraAccelerateX, racer._speed.speedX), std::copysignf(extraAccelerateY, racer._speed.speedY));
}

void Delayer::collision(Racer &racer, RacerController &controller, Command command) {
    float extraAccelerateX = static_cast<float>(0.05) * std::cos(racer._rotation * toRadian);
    float extraAccelerateY = static_cast<float>(0.05) * -std::sin(racer._rotation * toRadian);

    if (std::abs(racer._speed.speedY) <= 0.5) {
        extraAccelerateY = 0;
    }
    if (std::abs(racer._speed.speedX) <= 0.5) {
        extraAccelerateX = 0;
    }

    controller.changeSpeed(racer, false, -std::copysignf(extraAccelerateX, racer._speed.speedX), -std::copysignf(extraAccelerateY, racer._speed.speedY));
}

void Finish::collision(Racer &racer, RacerController &controller, Command command) { racer.finished = std::make_tuple(true, 0); }

bool Line::intersect(Point &playerTopLeft, Point &playerTopRight, Point &playerBottomLeft, Point &playerBottomRight, Point &playerBottomCenter) {
    std::vector<Point> points = {playerTopLeft, playerTopRight, playerBottomLeft, playerBottomRight, playerBottomCenter};
    bool isIntersects = false;

    for (auto playerPoint : points) {
        if (isPointInZone(playerPoint, _start, _end)) {
            float factorForLineEquationA = _end.y - _start.y;
            float factorForLineEquationB = _start.x - _end.x;
            float factorForLineEquationC = (_start.y * (_end.x - _start.x)) - (_start.x * (_end.y - _start.y));

            float dividendForDistance = std::abs(factorForLineEquationA * playerPoint.x + factorForLineEquationB * playerPoint.y + factorForLineEquationC);

            if (dividendForDistance == 0) {
                isIntersects = true;
            }

            auto distanceFromPointToLine = dividendForDistance / std::sqrt(std::pow(factorForLineEquationA, 2) + std::pow(factorForLineEquationB, 2));

            if (distanceFromPointToLine < kEps) {
                isIntersects = true;
            }

            if ((isPointOnTheLeftSideFromLine(playerTopLeft, _start, _end) != isPointOnTheLeftSideFromLine(playerBottomCenter, _start, _end)) ||  // alex
                (isPointOnTheLeftSideFromLine(playerBottomLeft, _start, _end) != isPointOnTheLeftSideFromLine(playerBottomCenter, _start, _end))) {
                isIntersects = true;
            }
        }
    }

    return isIntersects;
}

void Line::collision(Racer &racer, RacerController &controller, Command command) {
    std::vector<Point> points = {racer._position.first, racer._positionExtra.second, racer._positionExtra.first, racer._position.second,
                                 racer._bottomCenter};  // 0, 1, 2, 3, 4 // вектор для удобства работы
    std::map<uint8_t, float> distancesToLine;           // мапа со значениями перпендикуляров до линии
    uint8_t k = 0;

    float factorForLineEquationA = _end.y - _start.y;  // math calculations
    float factorForLineEquationB = _start.x - _end.x;
    float factorForLineEquationC = (_start.y * (_end.x - _start.x)) - (_start.x * (_end.y - _start.y));
    for (auto playerPoint : points) {
        float dividendForDistance =
            std::abs(factorForLineEquationA * playerPoint.x + factorForLineEquationB * playerPoint.y + factorForLineEquationC);  // math calculations
        auto distanceFromPointToLine =
            static_cast<float>(dividendForDistance / std::sqrt(std::pow(factorForLineEquationA, 2) + std::pow(factorForLineEquationB, 2)));
        distancesToLine.insert(std::make_pair(k++, distanceFromPointToLine));
    }
    std::function comp = [](const std::pair<uint8_t, float> &rhs, const std::pair<uint8_t, float> &lhs) {
        if ((rhs.first == 4 && rhs.second <= 5) || (lhs.first == 4 && lhs.second <= 5)) {
            return rhs.second < lhs.second;
        } else if (rhs.first == 4) {
            return false;
        } else if (lhs.first == 4) {
            return true;
        }
        return rhs.second < lhs.second;
    };
    auto minDistance = std::min_element(distancesToLine.begin(), distancesToLine.end(), comp);

    auto lineAngle = std::atan((_end.y - _start.y) / (_end.x - _start.x)) * toDegree;
    float pushAngle = getPushAngle(racer._center, _start, _end, lineAngle);
    auto kDistanceToCenter = static_cast<float>((1 / distancesToLine.at(4)));

    if (minDistance->first == 1 || minDistance->first == 3 || minDistance->first == 4) {  // front
        if ((isPointOnTheLeftSideFromLine(racer._position.second, _start, _end) != isPointOnTheLeftSideFromLine(racer._bottomCenter, _start, _end)) ||
            (isPointOnTheLeftSideFromLine(racer._positionExtra.second, _start, _end) != isPointOnTheLeftSideFromLine(racer._bottomCenter, _start, _end))) {
            pushAngle = getPushAngle(racer._position.first, _start, _end, lineAngle) - 180;
        }

        float extraAccelerateX = static_cast<float>(1.1) * std::cos(pushAngle * toRadian) * std::abs(racer._speed.speedX);
        float extraAccelerateY = static_cast<float>(1.1) * -std::sin(pushAngle * toRadian) * std::abs(racer._speed.speedY);
        controller.updatePosition(racer, {static_cast<float>(racer._center.x + 0.6 * std::cos(pushAngle * toRadian)),
                                          static_cast<float>(racer._center.y + 0.6 * -std::sin(pushAngle * toRadian))});
        controller.changeSpeed(racer, false, extraAccelerateX, extraAccelerateY);
    } else if ((minDistance->first == 0 || minDistance->first == 2) || (isPointOnTheLeftSideFromLine(racer._position.first, _start, _end) !=
                                                                        isPointOnTheLeftSideFromLine(racer._position.second, _start, _end))) {  // bottom
        controller.changeSpeed(racer, false, static_cast<float>(0.5) * std::cos(racer._rotation * toRadian) * kDistanceToCenter,
                               static_cast<float>(0.5) * -std::sin(racer._rotation * toRadian) * kDistanceToCenter);
        controller.changeRotationSpeed(command, racer, 0.01);
    }
}

std::vector<Line> Arc::getVectorOfLinesForApproximation(int iteration, float radius, Arc &arc) {
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

bool Arc::intersect(Point &playerTopLeft, Point &playerTopRight, Point &playerBottomLeft, Point &playerBottomRight, Point &playerBottomCenter) {
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
    std::vector<Line> approximatedLines = this->getVectorOfLinesForApproximation(iteration, radius, initArc);

    bool isIntersects = false;
    for (auto &line : approximatedLines) {
        if (line.intersect(playerTopLeft, playerTopRight, playerBottomLeft, playerBottomRight, playerBottomCenter)) {
            isIntersects = true;
        }
    }

    return isIntersects;
}

// float getPointAngle(const Point &center, const Point &point) {
//     float pointAngle = (-std::atan((center.y - point.y) / (center.x - point.x)) * toDegree);
//
//     if (pointAngle <= 0 && point.x < center.x && point.y < center.y) {
//         pointAngle += 180;
//     }
//     if (pointAngle <= 0 && point.x > center.x && point.y > center.y) {
//         pointAngle += 180;
//     }
//
//     return pointAngle;
// }

// void Arc::collision(Racer &racer, RacerController &controller, Command command) {
//     std::vector<Point> points = {racer._position.first, racer._positionExtra.second, racer._positionExtra.first, racer._position.second,
//                                  racer._bottomCenter};  // 0, 1, 2, 3, 4
//     std::map<uint8_t, float> distancesToArcCenter;
//     uint8_t k = 0;
//     float radius = getArcRadius(_center, _start);
//     for (auto playerPoint : points) {
//         auto distanceFromPointToArc = static_cast<float>(std::sqrt(std::pow(_center.x - playerPoint.x, 2) + std::pow(_center.y - playerPoint.y, 2)));
//         distancesToArcCenter.insert(std::make_pair(k++, distanceFromPointToArc));
//     }
//     std::function comp = [&radius](const std::pair<uint8_t, float> &rhs, const std::pair<uint8_t, float> &lhs) {
//         return std::abs(rhs.second - radius) < std::abs(lhs.second - radius);
//     };
//     std::_Rb_tree_iterator<std::pair<const uint8_t, float>> minDistanceToArc = std::min_element(distancesToArcCenter.begin(), distancesToArcCenter.end(),
//     comp); float pointAngle = getPointAngle(_center, points.at(minDistanceToArc->first));
//
//     float tangentPointX = _center.x + (radius * std::cos(pointAngle * toRadian));
//     float tangentPointY = _center.y + (radius * -std::sin(pointAngle * toRadian));
//
//     float kLineCoefficient = (tangentPointY - _center.y) / (tangentPointX - _center.x);
//     float kTangentLineCoefficient = -1 / kLineCoefficient;
//
//     float x1 = _center.x - radius;
//     float y1 = kTangentLineCoefficient * x1 - kTangentLineCoefficient * tangentPointX + tangentPointY;
//     Point start = {x1, y1};
//     float x2 = _center.x + radius;
//     float y2 = kTangentLineCoefficient * x2 - kTangentLineCoefficient * tangentPointX + tangentPointY;
//     Point end = {x2, y2};
//
//     Line line(start, end, {0, 0});
//     line.collision(racer, controller, command);
//
//     float d = 0;
// }

void Arc::collision(Racer &racer, RacerController &controller, Command command) {
    std::vector<Point> points = {racer._position.first,  racer._positionExtra.second, racer._positionExtra.first,
                                 racer._position.second, racer._bottomCenter,         racer._center};  // 0, 1, 2, 3, 4, 5
    std::map<uint8_t, float> distancesToArcCenter;
    uint8_t k = 0;
    float radius = getArcRadius(_center, _start);
    for (auto playerPoint : points) {
        auto distanceFromPointToArc = static_cast<float>(std::sqrt(std::pow(_center.x - playerPoint.x, 2) + std::pow(_center.y - playerPoint.y, 2)));
        distancesToArcCenter.insert(std::make_pair(k++, distanceFromPointToArc));
    }
    std::function comp = [&radius](const std::pair<uint8_t, float> &rhs, const std::pair<uint8_t, float> &lhs) {
        float rhsR = std::abs(rhs.second - radius);
        float lhsR = std::abs(lhs.second - radius);
        if ((rhs.first == 4 && rhsR <= 5) || (lhs.first == 4 && lhsR <= 5)) {
            return rhsR < lhsR;
        } else if (rhs.first == 4) {
            return false;
        } else if (lhs.first == 4) {
            return true;
        }
        return rhsR < lhsR;
    };

    auto minDistanceToArc = std::min_element(distancesToArcCenter.begin(), distancesToArcCenter.end(), comp);
    auto pushAngle = getArcPushAngle(distancesToArcCenter, radius, _center, points);

    if ((minDistanceToArc->first == 1 || minDistanceToArc->first == 3 || minDistanceToArc->first == 4)) {  // front
        float extraAccelerateX = static_cast<float>(1.1) * std::cos(pushAngle.first * toRadian) * std::abs(racer._speed.speedX);
        float extraAccelerateY = static_cast<float>(1.1) * -std::sin(pushAngle.first * toRadian) * std::abs(racer._speed.speedY);
        controller.updatePosition(racer, {static_cast<float>(racer._center.x + 0.3 * std::cos(pushAngle.first * toRadian)),
                                          static_cast<float>(racer._center.y + 0.3 * -std::sin(pushAngle.first * toRadian))});
        controller.changeSpeed(racer, false, extraAccelerateX, extraAccelerateY);
    } else if ((minDistanceToArc->first == 0 || minDistanceToArc->first == 2)) {  // bottom
        auto kDistanceToCenter = static_cast<float>((1 / std::abs((distancesToArcCenter.at(4) - radius))));

        controller.changeSpeed(racer, false, static_cast<float>(1.5) * std::cos(racer._rotation * toRadian) * kDistanceToCenter,
                               static_cast<float>(1.5) * -std::sin(racer._rotation * toRadian) * kDistanceToCenter);
        controller.changeRotationSpeed(command, racer, 0.01);
    }
}

bool Rectangle::intersect(Point &playerTopLeft, Point &playerTopRight, Point &playerBottomLeft, Point &playerBottomRight, Point &playerBottomCenter) {
    std::vector<Point> points = {playerTopLeft, playerTopRight, playerBottomLeft, playerBottomRight, playerBottomCenter};

    float figureTopPoint = std::max(_start.y, _end.y);
    float figureBottomPoint = std::min(_start.y, _end.y);
    float figureRightPoint = std::max(_start.x, _end.x);
    float figureLeftPoint = std::min(_start.x, _end.x);

    size_t playersAnglesInsideRectangle = 0;

    for (auto &playerPoint : points) {
        if (playerPoint.x >= figureLeftPoint && playerPoint.x <= figureRightPoint && playerPoint.y >= figureBottomPoint && playerPoint.y <= figureTopPoint) {
            playersAnglesInsideRectangle++;
        }
    }

    if (playersAnglesInsideRectangle > 1) {
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

void AbstractElement::init(int stage) { _drObj->init(stage); }
void Portal::collision(Racer &racer, RacerController &controller, Command command) { racer._teleport = true; }
