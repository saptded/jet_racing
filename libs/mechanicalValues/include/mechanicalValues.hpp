#pragma once

#include <iostream>
#include <vector>

struct Point {
    Point(float posX, float posY)
        : x(posX)
        , y(posY) {}
    float x;
    float y;
};

struct Speed {
    float speedX;
    float speedY;
};

enum Command { left, right, none, finish };
