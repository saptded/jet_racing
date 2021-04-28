//
// Created by dark0ghost on 14.04.2021.
//

#include "../hpp/AbstractServer.hpp"

class GameServer: public AbstractServer{

    size_t port = 40432;
    boost::asio::io_service io_service{};

    std::string get_request(){

    }


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
