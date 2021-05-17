//
// Created by Kseny
//

#pragma once

#include "racer.hpp"
#include <iostream>
#include <sfColor.hpp>
#include <SFML/Graphics.hpp>

class sfViewerDetails{
public:
    explicit sfViewerDetails(sf::RenderWindow& window);
    sfViewerDetails(): viewWidth(float(1920)/3), viewHeight(float(1080)/3) {};
    //void init(sf::RenderWindow& window);
    void update(Racer& racer);
    void display(sf::RenderWindow& window, int stage);
private:
    sf::View view;
    sfColor colors;
    float viewHeight = 0;
    float viewWidth = 0;
};