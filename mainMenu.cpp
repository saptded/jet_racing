#include <customDeserialization.h>
#include "menu.hpp"
#include "presenter.hpp"
int main() {

    bool isServer;
    std::cin >> isServer;
    if(isServer){
        GameServer gameServer = GameServer();
        ConnectionData connectionData = {2021, "localhost"}; // сетевые данные на которых запуститься сервер
        auto server = startServer(gameServer, connectionData);
    }

    ConnectionData data = ConnectionData{2021, "localhost"};
    auto gameClient = GameClient<CustomRequest>(data);
    std::string name = "isServer_" + std::to_string(isServer);
    gameClient.join<CustomDeserialization>(name);

    int letsgo;
    std::cin >> letsgo; // ждем

    //gameClient.getUpdates<CustomDeserialization>();

//    std::shared_ptr<RacerInfo> info = nullptr;
//    while(true){
//        Menu menu(info);
//        menu.run();
//
//        Presenter *presenter = Presenter::create(0);
//        info = presenter->run();
//        delete presenter;
//
//        menu.stopServer();
//        if(!info){
//            break;
//        }
//    }
}