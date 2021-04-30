//
// Created by Kseny
//

#pragma once

#include "response.hpp"
#include "viewerSource.hpp"
#include "viewerSourceRacer.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/VertexArray.hpp>

class ViewerSource {
public:
    void createStage(std::vector<abstractElement>& elements);
    void createRacers(std::vector<ResponseRacer>&, float width, float height, sf::RenderWindow&);

    void updateDynamics(ResponseDynamicObjects&);
    void updateRacer(int id, ResponseRacer&);

    void drawAll(sf::RenderWindow&);

private:
    //sf::View view;
    //void updateView();

    int stage = 0;
    std::vector<sf::VertexArray> walls;
    //sf::RectangleShape racer;
    //std::vector<sf::RectangleShape> enemies;
    std::vector<sf::RectangleShape> dynamicObjects;
    std::vector<ViewerSourceRacer> racers;// 0 - наш, далее соперники в соответствии с id (см. response.hpp)

    sf::VertexArray createArc(abstractElement&);
    sf::VertexArray createLine(abstractElement&);

    void drawStage(sf::RenderWindow& window);


    //    sf::Image carIm, fireIm;
    //    sf::Texture car, fire;
    //    Colors* color;
};
