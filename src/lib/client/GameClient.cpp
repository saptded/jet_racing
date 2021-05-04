//
// Created by dark0ghost on 15.04.2021.
//

#include <DataGame.hpp>
#include <iostream>
#include <vector>


class GameClient{

    std::string get_request() {
        return "";
    }

    std::string get_data() {

        return std::string();
    }


public:
    explicit GameClient()= default;

   void close() {

   }
   void send_data(DataGame& data) {
      for(auto i : data.position)
          std::cout<< i.x <<"\n";

      data.status = 200;

   }

    DataGame get_updates(){

        return DataGame(200,std::vector<Position<int>>());
    }


};

