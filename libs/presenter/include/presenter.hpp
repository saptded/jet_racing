#pragma once

#include "viewer.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <abstractModel.hpp>
#include <memory>
#include <observer.hpp>

class Presenter : public Observer {
public:
    static std::shared_ptr<Presenter> create(int id);

    ~Presenter();

    Presenter(const Presenter &) = delete;
    Presenter &operator=(const Presenter &) = delete;

    std::shared_ptr<MenuInfo> run();
    void handleEvent(Response &response) override;

private:
    explicit Presenter(int id);

    bool _finishGame;

    std::unique_ptr<Viewer> viewer;
    std::unique_ptr<AbstractModel> _model;
};
