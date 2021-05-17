#pragma once

#include "viewer.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <abstractModel.hpp>
#include "SFMLGameWindow.hpp"
#include <memory>
#include <observer.hpp>

class Presenter : public Observer {
public:
    static Presenter *create();

    ~Presenter();



    Presenter(const Presenter &) = delete;
    Presenter &operator=(const Presenter &) = delete;

    void run();
    void handleEvent(Response &response) override;

private:
    Presenter();

    std::unique_ptr<Viewer> viewer;

    bool _finishGame;
    std::unique_ptr<AbstractModel> _model;
    std::unique_ptr<SFMLGameWindow> _window;

//    sf::RenderWindow _window;

    void handleButtonEvent();
};
