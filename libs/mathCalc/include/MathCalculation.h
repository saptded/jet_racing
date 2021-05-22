#pragma once

#include "mechanicalValues.hpp"

float findCosine(float xFirstProjection, float xSecondProjection, float yFirstProjection, float ySecondProjection);

bool isPointOnTheLeftSideFromLine(const Point &center, const Point &start, const Point &end);

bool isPointInZone(Point &playerPoint, Point &start, Point &end);
