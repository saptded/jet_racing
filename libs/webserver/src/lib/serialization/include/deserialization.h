//
// Created by dark0ghost on 12.05.2021.
//
#pragma once
#ifndef LIBSERVER_DESERIALIZATION_H
#define LIBSERVER_DESERIALIZATION_H
#include <Position.hpp>
#include <string>


template<typename T>
class DeserializationObject{

    T jsonTransformer = T();

public:
    std::vector<Position> getPositionFromJson(std::string& json){
        return jsonTransformer.jsonToPosition(json);
    }

    std::string getIdFromJson(std::string& json){
        std::cout << json;
        return jsonTransformer.jsonToId(json.c_str());
    }
};


template<typename Point>
inline Position twoDPointWithNameConvertToPosition(const Point& twoDPoint, const std::string& name){
    std::string xPos = std::to_string(twoDPoint.x);
    std::string yPos = std::to_string(twoDPoint.y);
    Position pos = Position{name,xPos ,yPos, ""};
    return pos;
}

template<typename Racer, typename Point> [[maybe_unused]] Position convertRacerToPosition(Racer& racer){
    const std::string name = std::to_string(racer._id);
    Point& point = racer.point;
    return twoDPointWithNameConvertToPosition(point, name);
}

#endif //LIBSERVER_DESERIALIZATION_H
