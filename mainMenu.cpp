#include "menu.hpp"
#include "presenter.hpp"
int main() {
    std::shared_ptr<RacerInfo> info = nullptr;
    while(true){
        Menu menu(info);
        menu.run();

        auto presenter = Presenter::create(0);
        info = presenter->run();

        menu.stopServer();
        if(!info){
            break;
        }
    }
}