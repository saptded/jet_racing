//
// Created by dark0ghost on 14.04.2021.
//

#include "../hpp/AbstractServer.hpp"
#include <restinio/all.hpp>


class GameServer: public AbstractServer{

    struct Connection {

    };

    size_t port = 40432;





public:

    explicit GameServer(size_t port){
        this->port = port;
    }


    void start_server()  override{
        restinio::run(
                restinio::on_this_thread<my_server_traits>()
                        .address("localhost")
                        . request_handler ( std :: move (router)));

    }
    void close()  override{

    }
    void update_data_from_user() override {

    }


};

