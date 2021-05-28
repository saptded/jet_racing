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
        return jsonTransformer.jsonToPosition(json.c_str());
    }

    size_t getIdFromJson(std::string& json){
        return jsonTransformer.jsonToId(json.c_str());
    }

    bool getFlagFromJson(std::string& json){
        return jsonTransformer.jsonToFlag(json.c_str());
    }
};
#endif //LIBSERVER_DESERIALIZATION_H
