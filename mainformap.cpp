//
// Created by Kseny
//

#include "drawableLine.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window/Event.hpp>
#include <drawableObjects.hpp>

std::vector<abstractElement> makeStage();

int main() {
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "Tile");

    // линия
    abstractElement elemLine{
        {170, 160}, {200, 150}, {400, 200}, false, std::make_shared<DrawableLine>(),
    };
    elemLine.createDrawable(0);

    // дуги, образующие окружность
    abstractElement elemArc{
        {200, 150}, {170, 160}, {200, 200}, false, std::make_shared<DrawableArc>(),
    };
    elemArc.createDrawable(0);

    abstractElement elemArc2{
        {170, 160}, {200, 150}, {200, 200}, false, std::make_shared<DrawableArc>(),
    };
    elemArc2.createDrawable(0);

    // stage (интересно было попробовать)
    std::vector<abstractElement> elems = makeStage();

    // отрисовка
    while (window.isOpen()) {
        elemLine.draw(window);
        elemArc.draw(window);
        elemArc2.draw(window);
        for (auto el : elems) {
            el.draw(window);
        }
        window.display();
        window.clear(sf::Color::White);
    }
}

std::vector<abstractElement> makeStage() {
    std::vector<abstractElement> stage{{{50, 550}, {50, 750}, {0, 0}, false, std::make_shared<DrawableLine>()},
                                       {{150, 550}, {150, 750}, {0, 0}, false, std::make_shared<DrawableLine>()},
                                       {{350, 550}, {50, 550}, {200, 550}, false, std::make_shared<DrawableArc>()},
                                       {{200, 550}, {150, 550}, {175, 550}, false, std::make_shared<DrawableArc>()},
                                       {{200, 550}, {400, 750}, {400, 550}, false, std::make_shared<DrawableArc>()},
                                       {{350, 550}, {400, 600}, {400, 550}, false, std::make_shared<DrawableArc>()},
                                       {{400, 600}, {500, 500}, {400, 500}, false, std::make_shared<DrawableArc>()},
                                       {{400, 750}, {500, 750}, {0, 0}, false, std::make_shared<DrawableLine>()},
                                       {{500, 750}, {600, 650}, {500, 650}, false, std::make_shared<DrawableArc>()},
                                       {{600, 650}, {600, 50}, {0, 0}, false, std::make_shared<DrawableLine>()},
                                       {{500, 500}, {500, 50}, {0, 0}, false, std::make_shared<DrawableLine>()}};
    for (auto el : stage) {
        el.createDrawable(0);
    }
    return stage;
}