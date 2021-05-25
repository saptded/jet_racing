#include <customDeserialization.h>
#include "menu.hpp"
#include "presenter.hpp"
int main() {

    bool isServer = true;
    GameServer gameServer = GameServer();
    ConnectionData connectionData = {2020, "localhost"}; // сетевые данные на которых запуститься сервер
    std::cout << 2;
    //auto server = startServer(gameServer, connectionData);
    std::cout << 1;

    ConnectionData data = ConnectionData{2020, "localhost"};
    auto gameClient = GameClient<CustomRequest>(data);
    std::string name = "isServer_" + std::to_string(isServer);
    auto res = gameClient.join<CustomDeserialization>(name);
    std::cout << res;
    rapidjson::Document genericDocument;
    genericDocument.Parse(R"({"id": 2})");
    std::cout << genericDocument["id"].GetInt();

    // ждем
    //server->stop();


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