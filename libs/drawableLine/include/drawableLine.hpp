//
// Created by Kseny
//

#pragma once

#include "drawableObject.hpp"
#include "utils.hpp"
#include <SFML/Graphics/VertexArray.hpp>

class DrawableLine: public DrawableObject {
public:
    void create(abstractElement& element, int stage) override;
    void draw(sf::RenderWindow& window) override;
    void draw(abstractElement& element, sf::RenderWindow& window) override {};
private:
    sf::VertexArray lines;
};