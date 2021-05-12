//
// Created by Kseny
//

#pragma once

#include <SFML/Graphics/Color.hpp>
#include <vector>

class sfColor{
public:
    sf::Color door = {42, 44, 90};
    sf::Color accelerator = {63,175,70,155};
    sf::Color delayer = {214,46,78,155};
    sf::Color getWall(int stage);
    sf::Color getBg(int stage);
    sf::Color getCar(int id);
private:
    std::vector<sf::Color> walls = {
        sf::Color(80,101,50),
        sf::Color(253,224,107),
        sf::Color(100,93,80),
    };
    std::vector<sf::Color> bg = {
        sf::Color(195,203,145),
        sf::Color(151,144,129),
        sf::Color(242,222,213),
    };
    std::vector<sf::Color> cars = {
        sf::Color(255,56,56), //красный
        sf::Color(52,212,250), //голубой
        sf::Color(122,192,63), //зеленый
        sf::Color(238,148,47), //рыжий
    };
};