//
// Created by Kseny
//

#include "response.hpp"
#include "utils.hpp"
#include "viewer.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window/Event.hpp>
#include <drawableArc.hpp>
#include <drawableLine.hpp>

void handlePlayerInput(sf::Keyboard::Key key, bool isPressed, ResponseRacer& respRacer);
std::vector<abstractElement> makeStage();

//int mainv(){
//    sf::RenderWindow window(sf::VideoMode(1200, 1000), "Tile");
//    sf::View view;
//    sf::RectangleShape someSprite;
//    someSprite.setFillColor(sf::Color::Cyan);
//    someSprite.setSize(sf::Vector2f(40,60));
//    someSprite.setPosition(100,100);
//// Initialize the view to a rectangle located at (100, 100) and with a size of 400x200
//    view.reset(sf::FloatRect(95, 95, 50, 70));
//// Rotate it by 45 degrees
////    view.rotate(45);
//// Set its target viewport to be half of the window
//    //view.setViewport(sf::FloatRect(0.5f, 0.f, 0.5f, 1.f));
//// Apply it
//    window.setView(view);
//// Render stuff
//    while(window.isOpen()){
//        window.clear(sf::Color::White);
//        window.draw(someSprite);
//        window.display();
//// Set the default view back
//        sf::Event event{};
//        while (window.pollEvent(event))
//        {
//            switch (event.type)
//            {
//                case sf::Event::Closed:
//                    window.clear(sf::Color::White);
//                    window.setView(window.getDefaultView());
//// Render stuff not affected by the view
//                    window.draw(someSprite);
//                    window.display();
//                    break;
//            }
//        }
//
//    }
//}

int main() {

    auto stage = makeStage();
    Point point = {100, 100};

    auto racer = Racer(point, 0);
    ResponseRacer respRacer{racer};

    std::vector<Racer> enemies;
    for(int i = 1; i < 4; i++){
        point.x+=200;
        point.y+=100;
        auto enemy = Racer(point, i);
        enemies.push_back(enemy);
    }
    ResponseEnemies{enemies};

    sf::RenderWindow window(sf::VideoMode(1200, 1000), "Tile");
    Viewer viewer;
    ResponseInit respInit {
        racer, enemies, stage
    };
    viewer.render(respInit, window);

    ResponseStage respStage {
        stage
    };

    viewer.render(respRacer, window);
    ResponseEnemies respEnemies = {enemies};
    viewer.render(respEnemies, window);

    ResponseRender respRender;

    while(window.isOpen()){
        sf::Event event{};
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::KeyPressed:
                    handlePlayerInput(event.key.code, true, respRacer);
                    break;
                case sf::Event::KeyReleased:
                    handlePlayerInput(event.key.code, false, respRacer);
                    break;
                case sf::Event::Closed:
                    window.close();
                    break;
            }
        }

        /* */
        if (racer._rotation > 360){
            racer._rotation -= 360;
        } else if (racer._rotation < 360){
            racer._rotation += 360;
        }
        viewer.render(respStage, window);
        viewer.render(respEnemies, window);
        viewer.render(respRacer, window);
        viewer.render(respRender, window);
    }
    return 0;
}

void handlePlayerInput(sf::Keyboard::Key key, bool isPressed, ResponseRacer& respRacer){
    if (key == sf::Keyboard::S) {
        respRacer.racer._speed.speedX++;
        respRacer.racer._speed.speedY++;
    } else if (key == sf::Keyboard::A) {
        respRacer.racer._speed.speedX--;
        respRacer.racer._speed.speedY--;
    } else if (key == sf::Keyboard::D) {
        respRacer.racer._rotation -=2;;
    } else if (key == sf::Keyboard::F){
        respRacer.racer._rotation +=2;
    } else if (key == sf::Keyboard::Up){
        respRacer.racer._position.first.y -=5;
        respRacer.racer._position.first.y -=5;
    } else if (key == sf::Keyboard::Down){
        respRacer.racer._position.first.y +=5;
        respRacer.racer._position.first.y +=5;
    } else if (key == sf::Keyboard::Left){
        respRacer.racer._position.first.x -=5;
        respRacer.racer._position.first.x -=5;
    } else if (key == sf::Keyboard::Right){
        respRacer.racer._position.first.x +=5;
        respRacer.racer._position.first.x +=5;
    }
};

std::vector<abstractElement> makeStage(){
    std::vector<abstractElement> stage;
    stage.push_back({{50,550}, {50,750}, {0,0}, false, std::make_shared<DrawableLine>()});
    stage.push_back({{150,550}, {150,750}, {0,0}, false, std::make_shared<DrawableLine>()});
    stage.push_back({{350,550}, {50,550},{200,550}, false, std::make_shared<DrawableArc>()});
    stage.push_back({{200,550}, {150,550},{175,550}, false, std::make_shared<DrawableArc>()});
    stage.push_back({ {200,550},{400,750},{400,550}, false, std::make_shared<DrawableArc>()});
    stage.push_back({{350,550}, {400,600},{400,550}, false, std::make_shared<DrawableArc>()});
    stage.push_back({{400,600}, {500,500},{400,500}, false, std::make_shared<DrawableArc>()});
    stage.push_back({{400,750}, {500,750}, {0,0}, false, std::make_shared<DrawableLine>()});
    stage.push_back({{500,750}, {600,650},{500,650}, false, std::make_shared<DrawableArc>()});
    stage.push_back({{600,650}, {600,50}, {0,0}, false, std::make_shared<DrawableLine>()});
    stage.push_back({{500,500}, {500,50}, {0,0}, false, std::make_shared<DrawableLine>()});
    return stage;
}