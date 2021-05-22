#pragma once

#include "mechanicalValues.hpp"

float findCosine(float xFirstProjection, float xSecondProjection, float yFirstProjection, float ySecondProjection);

bool isPointInZone(Point &playerPoint, Point &start, Point &end);
