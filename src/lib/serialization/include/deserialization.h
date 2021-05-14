//
// Created by dark0ghost on 12.05.2021.
//

#ifndef LIBSERVER_DESERIALIZATION_H
#define LIBSERVER_DESERIALIZATION_H
#include <Position.hpp>
/*
 * T must have method jsonToVector
 * where return vector: std::string>
 * where index:
 * 0 - username
 * 1 - x
 * 2 - y
 * 3 - z
 */
template<typename T>
class DeserializationObject{

    T jsonTransformer = T();

public:
    Position getPositionFromJson(const std::string& json){
        std::vector<std::string> valueFrmJson = jsonTransformer.jsonToVector(json);
        std::string username = valueFrmJson[0];
        std::string x = valueFrmJson[1];
        std::string y = valueFrmJson[2];
        std::string z = valueFrmJson[3];
        return Position{username,x,y,z};
    }
};
#endif //LIBSERVER_DESERIALIZATION_H
