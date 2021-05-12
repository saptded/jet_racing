//
// Created by Kseny
//

#pragma once

#include "../../mechanicalValues/include/mechanicalValues.hpp"
#include <AbstractElement.h>
#include <SFML/Graphics/RenderWindow.hpp>

class DrawableObject {
public:
//    DrawableObject(Point start, Point end, Point center){};
    virtual void create(AbstractElement& element, int stage) = 0;
    virtual void draw(AbstractElement& element, sf::RenderWindow& window) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
};