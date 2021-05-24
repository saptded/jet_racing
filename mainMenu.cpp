#include "menu.hpp"
#include "presenter.hpp"
int main() {
    std::shared_ptr<MenuInfo> info = nullptr;
    while(true){
        Menu menu(info); // оценила то что можно вызвать delete если указатель (как у Леши), потом мб переделаю так же
        // записываем в инфо что-то об игроках
        info = menu.run();
        if(info){ // запускаем игру с входными параметрами
            //    Presenter *presenter = Presenter::create(info);
            //    записываем в инфо результаты игры
            //    info = presenter->run();
            //    delete presenter;
            if(!info) return 0; // типа окно игры закрыли (?)
        } else {
            return 0;
        }
    }
}