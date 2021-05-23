#pragma once

#include <SFML/Graphics.hpp>
#include "mechanicalValues.hpp"

class SFMLGameWindow {
public:
    SFMLGameWindow();

    sf::RenderWindow &getWindow();
    Command handleButtonEvent();
    void timer(float want_fps = 60);
    void close();

public:
    sf::RenderWindow _window;
    sf::Clock looper;
};
