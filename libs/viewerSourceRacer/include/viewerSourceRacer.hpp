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
    explicit ViewerSourceRacer(Point* points);
    void setPos(float x, float y);
    void setRot(Point*);
    void drawRacer(sf::RenderWindow& window);
private:
    sf::RectangleShape car;
    sf::RectangleShape fire;
    float zeroAngle;
    float countAngle(Point* points);
};

