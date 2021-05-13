#pragma once

#include <SFML/Graphics.hpp>

class SFMLGameWindow{
public:
    SFMLGameWindow();

    sf::RenderWindow &getWindow();
    Rotation handleButtonEvent();
    void close();

public:
    sf::RenderWindow _window;
};
