#include <customDeserialization.h>
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
            menu.stopServer();
            return 0;
        }
        menu.stopServer();
        if(!info){
            return 0;
        }
    }
}

int main2() {
    bool isServer = true;
    std::cin >> isServer;
    if(isServer){
        GameServer gameServer = GameServer();
        ConnectionData connectionData = {2020, "localhost"}; // сетевые данные на которых запуститься сервер
        std::cout << 2 << std::endl;
        auto server = startServer(gameServer, connectionData);
        std::cout << "server runs..."<< std::endl;
        std::cout << "waiting" << std::endl;
        int no;
        std::cin >> no;
        std::cout << "resume: open client" << std::endl;

        ConnectionData data = ConnectionData{2021, "localhost"};
        auto gameClient = GameClient(data);
        std::string name = "";
        std::string res = gameClient.join<CustomDeserialization>(name);
        //std::cout << "res " << res << std::endl;

        auto got = gameClient.getUpdates();
        std::cout<<got.size();
        return 0;
    }
    std::cout << "waiting" << std::endl;
    int no;
    std::cin >> no;
    std::cout << "resume: open client" << std::endl;

    ConnectionData data = ConnectionData{2020, "localhost"};
    auto gameClient = GameClient(data);
    std::string name = "";
    std::string res = gameClient.join<CustomDeserialization>(name);
    std::cout << "connected waiting";
    int waiting;
    std::cin >> waiting;
    auto got = gameClient.getUpdates();

//    rapidjson::Document genericDocument;
//    genericDocument.Parse(R"({"id": 2})");
//    std::cout << genericDocument["id"].GetInt() << std::endl;;

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