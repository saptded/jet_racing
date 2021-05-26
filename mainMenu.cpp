#include "menu.hpp"
#include "presenter.hpp"

int main(){

    std::shared_ptr<MenuInfo> info = nullptr;
    while(true){
        Menu menu(info);
        info = menu.run();
        if(info){
            Presenter *presenter = Presenter::create(info);
            info = presenter->run();
            delete presenter;
        } else {
            return 0;
        }
        if(!info){
            return 0;
        }
    }
}

