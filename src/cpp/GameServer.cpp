//
// Created by dark0ghost on 14.04.2021.
//
export module game_server;


#include "boost/asio.hpp"
#include "../hpp/AbstractServer.hpp"

export class GameServer: public AbstractServer{

    size_t port = 40432;
    boost::asio::io_service io_service{};


public:

    explicit GameServer(size_t port){
        this->port = port;
    }

    GameServer() = default;


    void start_server()  override{

    }
    void close()  override{

    }
     void update_data_from_user() override {

    }


};
