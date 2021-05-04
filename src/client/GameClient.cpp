//
// Created by dark0ghost on 15.04.2021.
//
#include "AbstractClient.hpp"
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <iostream>



class GameClient: public AbstractClient{

    std::string get_request() override{
        return "";
    }

    std::string get_data() override{

        return std::string();
    }


public:
    explicit GameClient(){
    }

   void close() override{

   }
   void send_data(DataGame data) override{

   }

    DataGame get_updates(){

        return DataGame();
    }


};

