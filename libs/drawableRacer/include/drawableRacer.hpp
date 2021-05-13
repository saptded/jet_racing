//
// Created by Kseny
//

#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <racer.hpp>

class DrawableRacer {
public:
    DrawableRacer() = delete;
    DrawableRacer(float width, float height, int id);
    void draw(const Racer &racer, sf::RenderWindow &window);

private:
    void loadSources();
    void changeFire(const Speed &speed);
    void setPos(const std::pair<Point, Point> &position);
    void setRot(const float &rotation);
    void drawWindow(sf::RenderWindow &window);
    sf::Sprite car;
    sf::Sprite fire;
    sf::Texture textureCar;
    sf::Texture textureFire;
    sf::Image imCar;
    sf::Image imFire;
};
