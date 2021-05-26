//
// Created by dark0ghost on 25.05.2021.
//

#ifndef JET_RACING_CUSTOMDESERIALIZATION_H
#define JET_RACING_CUSTOMDESERIALIZATION_H
#include <Position.hpp>
#include <rapidjson/document.h>
#include <string>
#include <vector>
#include <iostream>

class [[maybe_unused]] CustomDeserialization{

public:
   std::vector<Position> jsonToPosition(const char *json){
       std::vector<Position> response;
       rapidjson::Document genericDocument;
       genericDocument.Parse(json);
       if(genericDocument.IsArray()) {
           for (const auto &itr2 : genericDocument.GetArray()) {
               Position pos = Position{itr2["username"].GetString(), itr2["x"].GetString(), itr2["y"].GetString(),
                                       itr2["z"].GetString()};
               response.push_back(pos);
           }
       }
       return response;
   }

    size_t  jsonToId(const char *id) {
        rapidjson::Document genericDocument;
        genericDocument.Parse(id);
        if(genericDocument.IsObject()) {
            rapidjson::Value &idFromJson = genericDocument["id"];
            return idFromJson.GetInt();
        }
        return 0;
    }


    bool jsonToFlag(const char *id){
        rapidjson::Document genericDocument;
        genericDocument.Parse(id);
        if(genericDocument.IsObject()) {
            rapidjson::Value &idFromJson = genericDocument["flag"];
            return bool(idFromJson.GetInt());
        }
        return false;
    }

};
#endif  // JET_RACING_CUSTOMDESERIALIZATION_H
