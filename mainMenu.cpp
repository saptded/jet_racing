#include "menu.hpp"
#include "presenter.hpp"
int main() {
    std::shared_ptr<RacerInfo> info = nullptr;
    while(true){
        Menu menu(info);
        menu.run();

        Presenter *presenter = Presenter::create(0);
        info = presenter->run();
        delete presenter;

        menu.stopServer();
        if(!info){
            break;
        }
    }
}