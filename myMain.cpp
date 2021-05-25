#include "presenter.hpp"
#include "MathCalculation.h"

int main() {
//    float radian = findCosine(-850, -850.007629, -9200, -9199.18262);
//
//    std::cout << radian;


    int id = 0;

    Presenter *presenter = Presenter::create(id);
    presenter->run();

    delete presenter;
}