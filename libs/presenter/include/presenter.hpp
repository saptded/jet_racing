#pragma once

#include "gameViewer.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <abstractModel.hpp>
#include <memory>
#include <observer.hpp>

class Presenter : public Observer {
public:
    static std::shared_ptr<Presenter> create(int id);
    static std::shared_ptr<Presenter> create(std::shared_ptr<MenuInfo> info);

    ~Presenter();

    Presenter(const Presenter &) = delete;
    Presenter &operator=(const Presenter &) = delete;

    std::shared_ptr<MenuInfo> run();
    void handleEvent(std::shared_ptr<Response> response) override;

    explicit Presenter(std::shared_ptr<MenuInfo> info);

private:
    explicit Presenter(int id);

    bool _finishGame = false;

    std::unique_ptr<GameViewer> viewer;
    std::unique_ptr<AbstractModel> _model;
};
