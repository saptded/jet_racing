//
// Created by Kseny
//

#pragma once

#include "../../mechanicalValues/include/mechanicalValues.hpp"
#include <AbstractElement.h>
#include <SFML/Graphics/RenderWindow.hpp>

class DrawableObject {
public:
    DrawableObject()
        : start({0, 0})
        , end({0, 0})
        , center({0, 0}){};
    DrawableObject(Point _start, Point _end, Point _center)
        : start(_start)
        , end(_end)
        , center(_center){};
    virtual void draw(sf::RenderWindow &window) = 0;
    void drawDynamic(sf::RenderWindow &window, Point _start, Point _end, Point _center){};
    virtual void init(int stage) = 0;

protected:
    Point start;
    Point end;
    Point center;
};