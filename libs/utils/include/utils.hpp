//
// Created by saptded on 15.04.2021.
//

#pragma once

#include <vector>
#include <iostream>

typedef struct Point {
    float x;
    float y;
} Point;

typedef struct Speed {
    int speedX;
    int speedY;
} Speed;

enum RotationDirection { left, right, none };

enum elementType {line, arcTime, arcNtime}; //....

typedef struct abstractElement {
    elementType type;
    Point start;
    Point end;
    Point centre;
} abstractElement;


