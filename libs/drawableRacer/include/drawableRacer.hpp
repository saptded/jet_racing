//
// Created by Kseny
//

#pragma once

#include "response.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/VertexArray.hpp>

class drawableRacer {
public:
    void create (Racer& racer);
    void draw(Racer& racer, sf::RenderWindow& window);
private:
    void loadSources();
    void changeFire(Speed speed);
    void setPos(std::pair<Point,Point>& position);
    void setRot(float rotation);
    void createView();

    sf::Sprite car;
    sf::Sprite fire;
    sf::Texture textureCar;
    sf::Texture textureFire;
    sf::Image imCar;
    sf::Image imFire;

    sf::View view; // это странно но удобно...
};

