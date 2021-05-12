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
    void create (Racer& racer);
    void draw(Racer& racer, sf::RenderWindow& window);

private:
    void loadSources();
    void changeFire(Speed& speed);
    void setPos(std::pair<Point,Point>& position);
    void setRot(float& rotation);
    void drawWindow(sf::RenderWindow& window);
    sf::Sprite car;
    sf::Sprite fire;
    sf::Texture textureCar;
    sf::Texture textureFire;
    sf::Image imCar;
    sf::Image imFire;

};

