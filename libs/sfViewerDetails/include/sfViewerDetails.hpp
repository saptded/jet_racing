//
// Created by Kseny
//

#pragma once

#include "racer.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sfColor.hpp>

class sfViewerDetails {
public:
    //explicit sfViewerDetails(sf::RenderWindow &window);
    sfViewerDetails();
    sfViewerDetails(std::vector<std::vector<float>>);
    void update(Racer &racer);
    void display(sf::RenderWindow &window, int stage);

private:
    sf::Texture bgImage;
    sf::RectangleShape bg;
    sf::View view;
    sfColor colors;
    float viewHeight = 0;
    float viewWidth = 0;
    sf::Vector2f prevPos;

    //std::vector<DrawableRacer> drawableEnemies;
};