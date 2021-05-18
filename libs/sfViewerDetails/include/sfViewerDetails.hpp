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
    explicit sfViewerDetails(sf::RenderWindow &window);
    sfViewerDetails()
        : viewWidth(float(1920)  *1.5)
        , viewHeight(float(1080) *1.5){};
    void update(Racer &racer);
    void display(sf::RenderWindow &window, int stage);

private:
    sf::View view;
    sfColor colors;
    float viewHeight = 0;
    float viewWidth = 0;
};