#pragma once

#include <SFML/Graphics.hpp>

class GameTimer {
public:
    GameTimer() = default;

    void timer(float want_fps = 60);

public:
    sf::Clock looper;
};
