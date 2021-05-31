#include "menu.hpp"
#include "presenter.hpp"

int main(){

    servs servers = std::make_pair(nullptr, nullptr);
    std::shared_ptr<MenuInfo> info = nullptr;
    while(true){
        Menu menu(info, servers);
        info = menu.run();
        if(info){
            auto presenter = Presenter::create(info);
            info = presenter->run();
            servers = std::move(menu.getServer());
        } else {
            return 0;
        }
        if(!info){
            return 0;
        }
    }
}
