//
// Created by dark0ghost on 05.04.2021.
//

#ifndef LIBSERVER_ABSTRACTCLIENT_H
#define LIBSERVER_ABSTRACTCLIENT_H
#include "DataGame.hpp"
#include <cstring>
#include <string>
#include <utility>
#include <curl_intarface.h>
#include <Connection.hpp>

template<typename... Ts>
class GameClient{
     Connection connection;
     Response (*getRequest)(Ts&&... ts);

public:
    explicit GameClient(Connection connection1, Response (get)(Ts&&... ts)){
        connection = std::move(connection1);
        getRequest = &get;
    }
    explicit GameClient(Response (get)(Ts&&... ts)){
        getRequest = &get;
        connection = Connection();
    }

    std::string getUpdates();
    void sendData(UserPosition& userPosition);

    std::vector<std::string> searchOpenSession(std::vector<std::string> ipList, std::string port);
};
#endif //LIBSERVER_ABSTRACTCLIENT_H
