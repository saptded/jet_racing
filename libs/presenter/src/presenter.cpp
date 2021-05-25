#include "presenter.hpp"
#include "model.hpp"
#include <complex>

Presenter::Presenter(int id)
    : _finishGame(false)
    , _model(new Model(id))
    , _window(new SFMLGameWindow) {}

std::shared_ptr<RacerInfo> Presenter::run() {
    std::shared_ptr<RacerInfo> results;

    while (!_finishGame) {
        Command command = _window->handleButtonEvent();
        if (command == Command::finish) {
            _finishGame = true;
        }
        results = _model->updateModel(command);
        if (results != nullptr) {
            _finishGame = true;
        }
        _window->timer();
    }

    _window->getWindow().clear();
    _window->getWindow().close();
    return results;
}

void Presenter::handleEvent(Response &response) { viewer->render(response, _window->getWindow()); }

std::shared_ptr<Presenter> Presenter::create(int id) {
    static auto presenter = std::shared_ptr<Presenter>(new Presenter(id));
    presenter->_model->addObserver(presenter.get());
    presenter->viewer = std::make_unique<Viewer>();
    return presenter;
}
Presenter::~Presenter() { _model->removeObserver(this); }
