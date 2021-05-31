#pragma once

#include "drawableObject.hpp"
#include "mechanicalValues.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/VertexArray.hpp>

static const float WEIGHT_K = 5;

class DrawableArc : public DrawableObject {
public:
    DrawableArc(Point start, Point end, Point center): DrawableObject(start, end, center) {};
    void draw(sf::RenderWindow &window) override;
    void init(int stage) override;

private:
    float getAngle(Point &centre, Point &rad);
    float calcRadius(Point &one, Point &two);
    //sf::VertexArray arcs[3];
    std::vector<sf::VertexArray> arcs;
    float weightK = WEIGHT_K;
};

class DrawableLine : public DrawableObject {
public:
    DrawableLine(Point start, Point end, Point center): DrawableObject(start, end, center) {};
    void draw(sf::RenderWindow &window) override;
    void init(int stage) override;
private:
    sf::VertexArray lines[3];
    float weightK = WEIGHT_K;
};

class DrawableAccelerator : public DrawableObject {
public:
    DrawableAccelerator(Point start, Point end, Point center);
    void draw(sf::RenderWindow &window) override;
    void init(int stage) override {};
private:
    sf::RectangleShape rect;
};

class DrawableDelayer : public DrawableObject {
public:
    DrawableDelayer(Point start, Point end, Point center);
    void draw(sf::RenderWindow &window) override;
    void init(int stage) override {};
private:
    sf::RectangleShape rect;
};

class DrawableLineRect : public DrawableObject{
public:
    DrawableLineRect(Point start, Point end, Point center);
    void draw(sf::RenderWindow &window) override;
    void init(int stage) override;
protected:
    std::vector<DrawableLine> lineRect;
};

class DrawableFinish: public DrawableLineRect {
public:
    DrawableFinish(Point start, Point end, Point center): DrawableLineRect(start, end, center){};
    void init(int stage) override;
};

class DrawablePortal: public DrawableLineRect {
public:
    DrawablePortal(Point start, Point end, Point center): DrawableLineRect(start, end, center){};
    void init(int stage) override;
};

class DrawablePropeller : public DrawableObject {
public:
    DrawablePropeller(Point start, Point end, Point center);
    void draw(sf::RenderWindow &window) override;
    void drawDynamic(sf::RenderWindow &window, Point _start, Point _end, Point _center){};
    void init(int stage) override;
private:
    DrawableLine line;
    DrawableArc arc;
};