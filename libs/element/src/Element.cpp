#include <AbstractElement.h>
#include <algorithm>
#include <cmath>
#include <map>
#include <vector>

#include "Element.h"
#include "MathCalculation.h"

constexpr float eps = 3;
constexpr float toRadian = M_PI / 180;
constexpr float toDegree = 180 / M_PI;
constexpr float approximationDegree = 10;
constexpr size_t defaultCenterX = 0;
constexpr size_t defaultCenterY = 0;


void Accelerator::collision(Racer &racer, RacerController &controller, Command command) {
    float extraAccelerateX = static_cast<float>(0.06) * std::cos(racer._rotation * toRadian) * racer._speed.speedX;
    float extraAccelerateY = static_cast<float>(0.06) * -std::sin(racer._rotation * toRadian) * racer._speed.speedY;

    controller.changeSpeed(racer, false, extraAccelerateX, extraAccelerateY);
}


void Delayer::collision(Racer &racer, RacerController &controller, Command command) {
    float extraAccelerateX = static_cast<float>(0.15) * -std::cos(racer._rotation * toRadian) * std::abs(racer._speed.speedX);
    float extraAccelerateY = static_cast<float>(0.15) * std::sin(racer._rotation * toRadian) * std::abs(racer._speed.speedY);

    controller.changeSpeed(racer, false, extraAccelerateX, extraAccelerateY);
}

void Finish::collision(Racer &racer, RacerController &controller, Command command) { racer.finished = std::make_tuple(true, 0); }

void Line::collision(Racer &racer, RacerController &controller, Command command) {
    std::vector<Point> points = {racer._position.first, racer._positionExtra.second, racer._positionExtra.first, racer._position.second};  // 0, 1, 2, 3
    std::map<uint8_t, float> distancesToLine;
    uint8_t k = 0;

    float factorForLineEquationA = _end.y - _start.y;
    float factorForLineEquationB = _start.x - _end.x;
    float factorForLineEquationC = (_start.y * (_end.x - _start.x)) - (_start.x * (_end.y - _start.y));
    for (auto playerPoint : points) {

        float dividendForDistance = std::abs(factorForLineEquationA * playerPoint.x + factorForLineEquationB * playerPoint.y + factorForLineEquationC);
        auto distanceFromPointToLine =
            static_cast<float>(dividendForDistance / std::sqrt(std::pow(factorForLineEquationA, 2) + std::pow(factorForLineEquationB, 2)));
        distancesToLine.insert(std::make_pair(k++, distanceFromPointToLine));
    }
    auto dividendForDistance =
        static_cast<float>(std::abs(factorForLineEquationA * racer._center.x + factorForLineEquationB * racer._center.y + factorForLineEquationC));
    auto distanceToCenter = static_cast<float>(dividendForDistance / std::sqrt(std::pow(factorForLineEquationA, 2) + std::pow(factorForLineEquationB, 2)));

    std::function comp = [](const std::pair<uint8_t, float> &rhs, const std::pair<uint8_t, float> &lhs) { return rhs.second < lhs.second; };
    auto minDistance = std::min_element(distancesToLine.begin(), distancesToLine.end(), comp);

    auto lineAngle = std::atan((_end.y - _start.y) / (_end.x - _start.x)) * toDegree;
    float pushAngle = getPushAngle(racer._center, _start, _end, lineAngle);
    float kSpeedX = std::abs(racer._speed.speedX / 5);
    float kSpeedY = std::abs(racer._speed.speedY / 5);
    float kDistanceToCenter = (4 / distanceToCenter);

    if ((minDistance->first == 1 || minDistance->first == 3)) {  // front
        if ((isPointOnTheLeftSideFromLine(racer._position.second, _start, _end) != isPointOnTheLeftSideFromLine(racer._center, _start, _end)) ||
            (isPointOnTheLeftSideFromLine(racer._positionExtra.second, _start, _end) != isPointOnTheLeftSideFromLine(racer._center, _start, _end))) {
            pushAngle = getPushAngle(racer._position.first, _start, _end, lineAngle) - 180;
        }
        float extraAccelerateX = static_cast<float>(1.2) * std::cos(pushAngle * toRadian) * std::abs(racer._speed.speedX);
        float extraAccelerateY = static_cast<float>(1.2) * -std::sin(pushAngle * toRadian) * std::abs(racer._speed.speedY);
        controller.updatePosition(racer, {static_cast<float>(racer._center.x + 0.2 * std::cos(pushAngle * toRadian)),
                                          static_cast<float>(racer._center.y + 0.2 * -std::sin(pushAngle * toRadian))});
        controller.changeSpeed(racer, false, extraAccelerateX, extraAccelerateY);
    } else if ((minDistance->first == 0 || minDistance->first == 2) || (isPointOnTheLeftSideFromLine(racer._position.first, _start, _end) !=
                                                                        isPointOnTheLeftSideFromLine(racer._position.second, _start, _end))) {  // bottom
        controller.changeSpeed(racer, false, static_cast<float>(0.37) * std::cos(racer._rotation * toRadian) * kSpeedX * kDistanceToCenter,
                               static_cast<float>(0.37) * -std::sin(racer._rotation * toRadian) * kSpeedY * kDistanceToCenter);
        controller.changeRotationSpeed(command, racer, 0.15);
    }
}

