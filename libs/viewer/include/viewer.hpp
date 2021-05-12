//
// Created by Kseny
//

#pragma once

#include "response.hpp"
#include "utils.hpp"
#include <iostream>
#include <sfViewerDetails.hpp>

class Viewer {
public:
    Viewer(){
        details = std::make_shared<sfViewerDetails>();
    };
    template <typename T, typename M> void render(T& data, M& dist) {
        render(data, typename T::Response(), dist);
    };
private:
    template <typename T, typename M> void render (T& data, ::Response<INIT>, M& dist);
    template <typename T, typename M> void render (T& data, ::Response<RACER>, M& dist);
    template <typename T, typename M> void render (T& data, ::Response<ENEMIES>, M& dist);
    template <typename T, typename M> void render (T& data, ::Response<STAGE>, M& dist);
    template <typename T, typename M> void render (T& data, ::Response<CHANGE_STAGE>, M& dist);
    template <typename T, typename M> void render (T& data, ::Response<RENDER>, M& dist);

    std::shared_ptr<sfViewerDetails> details;
    int stage = 1;
};

template <typename T, typename M>
void Viewer::render (T& data, ::Response<INIT>, M& dist){
    stage = 1;
    data.racer.createDrawable();
    for (auto &enemy: data.enemies){
        enemy.createDrawable();
    }
    for (auto &elem: data.stage){
        elem.createDrawable(stage);
    }
    details->init(data.racer, dist);
}

template <typename T, typename M>
void Viewer::render (T& data, ::Response<RACER>, M& dist){
    data.racer.draw(dist);
    details->update(data.racer);
}

template <typename T, typename M>
void Viewer::render (T& data, ::Response<ENEMIES>, M& dist){
    for (auto &enemy: data.enemies) {
        enemy.draw(dist);
    }
}

template <typename T, typename M>
void Viewer::render (T& data, ::Response<CHANGE_STAGE>, M& dist){
    stage+=1;
    for (auto &elem: data.stage){
        elem.createDrawable(stage);
        elem.draw(dist);
    }
}

template <typename T, typename M>
void Viewer::render (T& data, ::Response<STAGE>, M& dist){
    for (auto &elem: data.stage){
        elem.draw(dist);
    }
}
template <typename T, typename M>
void Viewer::render(T &data, ::Response<RENDER>, M &dist) {
    details->display(dist, stage);
}
