//
// Created by Kseny
//

#pragma once

#include "racer.hpp"
#include "utils.hpp"
#include <iostream>
#include <sfColor.hpp>

class sfViewerDetails{
public:
    void init(Racer& racer, sf::RenderWindow& window);
    void update(Racer& racer);
    void display(sf::RenderWindow& window, int stage);
private:
    sf::View view;
    sfColor colors = sfColor();
};