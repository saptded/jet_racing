#include <complex>

#include "presenter.hpp"
#include "model.hpp"
#include "gameTimer.hpp"
#include "sfGameViewer.hpp"

Presenter::Presenter(int id)
    : _finishGame(false)
    , _model(new Model(id)) {}

std::shared_ptr<MenuInfo> Presenter::run() {
    std::shared_ptr<MenuInfo> results;
    GameTimer gameTimer;

    while (!_finishGame) {
        Command command = viewer->handleButtonEvent();
        if (command == Command::finish) {
            _finishGame = true;
        }
        results = _model->updateModel(command);
        if (results != nullptr) {
            _finishGame = true;
        }
        gameTimer.timer();
    }

    viewer->close();
    return results;
}

void Presenter::handleEvent(std::shared_ptr<Response> response) { viewer->render(response); }

Presenter::~Presenter() { _model->removeObserver(this); }

std::shared_ptr<Presenter> Presenter::create(int id) {
    static auto presenter = std::shared_ptr<Presenter>(new Presenter(id));
    presenter->_model->addObserver(presenter.get());
    presenter->viewer = std::make_unique<sfGameViewer>();
    return presenter;
}

std::shared_ptr<Presenter> Presenter::create(std::shared_ptr<MenuInfo> info) {
    static auto presenter = std::make_shared<Presenter>(info);
    presenter->_model->addObserver(presenter.get());
    presenter->viewer = std::make_unique<sfGameViewer>();
    return presenter;
}

Presenter::Presenter(std::shared_ptr<MenuInfo> info)
        : _finishGame(false)
        , _model(std::make_unique<Model>(info))
        {};

