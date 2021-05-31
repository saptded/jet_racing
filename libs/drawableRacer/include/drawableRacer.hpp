#pragma once

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <racer.hpp>

class DrawableRacer {
public:
    DrawableRacer() = delete;

    DrawableRacer(float width, float height, Point origin, int id, float rotation, bool isOwn);

    void draw(const Racer &racer, sf::RenderWindow &window);

private:

    void loadSources(bool isOwn);

    void setPos(const Point &center);
    void setRot(const float &rotation);

    void drawWindow(sf::RenderWindow &window);
    sf::Sprite car;
    sf::Sprite fire;
    sf::Texture texture;
    sf::Image image;
};

