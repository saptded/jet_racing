//
// Created by dark0ghost on 05.04.2021.
//

#ifndef LIBSERVER_ABSTRACTCLIENT_H
#define LIBSERVER_ABSTRACTCLIENT_H
#include "DataGame.hpp"
#include <cstring>
#include <string>

class GameClient{
protected:
     std::string getRequest();
     std::string getData();
public:
    DataGame getUpdates();
    void close();
    void sendData(DataGame& data);

};
#endif //LIBSERVER_ABSTRACTCLIENT_H
