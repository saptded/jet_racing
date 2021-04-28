//
// Created by dark0ghost on 15.04.2021.
//
#include "../hpp/AbstractClient.hpp"
#include "../hpp/ServerDataConnection.h"
#include <boost/asio.hpp>

class GameClient: public AbstractClient{
    boost::asio::io_service service;
    boost::asio::ip::tcp::endpoint ep;

    ServerDataConnection back_up_server_data_connection;

    std::string get_request(){
        return "";
    }



public:
    explicit GameClient(ServerDataConnection server_data_connection){
        back_up_server_data_connection = server_data_connection;
        ep = boost::asio::ip::tcp::endpoint (boost::asio::ip::address::from_string( back_up_server_data_connection.ip),  back_up_server_data_connection.port);
    }

   void close() override{

   }
   void send_data(DataGame data) override{

   }
   std::string get_data() {

       return std::string();
   }

    DataGame get_updates(){

        return DataGame();
    }


};

