#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <abstractModel.hpp>
#include <memory>
#include <observer.hpp>

class Presenter : public Observer {
public:
    static Presenter *create();

    Presenter(const Presenter &) = delete;
    Presenter &operator=(const Presenter &) = delete;

    void run();
    void handleEvent(Response &response) override;

private:
    Presenter();

    bool _finishGame;
    std::shared_ptr<AbstractModel> _model;

    sf::RenderWindow _window;

    void handleButtonEvent();
};
