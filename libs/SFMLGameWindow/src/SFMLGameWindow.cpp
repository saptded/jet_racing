#include "mechanicalValues.hpp"
#include <SFMLGameWindow.hpp>

Command SFMLGameWindow::handleButtonEvent() {
    sf::Event buttonEvent{};

    while (_window.pollEvent(buttonEvent)) {
        if (buttonEvent.type == sf::Event::Closed) {
            return Command::finish;
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        return Command::left;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        return Command::right;
    }

    return Command::none;
}

SFMLGameWindow::SFMLGameWindow()
    : _window(sf::RenderWindow(sf::VideoMode(1920, 1080), "game")) {}

sf::RenderWindow &SFMLGameWindow::getWindow() { return _window; }

void SFMLGameWindow::close() { _window.close(); }

void SFMLGameWindow::timer(float want_fps) {
    sf::Int32 frameDuration = looper.getElapsedTime().asMilliseconds();
    sf::Int32 timeToSleep = int(1000.f / want_fps) - frameDuration;
    if (timeToSleep > 0) {
        sf::sleep(sf::milliseconds(timeToSleep));
    }
    looper.restart();
}
