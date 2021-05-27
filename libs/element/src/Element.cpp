#include <algorithm>
#include <cmath>
#include <vector>

#include "Element.h"
#include "MathCalculation.h"

constexpr float kEps = 1e-7;
constexpr float toRadian = M_PI / 180;
constexpr float toDegree = 180 / M_PI;
constexpr float approximationDegree = 1;
constexpr size_t defaultCenterX = 0;
constexpr size_t defaultCenterY = 0;

bool Line::intersect(Point &playerTopLeft, Point &playerTopRight, Point &playerBottomLeft, Point &playerBottomRight) {
    std::vector<Point> points = {playerTopLeft, playerTopRight, playerBottomLeft, playerBottomRight};
    bool isIntesects = false;

    for (auto playerPoint : points) {
        if (isPointInZone(playerPoint, _start, _end)) {
            float factorForLineEquationA = _end.y - _start.y;
            float factorForLineEquationB = _start.x - _end.x;
            float factorForLineEquationC = (_start.y * (_end.x - _start.x)) - (_start.x * (_end.y - _start.y));

            float dividendForDistance = std::abs(factorForLineEquationA * playerPoint.x + factorForLineEquationB * playerPoint.y + factorForLineEquationC);

            if (dividendForDistance == 0) {
                isIntesects = true;
            }

            auto distanceFromPointToLine = dividendForDistance / std::sqrt(std::pow(factorForLineEquationA, 2) + std::pow(factorForLineEquationB, 2));

            if (distanceFromPointToLine < kEps) {
                isIntesects = true;
            }
        }
    }

    return isIntesects;
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
    std::vector<Line> approximatedLines = this->getVectorOfLinesForApproximation(iteration, radius, initArc);

    bool isIntersects = false;
    for (auto &line : approximatedLines) {
        if (line.intersect(playerTopLeft, playerTopRight, playerBottomLeft, playerBottomRight)) {
            isIntersects = true;
        }
    }

    return isIntersects;
}

bool Rectangle::intersect(Point &playerTopLeft, Point &playerTopRight, Point &playerBottomLeft, Point &playerBottomRight) {
    std::vector<Point> points = {playerTopLeft, playerTopRight, playerBottomLeft, playerBottomRight};

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
