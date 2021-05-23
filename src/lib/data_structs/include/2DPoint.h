//
// Created by dark0ghost on 23.05.2021.
//

#ifndef LIBSERVER_2DPOINT_H
#define LIBSERVER_2DPOINT_H
struct Point {
    Point(float posX, float posY) : x(posX), y(posY) {}
    float x;
    float y;
};

#endif //LIBSERVER_2DPOINT_H
