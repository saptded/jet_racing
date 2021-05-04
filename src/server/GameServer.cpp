//
// Created by dark0ghost on 14.04.2021.
//


#include <restinio/all.hpp>
#include <utility>
#include <Connection.hpp>



class GameServer{

    using router_t = restinio::router::express_router_t<>;

    Connection connection;
    std::unique_ptr<router_t> router =  std::make_unique<router_t>();

    void route(){

    }



public:

    explicit GameServer(Connection connection1) : connection(std::move(connection1)) {
        route();
    }


    void start() {
       /* restinio::run(
                restinio::on_this_thread()
                        .address(connection.host)
                        .port(connection.port)
                        //.request_handler(router)
                        );*/

    }
    void close() {

    }

};

