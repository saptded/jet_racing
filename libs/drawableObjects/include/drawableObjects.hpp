//
// Created by Kseny
//

#pragma once

#include "mechanicalValues.hpp"
//#include "AbstractElement.h"
#include "drawableObject.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/VertexArray.hpp>

class DrawableArc: public DrawableObject {
public:
    DrawableArc(Point start, Point end, Point center);
    //void create(AbstractElement& element, int stage) override;
    //void draw(AbstractElement& element, sf::RenderWindow& window) override {};

    void draw(sf::RenderWindow& window) override;
    float getAngle(Point&centre, Point&rad); // сделаны public для тестирования(
    float calcRadius(Point& one, Point& two); //
private:
    sf::VertexArray arcs[3];
};

class DrawableLine: public DrawableObject {
public:
    DrawableLine(Point start, Point end, Point center);
    //void create(AbstractElement& element, int stage) override;
    void draw(sf::RenderWindow& window) override;
    //void draw(AbstractElement& element, sf::RenderWindow& window) override {};
private:
    sf::VertexArray lines[3];
};

// дальше реализаций пока нет

class DrawableAccelerator: public DrawableObject {
public:
    DrawableAccelerator(Point start, Point end, Point center);
    //void create(AbstractElement& element, int stage) override;
    void draw(sf::RenderWindow& window) override;
    //void draw(AbstractElement& element, sf::RenderWindow& window) override {};
private:
    sf::RectangleShape rect;
};

class DrawableDelayer: public DrawableObject {
public:
    DrawableDelayer(Point start, Point end, Point center);
    //void create(AbstractElement& element, int stage) override;
    void draw(sf::RenderWindow& window) override;
    //void draw(AbstractElement& element, sf::RenderWindow& window) override {};
private:
    sf::RectangleShape rect;
};

class DrawablePortal: public DrawableObject {
public:
    DrawablePortal(Point start, Point end, Point center);
    //void create(AbstractElement& element, int stage) override;
    void draw(sf::RenderWindow& window) override;
    //void draw(AbstractElement& element, sf::RenderWindow& window) override {};
private:
    sf::RectangleShape rect;
};

class DrawableFinish: public DrawableObject {
public:
    DrawableFinish(Point start, Point end, Point center);
    //void create(AbstractElement& element, int stage) override;
    void draw(sf::RenderWindow& window) override;
    //void draw(AbstractElement& element, sf::RenderWindow& window) override {};
private:
    sf::RectangleShape rect;
};

class DrawablePropeller: public DrawableObject {
public:
    DrawablePropeller(Point start, Point end, Point center);
    //void create(AbstractElement& element, int stage) override;
    void draw(sf::RenderWindow& window) override;
    void drawRotated(sf::RenderWindow& window, float angle);
    //void draw(AbstractElement& element, sf::RenderWindow& window) override {};
private:
    sf::RectangleShape rect;
};