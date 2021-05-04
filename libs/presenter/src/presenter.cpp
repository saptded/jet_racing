#include "presenter.hpp"
#include "model.hpp"
#include <SFML/Graphics.hpp>

Presenter::Presenter()
    : _finishGame(false)
    , _model(new Model())
    , _window(sf::RenderWindow(sf::VideoMode(1280, 720), "buttonEvents")) {

    _model->addObserver(this);
}

void Presenter::run() {
    float want_fps = 60;
    sf::Clock loopTimer;

    while (!_finishGame) {
        handleButtonEvent();
        sf::Int32 frameDuration = loopTimer.getElapsedTime().asMilliseconds();
        sf::Int32 timeToSleep = int(1000.f / want_fps) - frameDuration;
        if (timeToSleep > 0) {
            sf::sleep(sf::milliseconds(timeToSleep));
        }
        loopTimer.restart();
    }

    _window.close();
}

void Presenter::handleEvent(Response &response) {
    auto height = static_cast<float>(response._racer.value()->_height);
    auto width = static_cast<float>(response._racer.value()->_width);

    sf::RectangleShape racer(sf::Vector2f(width, height));
    racer.setOrigin(3 * width / 4, height / 2);
    racer.move(static_cast<float>(response._racer.value()->_center.x), static_cast<float>(response._racer.value()->_center.y));
    racer.rotate(-static_cast<float>(response._racer.value()->_rotation));
    racer.setFillColor(sf::Color::Cyan);

    _window.clear();
    _window.draw(racer);
    _window.display();
}

void Presenter::handleButtonEvent() {
    sf::Event buttonEvent{};
    Rotation currentCommand = Rotation::none;

    while (_window.pollEvent(buttonEvent)) {
        if (buttonEvent.type == sf::Event::Closed) {
            _finishGame = true;
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        currentCommand = Rotation::left;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        currentCommand = Rotation::right;
    }

    _model->updateModel(currentCommand);
}

Presenter *Presenter::create() {
    static auto presenter = new Presenter;
    return presenter;
}
