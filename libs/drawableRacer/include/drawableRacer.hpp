#pragma once

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <racer.hpp>

enum textureType{
    RACER_T,
    ENEMY_T,
    FINISHED_T
};

class DrawableRacer {
public:
    DrawableRacer() = delete;

    DrawableRacer(float width, float height, Point origin, int id, float rotation);

    void draw(const Racer &racer, sf::RenderWindow &window);

private:


    void loadSources();

    void changeFire(const Speed &speed);

    void setPos(const Point &center);
    void setPos(const std::pair<Point, Point> &position);
    void setPos(const std::pair<Point, Point> &pos, sf::RenderWindow &window);
    void setRot(const float &rotation);

    void drawWindow(sf::RenderWindow &window);
    sf::Sprite car;
    sf::Sprite fire;
    sf::Texture texture;
    sf::Image image;

//    sf::CircleShape pointBottom;
//    sf::CircleShape pointCenter;
//    sf::CircleShape point1;
//    sf::CircleShape point2;
};

