#pragma once

#include <utility>
#include "mechanicalValues.hpp"

float findCosine(float xFirstProjection, float xSecondProjection, float yFirstProjection, float ySecondProjection);

bool isPointOnTheLeftSideFromLine(const Point &center, const Point &start, const Point &end);

bool isPointInZone(Point &playerPoint, Point &start, Point &end);

float getPushAngle(Point &playerPoint, Point &start, Point &end, float lineAngle);

float getArcRadius(const Point &center, const Point &start);

std::pair<float, bool> getArcPushAngle(std::map<uint8_t, float> &distancesToArcCenter, float radius, Point &center, std::vector<Point> &points);