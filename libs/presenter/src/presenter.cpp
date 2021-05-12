#include "presenter.hpp"
#include "model.hpp"
#include <SFML/Graphics.hpp>
#include <complex>

//enum Type {
//    line,
//};

//typedef struct AbstractElement {
//    AbstractElement(Type type, Point start, Point end, Point center, bool isDynamic)
//        : type(type)
//        , start(start)
//        , end(end)
//        , center(center)
//        , isDynamic(isDynamic) {}
//
//    Type type;
//    Point start;
//    Point end;
//    Point center;
//    bool isDynamic;
//
//    virtual void updateElement() {};
//} AbstractElement;
//
//typedef struct Line : public AbstractElement {
//    Line(Type type, Point start, Point end, Point center, bool isDynamic)
//        : AbstractElement(type, start, end, center, isDynamic) {}
//    void updateElement() override{};
//} Line;
//
//[[maybe_unused]] Line obj1(Type::line, {400, 400}, {400, 0}, {640, 50}, false);

Presenter::Presenter()
    : _finishGame(false)
    , _model(new Model())
    , _window(sf::RenderWindow(sf::VideoMode(1920, 1080), "buttonEvents")) {

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
    viewer->render(response, _window);
}

void Presenter::handleButtonEvent() { // TODO сделай из этого интерфейс в который передашь функтор-реакцию (updateModel)
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


//auto height = static_cast<float>(response._racer.value()->_height);
//auto width = static_cast<float>(response._racer.value()->_width);
//
//sf::CircleShape point1(4);
//point1.setOrigin(4, 4);
//point1.setPosition(response._racer.value()->_position.first.x, response._racer.value()->_position.first.y);
//point1.setFillColor(sf::Color::Magenta);
//
//sf::CircleShape point2(4);
//point2.setOrigin(4, 4);
//point2.setPosition(response._racer.value()->_position.second.x, response._racer.value()->_position.second.y);
//point2.setFillColor(sf::Color::Red);
//
//sf::CircleShape center(4);
//center.setOrigin(4, 4);
//center.setPosition(response._racer.value()->_center.x, response._racer.value()->_center.y);
//center.setFillColor(sf::Color::Black);
//
//sf::RectangleShape racer(sf::Vector2f(width, height));
//racer.setOrigin(response._racer.value()->_origin.x, response._racer.value()->_origin.y);
//racer.move(static_cast<float>(response._racer.value()->_center.x), static_cast<float>(response._racer.value()->_center.y));
//racer.rotate(-static_cast<float>(response._racer.value()->_rotation));
//racer.setFillColor(sf::Color::Cyan);
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
