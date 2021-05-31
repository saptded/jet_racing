//
// Created by Kseny
//

#pragma once

#include <SFML/Graphics/Color.hpp>
#include <vector>

class sfColor {
public:
    sf::Color accelerator = {145, 236, 141, 55};
    sf::Color delayer = {255, 0, 0, 55};
    sf::Color getWall(int stage);
    sf::Color getCar(int id);

    sf::Color menuDark = {200, 200, 200, 180};
    sf::Color menuBright = sf::Color::White;

    sf::Color fire = {185, 247, 255, };
    sf::Color white = sf::Color::White;
    sf::Color black = sf::Color::Black;
private:
    std::vector<sf::Color> walls = {
        sf::Color(108,93,228), // фиолетовые
        sf::Color(223, 94, 228), // розовые
        sf::Color(184, 208, 210), //белые
        sf::Color(100, 93, 80),
        sf::Color(106, 234, 90), // цвет финиша - зеленоватый
        sf::Color(255, 255, 109),// цвет портала - желтый

    };
    std::vector<sf::Color> bg = {
        sf::Color(195, 203, 145),
        sf::Color(151, 144, 129),
        sf::Color(242, 222, 213),
    };
    std::vector<sf::Color> cars = {
        sf::Color::White,
        sf::Color(255, 56, 56),   //красный
        sf::Color(52, 212, 250),  //голубой
        sf::Color(122, 192, 63),  //зеленый
        sf::Color(238, 148, 47),  //рыжий
    };
};