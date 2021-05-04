#pragma once

#include <iostream>
#include <vector>

typedef struct Point {
    double x;
    double y;
} Point;

typedef struct Speed {
    double speedX;
    double speedY;
} Speed;

enum Rotation { left, right, none };
