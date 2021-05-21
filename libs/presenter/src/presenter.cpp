#include "presenter.hpp"
#include "model.hpp"
#include <complex>

Presenter::Presenter(int id)
    : _finishGame(false)
    , _model(new Model(id))
    , _window(new SFMLGameWindow) {

}

void Presenter::run() {

    while (!_finishGame) {
        Rotation command = _window->handleButtonEvent();
        if (command == Rotation::finish) {
            _finishGame = true;
        }
        _model->updateModel(command);
        _window->timer();
    }

    _window->getWindow().clear();
    _window->getWindow().close();
}

void Presenter::handleEvent(Response &response) { viewer->render(response, _window->getWindow()); }

Presenter *Presenter::create(int id) {
    static auto presenter = new Presenter(id);
    presenter->_model->addObserver(presenter);
    presenter->viewer = std::make_unique<Viewer>();
    return presenter;
}
Presenter::~Presenter() { _model->removeObserver(this); }

// auto height = static_cast<float>(response._racer.value()->_height);
// auto width = static_cast<float>(response._racer.value()->_width);
//
// sf::CircleShape point1(4);
// point1.setOrigin(4, 4);
// point1.setPosition(response._racer.value()->_position.first.x, response._racer.value()->_position.first.y);
// point1.setFillColor(sf::Color::Magenta);
//
// sf::CircleShape point2(4);
// point2.setOrigin(4, 4);
// point2.setPosition(response._racer.value()->_position.second.x, response._racer.value()->_position.second.y);
// point2.setFillColor(sf::Color::Red);
//
// sf::CircleShape center(4);
// center.setOrigin(4, 4);
// center.setPosition(response._racer.value()->_center.x, response._racer.value()->_center.y);
// center.setFillColor(sf::Color::Black);
//
// sf::RectangleShape racer(sf::Vector2f(width, height));
// racer.setOrigin(response._racer.value()->_origin.x, response._racer.value()->_origin.y);
// racer.move(static_cast<float>(response._racer.value()->_center.x), static_cast<float>(response._racer.value()->_center.y));
// racer.rotate(-static_cast<float>(response._racer.value()->_rotation));
// racer.setFillColor(sf::Color::Cyan);
//
////
////    sf::RectangleShape lin(sf::Vector2f(1280, 1));
////    lin.setPosition(obj1.start.x, obj1.start.y);
////    double a = std::atan((obj1.end.y - obj1.start.y) / (obj1.end.x - obj1.start.x));
////    lin.rotate(a * 180 / M_PI);
////    lin.setFillColor(sf::Color::Red);
//
//_window.clear();
//_window.draw(racer);
//_window.draw(lin);
//_window.draw(point1);
//_window.draw(point2);
//_window.draw(center);
//_window.display();

// auto height = static_cast<float>(response._racer.value()->_height);
// auto width = static_cast<float>(response._racer.value()->_width);
//
// sf::CircleShape point1(4);
// point1.setOrigin(4, 4);
// point1.setPosition(response._racer.value()->_position.first.x, response._racer.value()->_position.first.y);
// point1.setFillColor(sf::Color::Magenta);
//
// sf::CircleShape point2(4);
// point2.setOrigin(4, 4);
// point2.setPosition(response._racer.value()->_position.second.x, response._racer.value()->_position.second.y);
// point2.setFillColor(sf::Color::Red);
//
// sf::CircleShape center(4);
// center.setOrigin(4, 4);
// center.setPosition(response._racer.value()->_center.x, response._racer.value()->_center.y);
// center.setFillColor(sf::Color::Black);
//
// sf::RectangleShape racer(sf::Vector2f(width, height));
// racer.setOrigin(response._racer.value()->_origin.x, response._racer.value()->_origin.y);
// racer.move(static_cast<float>(response._racer.value()->_center.x), static_cast<float>(response._racer.value()->_center.y));
// racer.rotate(-static_cast<float>(response._racer.value()->_rotation));
// racer.setFillColor(sf::Color::Cyan);
//
////
////    sf::RectangleShape lin(sf::Vector2f(1280, 1));
////    lin.setPosition(obj1.start.x, obj1.start.y);
////    double a = std::atan((obj1.end.y - obj1.start.y) / (obj1.end.x - obj1.start.x));
////    lin.rotate(a * 180 / M_PI);
////    lin.setFillColor(sf::Color::Red);
//
//_window.clear();
//_window.draw(racer);
//_window.draw(lin);
//_window.draw(point1);
//_window.draw(point2);
//_window.draw(center);
//_window.display();
