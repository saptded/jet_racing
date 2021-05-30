//<<<<<<< HEAD
//#include <customDeserialization.h>
//#include <GameServer.hpp>
//#include <customRequest.h>
//#include <GameClient.hpp>
//#include <startServer.h>
#include <customDeserialization.h>
#include "menu.hpp"
#include "presenter.hpp"
//=======
#define DEBUG
#include <customDeserialization.h>
#include "menu.hpp"
#include "presenter.hpp"
#define endl "\n"

int main2() {

    bool isServer = true;
    GameServer gameServer = GameServer();
    ConnectionData connectionData = {2020, "localhost"}; // сетевые данные на которых запуститься сервер
    auto server = startServer(gameServer, connectionData);

    ConnectionData data = ConnectionData{2020, "localhost"};
    auto gameClient = GameClient<CustomRequest>(data);
    std::string name = "isServer_" + std::to_string(isServer);
    auto res = gameClient.join<CustomDeserialization>(name);
    std::cout << res << " res" << endl;
    std::string test2 = "test";
    auto res2 = gameClient.join<CustomDeserialization>(test2);
    //Position pos = Position{std::to_string(res), "1", "2", "3", 0.01, 1, true};
    Position pos = Position{std::to_string(res), "1", "2", "3", 0.01, 1, true};
    gameClient.sendData(pos);
    std::cout << gameClient.getFlag<CustomDeserialization>() << " res flag send" << endl;
    gameClient.sendFlag(true);
    std::cout << gameClient.getFlag<CustomDeserialization>() << " res flag get" << endl;
    std::vector<Position> names = gameClient.getUpdates<CustomDeserialization>();
    for (auto &i: names) {
        std::cout << (R"(Position{"username":")" + i.username + R"(","x":")" + i.x + R"(","y":")" + i.y +
                      R"(","rotation":")" + i.rotation + R"(","speed":)" + std::to_string(i.speed) + R"(,"stage":)" +
                      std::to_string(i.stage) + R"(,"isFinished":)" + std::to_string(i.isFinished) + "},") << endl;
    }
    server->wait();
    //rapidjson::Document genericDocument;
    // genericDocument.Parse(R"({"id": 2})");
    //std::cout << genericDocument["id"].GetInt();
//>>>>>>> connecting_modules_web
}

int main() {
    servs servers = std::make_pair(nullptr, nullptr);
    std::shared_ptr<MenuInfo> info = nullptr;
    while(true){
        Menu menu(info, servers);
        info = std::move(menu.run());

        if(!info){
            return 0;
        }

        Presenter *presenter = Presenter::create(info);
        info = presenter->run();
        delete presenter;

        servers = std::move(menu.getServer());

        if(!info){
            return 0;
        }
    }
}