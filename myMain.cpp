#include "presenter.hpp"

int main() {
    Presenter *presenter = Presenter::create();
    presenter->run();

    delete presenter;
}