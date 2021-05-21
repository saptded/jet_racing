#include "presenter.hpp"

int main() {
    int id = 0;

    Presenter *presenter = Presenter::create(id);
    presenter->run();

    delete presenter;
}