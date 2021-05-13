#include <SFML/Graphics.hpp>
#include <complex>

#include "presenter.hpp"
#include "model.hpp"

Presenter::Presenter()
    : _finishGame(false)
    , _model(new Model())
    , _window(new SFMLGameWindow()) {

    _model->addObserver(this);
}

void Presenter::run() {
    float want_fps = 60;
    sf::Clock loopTimer;

    while (!_finishGame) {
        Rotation command = _window->handleButtonEvent();
        _model->updateModel(command);
        sf::Int32 frameDuration = loopTimer.getElapsedTime().asMilliseconds();
        sf::Int32 timeToSleep = int(1000.f / want_fps) - frameDuration;
        if (timeToSleep > 0) {
            sf::sleep(sf::milliseconds(timeToSleep));
        }
        loopTimer.restart();
    }

    _window->close();
}

void Presenter::handleEvent(Response &response) {
    auto height = static_cast<float>(response.racer.value()->_height);
    auto width = static_cast<float>(response.racer.value()->_width);

    sf::CircleShape point1(4);
    point1.setOrigin(4, 4);
    point1.setPosition(response.racer.value()->_position.first.x, response.racer.value()->_position.first.y);
    point1.setFillColor(sf::Color::Magenta);

    sf::CircleShape point2(4);
    point2.setOrigin(4, 4);
    point2.setPosition(response.racer.value()->_position.second.x, response.racer.value()->_position.second.y);
    point2.setFillColor(sf::Color::Red);

    sf::CircleShape center(4);
    center.setOrigin(4, 4);
    center.setPosition(response.racer.value()->_center.x, response.racer.value()->_center.y);
    center.setFillColor(sf::Color::Black);

    sf::RectangleShape racer(sf::Vector2f(width, height));
    racer.setOrigin(response.racer.value()->_origin.x, response.racer.value()->_origin.y);
    racer.move(static_cast<float>(response.racer.value()->_center.x), static_cast<float>(response.racer.value()->_center.y));
    racer.rotate(-static_cast<float>(response.racer.value()->_rotation));
    racer.setFillColor(sf::Color::Cyan);
    ///////////////////////////////////////////
    enum Type {
        line,
    };

    typedef struct AbstractElement {
        AbstractElement(Type type, Point start, Point end, Point center, bool isDynamic)
            : type(type)
            , start(start)
            , end(end)
            , center(end)
            , isDynamic(isDynamic) {}

        Type type;
        Point start;
        Point end;
        Point center;
        bool isDynamic;

        virtual void updateElement(){};
    } AbstractElement;

    typedef struct Line : public AbstractElement {
        Line(Type type, Point start, Point end, Point center, bool isDynamic)
            : AbstractElement(type, start, end, center, isDynamic) {}
        void updateElement() override{};
    } Line;
    Line obj1(Type::line, {400, 1100}, {400, 0}, {640, 50}, false);
    /////////////////////////////////////////////
    sf::RectangleShape lin(sf::Vector2f(1920, 1));
    lin.setPosition(obj1.start.x, obj1.start.y);
    double a = std::atan((obj1.end.y - obj1.start.y) / (obj1.end.x - obj1.start.x));
    lin.rotate(a * 180 / M_PI);
    lin.setFillColor(sf::Color::Red);

    _window->getWindow().clear();
    _window->getWindow().draw(racer);
    _window->getWindow().draw(lin);
    _window->getWindow().draw(point1);
    _window->getWindow().draw(point2);
    _window->getWindow().draw(center);
    _window->getWindow().display();
}

Presenter *Presenter::create() {
    static auto presenter = new Presenter;
    return presenter;
}
