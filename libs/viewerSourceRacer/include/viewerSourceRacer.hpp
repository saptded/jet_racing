//
// Created by Kseny
//

#pragma once



#include "response.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/VertexArray.hpp>

class ViewerSourceRacer {
public:
    explicit ViewerSourceRacer(float width, float height, int id);
    void setPos(Point& position);
    void setRot(float rotation);
    void drawRacer(sf::RenderWindow& window);
private:
    sf::RectangleShape car;
    sf::RectangleShape fire;
};

