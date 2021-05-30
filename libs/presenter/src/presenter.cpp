#include "presenter.hpp"
#include "model.hpp"
#include <complex>

Presenter::Presenter(int id)
    : _finishGame(false)
    //, _model(new Model(id))
    , _model(nullptr)
    , _window(new SFMLGameWindow("no")) {}

std::shared_ptr<MenuInfo> Presenter::run() {
    std::shared_ptr<MenuInfo> results;

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

//Presenter *Presenter::create(int id) {
//    static auto presenter = new Presenter(id);
//    presenter->_model->addObserver(presenter);
//    presenter->viewer = std::make_unique<Viewer>();
//    return presenter;
//}
Presenter::~Presenter() { _model->removeObserver(this); }

Presenter *Presenter::create(std::shared_ptr<MenuInfo> menuInfo){
    static auto presenter = new Presenter(
            std::move(menuInfo));
    presenter->_model->addObserver(presenter);
    presenter->viewer = std::make_unique<Viewer>();
    return presenter;
}

Presenter::Presenter(std::shared_ptr<MenuInfo> info)
        : _finishGame(false)
        , _model(std::make_unique<Model>(info))
        , _window(new SFMLGameWindow("JetRacing: " + info->myName)){};