void Arc::collision(Racer &racer, RacerController &controller, Command command) {
    std::vector<Point> points = {racer._position.first, racer._positionExtra.second, racer._positionExtra.first, racer._position.second};  // 0, 1, 2, 3
    std::map<uint8_t, float> distancesToArcCenter;
    uint8_t k = 0;
    float radius = getArcRadius(_center, _start);
    for (auto playerPoint : points) {
        auto distanceFromPointToArc = static_cast<float>(std::sqrt(std::pow(_center.x - playerPoint.x, 2) + std::pow(_center.y - playerPoint.y, 2)));
        distancesToArcCenter.insert(std::make_pair(k++, distanceFromPointToArc));
    }
    auto distanceFromCenterToArcCenter = static_cast<float>(std::sqrt(std::pow(_center.x - racer._center.x, 2) + std::pow(_center.y - racer._center.y, 2)));
    std::function comp = [](const std::pair<uint8_t, float> &rhs, const std::pair<uint8_t, float> &lhs) { return rhs.second < lhs.second; };
    std::_Rb_tree_iterator<std::pair<const uint8_t, float>> maxDistance;
    float pushAngle = getArcPushAngle(distanceFromCenterToArcCenter, radius, _center, racer._center);
    if (distanceFromCenterToArcCenter > radius) {
        maxDistance = std::min_element(distancesToArcCenter.begin(), distancesToArcCenter.end(), comp);
    } else {
        maxDistance = std::max_element(distancesToArcCenter.begin(), distancesToArcCenter.end(), comp);
    }

    if ((maxDistance->first == 1 || maxDistance->first == 3)) {                                   // front
        if ((distanceFromCenterToArcCenter > radius && distancesToArcCenter[1] + 2 <= radius) ||  // critical
            (distanceFromCenterToArcCenter < radius && distancesToArcCenter[1] - 2 >= radius)) {
            pushAngle = getArcPushAngle(distancesToArcCenter[1], radius, _center, points[1]);
        } else if ((distanceFromCenterToArcCenter > radius && distancesToArcCenter[3] + 2 <= radius) ||
                   (distanceFromCenterToArcCenter < radius && distancesToArcCenter[3] - 2 >= radius)) {
            pushAngle = getArcPushAngle(distancesToArcCenter[3], radius, _center, points[3]);
        }
        float extraAccelerateX = static_cast<float>(1.2) * std::cos(pushAngle * toRadian) * std::abs(racer._speed.speedX);
        float extraAccelerateY = static_cast<float>(1.2) * -std::sin(pushAngle * toRadian) * std::abs(racer._speed.speedY);
        controller.updatePosition(racer, {static_cast<float>(racer._center.x + 0.3 * std::cos(pushAngle * toRadian)),
                                          static_cast<float>(racer._center.y + 0.3 * -std::sin(pushAngle * toRadian))});
        controller.changeSpeed(racer, false, extraAccelerateX, extraAccelerateY);
    } else if ((maxDistance->first == 0 || maxDistance->first == 2)) {  // bottom
        float kSpeedX = std::abs(racer._speed.speedX / 2);
        float kSpeedY = std::abs(racer._speed.speedY / 2);
        controller.changeSpeed(racer, false, static_cast<float>(0.15) * std::cos(racer._rotation * toRadian) * kSpeedX,
                               static_cast<float>(0.15) * -std::sin(racer._rotation * toRadian) * kSpeedY);
        controller.changeRotationSpeed(command, racer, 0.15);
    }
}

