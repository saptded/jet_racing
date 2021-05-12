//
// Created by Kseny
//

#pragma once

#include "utils.hpp"
#include <SFML/Graphics/RenderWindow.hpp>

class DrawableObject {
public:
    virtual void create(abstractElement& element, int stage) = 0;
    virtual void draw(abstractElement& element, sf::RenderWindow& window) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
};