//
// Created by Kseny
//

#include "drawableLine.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window/Event.hpp>
#include <drawableArc.hpp>

std::vector<abstractElement> makeStage();

int main(){
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "Tile");
    window.clear(sf::Color::White);
    window.display();

    while(window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed: {
                    // одна линия
                    abstractElement elemLine {
                        {350,200},
                        {450, 200},
                        {400,200},
                        false,
                        std::make_shared<DrawableArc>(),
                    };
                    elemLine.createDrawable();
                    // одна дуга
                    DrawableArc arc;
                    abstractElement elemArc {
                        {170,160},
                        {200,150},
                        {200, 200},
                        false,
                        std::make_shared<DrawableArc>(),
                    };
                    elemArc.createDrawable();
                    // stage (интересно было попробовать)
                    std::vector<abstractElement> elems = makeStage();

                    //
                    window.clear(sf::Color::White);
                    elemLine.draw(window);
                    elemArc.draw(window);
                    for (auto el: elems){
                        el.draw(window);
                    }
                    window.display();
                    break;
                }
            }
        }
    }
}

std::vector<abstractElement> makeStage(){
    std::vector<abstractElement> stage;
    stage.push_back({{50,550}, {50,750}, {0,0}, false, std::make_shared<DrawableLine>()});
    stage.push_back({{150,550}, {150,750}, {0,0}, false, std::make_shared<DrawableLine>()});
    //stage.push_back({{350,550}, {100,550},{200,550}, false, std::make_shared<DrawableArc>()});
    stage.push_back({{200,550}, {150,550},{175,550}, false, std::make_shared<DrawableArc>()});
    stage.push_back({{200,550}, {400,750},{400,550}, false, std::make_shared<DrawableArc>()});
    stage.push_back({{350,550}, {400,600},{400,550}, false, std::make_shared<DrawableArc>()});
    stage.push_back({{400,600}, {500,500},{400,500}, false, std::make_shared<DrawableArc>()});
    stage.push_back({{400,750}, {500,750}, {0,0}, false, std::make_shared<DrawableLine>()});
    stage.push_back({{500,750}, {600,650},{500,650}, false, std::make_shared<DrawableArc>()});
    stage.push_back({{600,650}, {600,50}, {0,0}, false, std::make_shared<DrawableLine>()});
    stage.push_back({{500,500}, {500,50}, {0,0}, false, std::make_shared<DrawableLine>()});
    for (auto el: stage){
        el.createDrawable();
    }
    return stage;
}