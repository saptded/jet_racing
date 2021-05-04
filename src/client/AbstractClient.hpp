//
// Created by dark0ghost on 05.04.2021.
//

#ifndef LIBSERVER_ABSTRACTCLIENT_H
#define LIBSERVER_ABSTRACTCLIENT_H
#include "../data_structs/DataGame.hpp"
#include <cstring>

class AbstractClient{
protected:
    virtual std::string get_request() = 0;
public:
    virtual DataGame get_updates() = 0;
    virtual void close() = 0;
    virtual void send_data(DataGame data) = 0;
    virtual std::string get_data() = 0;

};
#endif //LIBSERVER_ABSTRACTCLIENT_H
