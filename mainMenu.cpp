#include "menu.hpp"
#include "presenter.hpp"

int main(){

    std::shared_ptr<MenuInfo> info = nullptr;
    while(true){
        Menu menu(info);
        info = menu.run();
        if(info){
            auto presenter = Presenter::create(0);
            info = presenter->run();
        } else {
            return 0;
        }
        if(!info){
            return 0;
        }
    }
}

