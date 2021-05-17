#pragma once

#include <SFML/Graphics.hpp>

class SFMLGameWindow{
public:
    SFMLGameWindow();

    sf::RenderWindow &getWindow();
    Rotation handleButtonEvent();
    void timer(float want_fps = 60);
    void close();

public:
    sf::RenderWindow _window;
    sf::Clock looper;
};
