#include "presenter.hpp"

int main() {
    std::shared_ptr<Presenter> presenter = std::shared_ptr<Presenter>(Presenter::create());

    presenter->run();
}