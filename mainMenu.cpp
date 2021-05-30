//#include <customDeserialization.h>
//#include <GameServer.hpp>
//#include <customRequest.h>
//#include <GameClient.hpp>
//#include <startServer.h>
#include <customDeserialization.h>
#include "menu.hpp"
#include "presenter.hpp"


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
//    std::cout << res << " res" << std::endl;
//    std::string test2 = "test";
//    auto res2 = gameClient.join<CustomDeserialization>(test2);
//
//    std::cout << gameClient.getFlag<CustomDeserialization>() << " res1" << std::endl;
//    gameClient.sendFlag(true);
//    std::cout << gameClient.getFlag<CustomDeserialization>() << " res2" << std::endl;
//    Position pos = {"test", std::to_string(42), std::to_string(42)
//            , std::to_string(42)
//            , 42
//            , 42};
//    std::cout << pos.stage<< std::endl;
//    gameClient.sendData(pos);
//    std::vector<Position> names = gameClient.getUpdates<CustomDeserialization>();
//    for(auto& i: names){
//        std::cout << (R"(Position{"username":")" + i.username + R"(","x":")" + i.x + R"(","y":")" + i.y + R"(","rotation":")" + i.rotation + R"(","speed":)" + std::to_string(i.speed) + R"(,"stage":)" + std::to_string(i.stage) +  R"(,"isFinished":)" + std::to_string(i.isFinished) + "},") << std::endl;
//    }
//    std::cout << names.size() << std::endl;
//    server->wait();
    std::shared_ptr<running_server_instance_t<http_server_t<ServerTraits>>> server= nullptr;
    std::shared_ptr<MenuInfo> info = nullptr;
    while(true){
        Menu menu(info, server);
        info = menu.run();

        Presenter *presenter = Presenter::create(info);
        info = presenter->run();
        delete presenter;

        server = std::move(menu.getServer());
        if(!info){
            break;
        }
    }
}