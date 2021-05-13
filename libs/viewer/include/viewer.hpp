//
// Created by Kseny
//

#pragma once

#include "response.hpp"
#include <iostream>
#include <optional>
#include <sfViewerDetails.hpp>

class Viewer {
public:
    Viewer();
    // template <typename T, typename M>
    void render(Response &data, sf::RenderWindow &dist) {
        switch (data.eventType) {
            case INIT: break;
            case RACER: renderRacer(data, dist); break;
            case ENEMIES: break;
            case STAGE: renderMap(data, dist); break;
            case CHANGE_STAGE: break;
            case RENDER: displayWindow(dist); break;
            case RESULTS: break;
        }
        //        render(data, data.eventType, dist);
    };

private:
    //    void init(const Response &data, sf::RenderWindow &dist);
    void renderMap(Response &data, sf::RenderWindow &dist);
    void displayWindow(sf::RenderWindow& dist);
    void renderRacer(Response &data, sf::RenderWindow &dist);
    //    //template <typename T, typename M>
    //    void render (Response data, , sf::RenderWindow &dist);
    //    template <typename T, typename M> void render (T& data, ::Response<RACER>, M& dist);
    //    template <typename T, typename M> void render (T& data, ::Response<ENEMIES>, M& dist);
    //    template <typename T, typename M> void render (T& data, ::Response<STAGE>, M& dist);
    //    template <typename T, typename M> void render (T& data, ::Response<CHANGE_STAGE>, M& dist);
    //    template <typename T, typename M> void render (T& data, ::Response<RENDER>, M& dist);

    std::shared_ptr<sfViewerDetails> details;
    int stage = 1;
};

// void Viewer::init(const Response &data, sf::RenderWindow &dist) {
//     stage = 1;
//     data.racer.value()->createDrawable();
//     for (auto enemy : data.enemies.value()) {
//         enemy.createDrawable();
//     }
//     for (auto elem : data.map.value()) {
//         elem.createDrawable(stage);
//     }
//     details->init(data.racer.value(), dist);
// }

// template <typename T, typename M>
// void Viewer::render (T& data, ::Response<RACER>, M& dist){
//     data.racer.draw(dist);
//     details->update(data.racer);
// }
//
// template <typename T, typename M>
// void Viewer::render (T& data, ::Response<ENEMIES>, M& dist){
//     for (auto &enemy: data.enemies) {
//         enemy.draw(dist);
//     }
// }
//
// template <typename T, typename M>
// void Viewer::render (T& data, ::Response<CHANGE_STAGE>, M& dist){
//     stage+=1;
//     for (auto &elem: data.stage){
//         elem.createDrawable(stage);
//         elem.draw(dist);
//     }
// }
//

// template <typename T, typename M>
// void Viewer::render(T &data, ::Response<RENDER>, M &dist) {
//     details->display(dist, stage);
// }
