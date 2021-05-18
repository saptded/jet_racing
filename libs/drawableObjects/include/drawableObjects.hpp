#pragma once

#include "mechanicalValues.hpp"
#include "drawableObject.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/VertexArray.hpp>

class DrawableArc : public DrawableObject {
public:
    DrawableArc(Point start, Point end, Point center);
    void draw(sf::RenderWindow &window) override;
    void change(int stage) override;
private:
    float getAngle(Point &centre, Point &rad);
    float calcRadius(Point &one, Point &two);
    sf::VertexArray arcs[3];
    float weightK = 5;
};

class DrawableLine : public DrawableObject {
public:
    DrawableLine(Point start, Point end, Point center);
    void draw(sf::RenderWindow& window) override;
    void change(int stage) override;
private:
    sf::VertexArray lines[3];
    float weightK = 5;
};

// дальше реализаций пока нет

class DrawableAccelerator : public DrawableObject {
public:
    DrawableAccelerator(Point start, Point end, Point center);
    void draw(sf::RenderWindow& window) override;
    void change(int stage) override{};
private:
    sf::RectangleShape rect;
};

class DrawableDelayer : public DrawableObject {
public:

    DrawableDelayer(Point start, Point end, Point center);
    void draw(sf::RenderWindow& window) override;
    void change(int stage) override{};
private:
    sf::RectangleShape rect;
};

class DrawablePortal : public DrawableObject {
public:

    DrawablePortal(Point start, Point end, Point center);
    void draw(sf::RenderWindow& window) override;
    void change(int stage) override{};
private:
    sf::RectangleShape rect;
};

class DrawableFinish : public DrawableObject {
public:
    DrawableFinish(Point start, Point end, Point center);
    void draw(sf::RenderWindow& window) override;
    void change(int stage) override{};
private:
    sf::RectangleShape rect;
};

class DrawablePropeller: public DrawableObject {
public:
    DrawablePropeller(Point start, Point end, Point center);
    void draw(sf::RenderWindow& window) override;
    void drawDynamic(sf::RenderWindow& window,  Point _start, Point _end, Point _center);
    void change(int stage) override{};
private:
    sf::RectangleShape rect;
};