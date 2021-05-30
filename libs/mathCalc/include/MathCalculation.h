#pragma once

#include "mechanicalValues.hpp"
#include <utility>

bool isPointOnTheLeftSideFromLine(const Point &point, const Point &start, const Point &end);

float getPushAngle(Point &playerPoint, Point &start, Point &end, float lineAngle);

float getArcRadius(const Point &center, const Point &start);

std::pair<float, bool> getArcPushAngle(std::map<uint8_t, float> &distancesToArcCenter, float radius, Point &center, std::vector<Point> &points);