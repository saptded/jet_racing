//
// Created by dark0ghost on 14.04.2021.
//

#pragma once
#include <restinio/all.hpp>
#include <utility>
#include "../hpp/AbstractServer.hpp"


class GameServer: public AbstractServer{

    using router_t = restinio::router::express_router_t<>;

    Connection connection;
 //   std::unique_ptr<router_t> router =  std::make_unique<router_t>();



public:

    explicit GameServer(Connection connection1) : connection(std::move(connection1)) {
        route();
    }

    void route(){


    }


    void start_server()  override{
       /* restinio::run(
                restinio::on_this_thread()
                        .address(connection.host)
                        .port(connection.port)
                        //.request_handler(router)
                        );*/

    }
    void close()  override{

    }
    void update_data_from_user() override {

    }


};

