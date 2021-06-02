//
// Created by Kseny
//

#pragma once

#include "racer.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio/Music.hpp>
#include <iostream>
#include <sfColor.hpp>

class sfViewerDetails {
public:
    explicit sfViewerDetails(float _windowWidth, float _windowHeight);

    void update(Racer &racer);

    void display(sf::RenderWindow &window, int stage);

private:
    sf::Texture bgImage;
    sf::RectangleShape bg;
    sf::View view;
    sfColor colors;
    float viewHeight = 0;
    float viewWidth = 0;
    float windowWidth;
    float windowHeight;
    int viewK = 3;
    sf::Vector2f prevPos;
    sf::Font font;
    sf::Text text;
    int counter = 0;
    sf::Music music;//создаем объект музыки
};