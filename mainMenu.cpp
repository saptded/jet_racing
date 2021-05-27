//#include <customDeserialization.h>
//#include <GameServer.hpp>
//#include <customRequest.h>
//#include <GameClient.hpp>
//#include <startServer.h>
#include "menu.hpp"
#include "presenter.hpp"


//#define endl "\n"
int main() {




//    bool isServer = true;
//    GameServer gameServer = GameServer();
//    ConnectionData connectionData = {2020, "localhost"}; // сетевые данные на которых запуститься сервер
//    auto server = startServer(gameServer, connectionData);
//
//    ConnectionData data = ConnectionData{2020, "localhost"};
//    auto gameClient = GameClient<CustomRequest>(data);
//    std::string name = "isServer_" + std::to_string(isServer);
//    auto res = gameClient.join<CustomDeserialization>(name);
//    std::cout << res << " res" << endl;
//
//    std::cout << gameClient.getFlag<CustomDeserialization>() << " res1" << endl;
//    gameClient.sendFlag(true);
//    std::cout << gameClient.getFlag<CustomDeserialization>() << " res2" << endl;
//    std::vector<Position> names = gameClient.getUpdates<CustomDeserialization>();
//    std::cout << names[0].username << endl;
//    server->wait();
    //rapidjson::Document genericDocument;
    // genericDocument.Parse(R"({"id": 2})");
    //std::cout << genericDocument["id"].GetInt();

    // ждем
    //server->stop();


    //gameClient.getUpdates<CustomDeserialization>();

    std::shared_ptr<MenuInfo> info = nullptr;
    while(true){
        Menu menu(info);
        info = menu.run();

        Presenter *presenter = Presenter::create(info);
        info = presenter->run();
        delete presenter;

        menu.stopServer();
        if(!info){
            break;
        }
    }
}