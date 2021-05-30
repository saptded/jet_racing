#include <complex>

#include "gameTimer.hpp"
#include "model.hpp"
#include "presenter.hpp"

Presenter::Presenter(int id)
    : _finishGame(false)
    , _model(new Model(id)) {}

std::shared_ptr<MenuInfo> Presenter::run() {
    std::shared_ptr<MenuInfo> results;
    GameTimer gameTimer;

    while (!_finishGame) {
        Command command = /*viewer->handleButtonEvent()*/ Command::none;
        if (command == Command::finish) {
            _finishGame = true;
        }
        results = _model->updateModel(command);
        if (results != nullptr) {
            _finishGame = true;
        }
        gameTimer.timer();
    }

    /*
        viewer->close();
    */
    return results;
}

void Presenter::handleEvent(Response &response) { /*viewer->render(response);*/
}

std::shared_ptr<Presenter> Presenter::create(int id) {
    static auto presenter = std::shared_ptr<Presenter>(new Presenter(id));
    presenter->_model->addObserver(presenter.get());
    /*
        presenter->viewer = std::make_unique<Viewer>();
    */
    return presenter;
}
Presenter::~Presenter() { _model->removeObserver(this); }
