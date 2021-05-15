#include "mechanicalValues.hpp"
#include <SFMLGameWindow.hpp>

Rotation SFMLGameWindow::handleButtonEvent() {
    sf::Event buttonEvent{};

    while (_window.pollEvent(buttonEvent)) {
        if (buttonEvent.type == sf::Event::Closed) {
            return Rotation::finish;
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        return Rotation::left;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        return Rotation::right;
    }

    return Rotation::none;
}

SFMLGameWindow::SFMLGameWindow()
    : _window(sf::RenderWindow(sf::VideoMode(1920, 1080), "game")) {}

sf::RenderWindow &SFMLGameWindow::getWindow() { return _window; }
void SFMLGameWindow::close() { _window.close(); }
