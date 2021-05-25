//
// Created by Kseny
//

#include "sfColor.hpp"

sf::Color sfColor::getWall(int stage) {
    if ((stage >= 0) && (stage <= walls.size())) {
        return walls[stage - 1];
    } else {
        return sf::Color::White;
    }
};
//sf::Color sfColor::getBg(int stage) {
//    if ((stage >= 0) && (stage <= bg.size())) {
//        return bg[stage - 1];
//    } else {
//        return sf::Color::White;
//    }
//};
sf::Color sfColor::getCar(int id) {
    if ((id >= 0) && (id <= cars.size())) {
        return cars[id];
    } else {
        return sf::Color::Cyan;
    }
};
