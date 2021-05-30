#pragma once

#include "SFMLGameWindow.hpp"
#include "viewer.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <abstractModel.hpp>
#include <memory>
#include <observer.hpp>

class Presenter : public Observer {
public:
    //static Presenter *create(int id);
    static Presenter *create(std::shared_ptr<MenuInfo>);

    ~Presenter();

    Presenter(const Presenter &) = delete;
    Presenter &operator=(const Presenter &) = delete;

    std::shared_ptr<MenuInfo> run();
    void handleEvent(Response &response) override;

private:
    explicit Presenter(int id);
    explicit Presenter(std::shared_ptr<MenuInfo> info);

    bool _finishGame = false;

    std::unique_ptr<Viewer> viewer;
    std::unique_ptr<AbstractModel> _model;
    std::unique_ptr<SFMLGameWindow> _window;
};
