//
// Created by Kseny
//

#pragma once

#include <iostream>
#include "utils.hpp"
#include "racer.hpp"

class sfViewerDetails{
public:
    void init(Racer& racer, sf::RenderWindow& window);
    void update(Racer& racer);
    void display(sf::RenderWindow& window, int stage);
private:
    sf::View view;
};