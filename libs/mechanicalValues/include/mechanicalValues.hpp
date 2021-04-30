#pragma once

#include <vector>
#include <iostream>

typedef struct Point {
    double x;
    double y;
} Point;

typedef struct Speed {
    double speedX;
    double speedY;
} Speed;

enum Rotation { left, right, none };
