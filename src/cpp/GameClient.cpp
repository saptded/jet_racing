//
// Created by dark0ghost on 15.04.2021.
//



export module client;
#include "../hpp/AbstractClient.hpp"
#include <string>

export class GameClient: public AbstractClient{

public:
   void close() override{

   }
   void send_data(DataGame data) override{

   }
   std::string get_data() override{

       return std::string();
   }


};
