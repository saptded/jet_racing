//
// Created by dark0ghost on 15.04.2021.
//



export module game_client;
#include "../hpp/AbstractClient.hpp"
#include <string>

class GameServer: public AbstractClient{

public:
   void close() override{

   }
   void send_data(int data){

   }
   std::string get_data() override{

   }


};
