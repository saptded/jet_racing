//
// Created by dark0ghost on 14.04.2021.
//
module;
export module game_server;

/**
 * require c++20
 */
const struct timespec *__restrict __abstime;
struct sigevent;
const struct itimerspec *__utmr;
/**
 *
 */
#include "../hpp/AbstractServer.hpp"

export class GameServer: public AbstractServer{

    size_t port = 40432;
    boost::asio::io_service io_service{};


public:

    explicit GameServer(size_t port){
        this->port = port;
    }


    void start_server()  override{

    }
    void close()  override{

    }
    void update_data_from_user() override {

    }


};
