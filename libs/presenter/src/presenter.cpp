#include "presenter.hpp"
#include "model.hpp"
#include <complex>

Presenter::Presenter(int id)
    : _finishGame(false)
    , _model(new Model(id))
    , _window(new SFMLGameWindow) {}

void Presenter::run() {

    while (!_finishGame) {
        Command command = _window->handleButtonEvent();
        if (command == Command::finish) {
            _finishGame = true;
        }
        _model->updateModel(command);
        _window->timer();
    }

    _window->getWindow().clear();
    _window->getWindow().close();
}

void Presenter::handleEvent(Response &response) { viewer->render(response, _window->getWindow()); }

Presenter *Presenter::create(int id) {
    static auto presenter = new Presenter(id);
    presenter->_model->addObserver(presenter);
    presenter->viewer = std::make_unique<Viewer>();
    return presenter;
}
Presenter::~Presenter() { _model->removeObserver(this); }
