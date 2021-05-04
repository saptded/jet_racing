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
     std::string get_request();
     std::string get_data();
public:
    DataGame get_updates();
    void close();
    void send_data(DataGame& data);

};
#endif //LIBSERVER_ABSTRACTCLIENT_H
