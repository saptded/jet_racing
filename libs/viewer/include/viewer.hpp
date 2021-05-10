//
// Created by Kseny
//

#pragma once

#include <iostream>
#include "response.hpp"
#include "utils.hpp"

static void consoleLogFirst(std::string info){
    //std::cout << info << std::endl;
}

class Viewer {
public:
    template <typename T, typename M> void render(T& data, M& dist) {
        consoleLogFirst("Viewer render");
        render(data, typename T::Response(), dist);
    };
private:

    template <typename T, typename M> void render (T& data, ::Response<INIT>, M& dist);
    template <typename T, typename M> void render (T& data, ::Response<RACER>, M& dist);
    template <typename T, typename M> void render (T& data, ::Response<ENEMIES>, M& dist);
    template <typename T, typename M> void render (T& data, ::Response<DYNAMIC_OBJECTS>, M& dist);
    template <typename T, typename M> void render (T& data, ::Response<CHANGE_STAGE>, M& dist);
    template <typename T, typename M> void render (T& data, ::Response<RENDER>, M& dist);

    std::unique_ptr<ViewerDetails> impl;
};

template <typename T, typename M>
void Viewer::render (T& data, ::Response<INIT>, M& dist){
    consoleLogFirst("init in Viewer.h");
    for (auto elem: data.stage){
        //elem.drawa
    }

    src.createStage(data.stage);
    src.createRacers(data.racers, dist);
    src.drawAll(dist);
}

template <typename T, typename M>
void Viewer::render (T& data, ::Response<RACER>, M& dist){
    consoleLogFirst("racer in Viewer.h");
    //src.updateRacer(data.racer._id, data.racer);
}

template <typename T, typename M>
void Viewer::render (T& data, ::Response<ENEMIES>, M& dist){
    consoleLogFirst("enemies in Viewer.h");
//    for (auto racer: data.enemies) {
//        src.updateRacer(racer._id, racer);
//    }
}

template <typename T, typename M>
void Viewer::render (T& data, ::Response<CHANGE_STAGE>, M& dist){
    consoleLogFirst("change_stage in Viewer.h");
    //src.createStage(data.stage, dist);
}

template <typename T, typename M>
void Viewer::render (T& data, ::Response<DYNAMIC_OBJECTS>, M& dist){
    consoleLogFirst("dynamic_objects in Viewer.h");
    //src.updateDynamics(data.elements);
}
template <typename T, typename M>
void Viewer::render(T &data, ::Response<RENDER>, M &dist) {
    consoleLogFirst("render in Viewer.h");

}
