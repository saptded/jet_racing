//
// Created by Kseny
//

#pragma once

#include "drawableObject.hpp"
#include "utils.hpp"
#include <SFML/Graphics/VertexArray.hpp>

class DrawableArc: public DrawableObject {
public:
    //void create(std::weak_ptr<abstractElement> element) override;
    void create(abstractElement& element) override;
    void draw(abstractElement& element, sf::RenderWindow& window) override {};
    void draw(sf::RenderWindow& window) override;

private:
    sf::VertexArray arcs;
};