//
// Created by Kseny
//

#pragma once

#include "drawableObject.hpp"
#include "utils.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/VertexArray.hpp>

class DrawableArc: public DrawableObject {
public:
    void create(abstractElement& element, int stage) override;
    void draw(abstractElement& element, sf::RenderWindow& window) override {};
    void draw(sf::RenderWindow& window) override;
    float getAngle(Point&centre, Point&rad); // сделаны public для тестирования(
    float calcRadius(Point& one, Point& two); //
private:
    sf::VertexArray arcs[3];
};

class DrawableLine: public DrawableObject {
public:
    void create(abstractElement& element, int stage) override;
    void draw(sf::RenderWindow& window) override;
    void draw(abstractElement& element, sf::RenderWindow& window) override {};
private:
    sf::VertexArray lines[3];
};

// дальше реализаций пока нет

class DrawableAccelerator: public DrawableObject {
public:
    void create(abstractElement& element, int stage) override;
    void draw(sf::RenderWindow& window) override;
    void draw(abstractElement& element, sf::RenderWindow& window) override {};
private:
    sf::RectangleShape rect;
};

class DrawableDelayer: public DrawableObject {
public:
    void create(abstractElement& element, int stage) override;
    void draw(sf::RenderWindow& window) override;
    void draw(abstractElement& element, sf::RenderWindow& window) override {};
private:
    sf::RectangleShape rect;
};

class DrawablePortal: public DrawableObject {
public:
    void create(abstractElement& element, int stage) override;
    void draw(sf::RenderWindow& window) override;
    void draw(abstractElement& element, sf::RenderWindow& window) override {};
private:
    sf::RectangleShape rect;
};

class DrawableFinish: public DrawableObject {
public:
    void create(abstractElement& element, int stage) override;
    void draw(sf::RenderWindow& window) override;
    void draw(abstractElement& element, sf::RenderWindow& window) override {};
private:
    sf::RectangleShape rect;
};