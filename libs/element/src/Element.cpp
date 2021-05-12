#include <algorithm>
#include <cmath>
#include <vector>

#include "Element.h"
#include "MathCalculation.h"

constexpr float eps = 1e-7;
constexpr float lambdaMin = 0.994444444;
constexpr float lambdaMax = 1.005555556;
constexpr float straightAngle = 180;
constexpr float toRadian = M_PI / 180;
constexpr float toDegree = 180 / M_PI;
constexpr float approximationDegree = 30;
constexpr size_t defaultCenterX = 0;
constexpr size_t defaultCenterY = 0;

// bool Idle::intersect(Point playerTopLeft, Point playerTopRight, Point playerBottomLeft, Point playerBottomRight) {
//     return false;
// }
//
// bool Idle::isElementDynamic() {
//     return false;
// }

bool Line::isElementDynamic() { return false; }

bool Arc::isElementDynamic() { return false; }

bool Propeller::isElementDynamic() { return isDynamic; }

bool Accelerator::isElementDynamic() { return false; }

bool Delayer::isElementDynamic() { return false; }

bool Portal::isElementDynamic() { return false; }

bool Finish::isElementDynamic() { return false; }

bool Line::intersect(Point playerTopLeft, Point playerTopRight, Point playerBottomLeft, Point playerBottomRight) {
    std::vector<Point> points = {playerTopLeft, playerTopRight, playerBottomLeft, playerBottomRight};

    for (auto it : points) {
        if ((it.x == _start.x && it.y == _start.y) || (it.x == _end.x && it.y == _end.y)) {
            return true;
        }

        float projectionPlayerFigureStartX = _start.x - it.x;
        float projectionPlayerFigureEndX = _end.x - it.x;
        float projectionPlayerFigureStartY = _start.y - it.y;
        float projectionPlayerFigureEndY = _end.y - it.y;

        float cosinePlayerFigure =
            findCosine(projectionPlayerFigureStartX, projectionPlayerFigureEndX, projectionPlayerFigureStartY, projectionPlayerFigureEndY);

        if (cosinePlayerFigure == 1) {
            return false;
        }

        if (1 - cosinePlayerFigure < eps) {
            if ((std::acos(cosinePlayerFigure) * toDegree > straightAngle * lambdaMin &&
                 std::acos(cosinePlayerFigure) * toDegree < straightAngle * lambdaMax) ||
                (std::acos(cosinePlayerFigure) * toDegree > -(straightAngle * lambdaMax) &&
                 std::acos(cosinePlayerFigure) * toDegree > -(straightAngle * lambdaMin))) {
                return true;
            }
        }
    }

    return false;
}
bool Arc::intersect(Point playerTopLeft, Point playerTopRight, Point playerBottomLeft, Point playerBottomRight) {
    float xProjectionCenterStart = _center.x - _start.x;
    float yProjectionCenterStart = _center.y - _start.y;
    float xProjectionCenterEnd = _center.x - _end.x;
    float yProjectionCenterEnd = _center.y - _end.y;

    // TODO передать сразу точки center, start и end
    float cosineOfAngleStartEnd = findCosine(xProjectionCenterStart, xProjectionCenterEnd, yProjectionCenterStart, yProjectionCenterEnd);

    //    if (cosineOfAngleStartEnd > 1 || cosineOfAngleStartEnd < -1) {
    //        return false;
    //    }

    float degree = std::acos(cosineOfAngleStartEnd) * toDegree;

    float radius;
    if (_center.x != _start.x) {
        radius = std::abs(_center.x - _start.x);
    } else {
        radius = std::abs(_center.y - _start.y);
    }

    std::vector<Line> approximatedLines;

    // TODO посчитать вручную количество итераций

    // TODO вынести цикл в отдельную функцию и возваращть вектор
    for (int i = approximationDegree; i <= degree; i += approximationDegree) {
        float projectionOfAdjacentAngle = radius * std::cos(i * toRadian);
        float projectionOfOppositeAngle = radius * std::sin(i * toRadian);

        float newPointX;
        float newPointY;

        if (i < degree) {
            if (_center.x > _start.x) {
                newPointX = _center.x - projectionOfAdjacentAngle;
                newPointY = _center.y - projectionOfOppositeAngle;
            }

            if (_center.x < _start.x) {
                newPointX = _center.x + projectionOfAdjacentAngle;
                newPointY = _center.y + projectionOfOppositeAngle;
            }

            if (_center.y > _start.y) {
                newPointX = _center.x + projectionOfOppositeAngle;
                newPointY = _center.y - projectionOfAdjacentAngle;
            }

            if (_center.y < _start.y) {
                newPointX = _center.x - projectionOfOppositeAngle;
                newPointY = _center.y + projectionOfAdjacentAngle;
            }
        }

        if (i == degree) {  // TODO: if last iteration
            newPointX = _end.x;
            newPointY = _end.y;
        }

        Point newEnd = {newPointX, newPointY};
        Point center = {defaultCenterX, defaultCenterY};

        Line line(_start, newEnd, center);

        approximatedLines.push_back(line);

        std::swap(_start, newEnd);
    }

    for (auto &it : approximatedLines) {
        if (it.intersect(playerTopLeft, playerTopRight, playerBottomLeft, playerBottomRight)) {
            return true;
        }
    }

    return false;
}

bool Rectangle::intersect(Point playerTopLeft, Point playerTopRight, Point playerBottomLeft, Point playerBottomRight) {
    std::vector<Point> points = {playerTopLeft, playerTopRight, playerBottomLeft, playerBottomRight};

    auto minmaxHeight = std::minmax_element(points.begin(), points.end(), [](Point const &lhs, Point const &rhs) { return lhs.y < rhs.y; });

    auto minmaxWidth = std::minmax_element(points.begin(), points.end(), [](Point const &lhs, Point const &rhs) { return lhs.x < rhs.x; });

    float playerTop = minmaxHeight.second->y;
    float playerBottom = minmaxHeight.first->y;
    float playerRight = minmaxWidth.second->x;
    float playerLeft = minmaxWidth.first->x;

    float figureTop = std::max(_start.y, _end.y);
    float figureBottom = std::min(_start.y, _end.y);
    float figureRight = std::max(_start.x, _end.x);
    float figureLeft = std::min(_start.x, _end.x);

    if ((playerTop <= figureTop || playerBottom >= figureBottom) && (playerRight <= figureRight || playerLeft >= figureLeft)) {
        return true;
    }

    return false;
}
