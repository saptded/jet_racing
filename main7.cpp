//
// Created by Kseny
//

#include "drawableLine.hpp"
//#include "viewer.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window/Event.hpp>
#include <cmath>

#define PI 3.14159
//static float calcRadius(Point& one, Point& two){
//    return sqrtf(powf(one.x-two.x, 2) + powf(one.y-two.y, 2));
//}
//static float getAngle(Point& rad, Point& center){
//    float angle;
//    if(rad.y - center.y == 0){
//        if(rad.x > center.x){
//            angle = 0;
//        } else {
//            angle = PI;
//        }
//        return angle;
//    } else if (rad.x - center.x == 0){
//        if(rad.y > center.y){
//            angle = PI/2;
//        } else {
//            angle = -PI/2;
//        }
//        return angle;
//    }
//    angle = acosf((rad.x - center.x)/ calcRadius(rad, center));
//    if (rad.y < center.y){
//        std::cout << "angle from acos " << angle << std::endl;
//        angle = 2*PI-angle;
//    }
//    return angle;
//};
//
//void handlePlayerInput(sf::Keyboard::Key key, bool isPressed, ResponseRacer& respRacer);
//std::vector<abstractElement> makeStage();
//
int main(){
    DrawableLine line;
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "Tile");
    window.clear(sf::Color::White);
    window.display();
    abstractElement elem {
        notype,
        {100,100},
        {200, 200},
        {300,300},
        line,
        false
    };
    elem.create();
    while(window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                    window.clear(sf::Color::White);
                    elem.draw(window);
                    window.display();
                    break;
            }
        }
    }
}

int mainview(){
    sf::RenderWindow window(sf::VideoMode(1200, 1000), "Tile");
    sf::View view;
    sf::RectangleShape someSprite;
    someSprite.setFillColor(sf::Color::Cyan);
    someSprite.setSize(sf::Vector2f(40,60));
    someSprite.setPosition(100,100);
// Initialize the view to a rectangle located at (100, 100) and with a size of 400x200
    view.reset(sf::FloatRect(95, 95, 50, 70));
// Rotate it by 45 degrees
//    view.rotate(45);
// Set its target viewport to be half of the window
    //view.setViewport(sf::FloatRect(0.5f, 0.f, 0.5f, 1.f));
// Apply it
    window.setView(view);
// Render stuff
    while(window.isOpen()){
        window.clear(sf::Color::White);
        window.draw(someSprite);
        window.display();
// Set the default view back
        sf::Event event{};
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                    window.clear(sf::Color::White);
                    window.setView(window.getDefaultView());
// Render stuff not affected by the view
                    window.draw(someSprite);
                    window.display();
                    break;
            }
        }

    }
}

//int mainkl() {
//
//    auto stage = makeStage();
//
//    Point point = {100, 100};
//
//    auto racer = Racer(point, 0);
//
//    ResponseRacer respRacer{racer};
//    std::vector<Racer> racers;
//    racers.push_back(racer);
//    std::vector<Racer> enemies;
//
//    for(int i = 1; i < 4; i++){
//        point.x+=200;
//        point.y+=100;
//        auto enemy = Racer(point, i);
//        enemies.push_back(enemy);
//        racers.push_back(enemy);
//    }
//
//    sf::RenderWindow window(sf::VideoMode(1200, 1000), "Tile");
//    Viewer viewer;
//    ResponseInit respInit {
//        racers, stage
//    };
//    viewer.render(respInit, window);
//    viewer.render(respRacer, window);
//    ResponseEnemies respEnemies = {enemies};
//    viewer.render(respEnemies, window);
//
//    ResponseRender respRender;
//    while(window.isOpen()){
//
//        sf::Event event{};
//        while (window.pollEvent(event))
//        {
//            switch (event.type)
//            {
//                case sf::Event::KeyPressed:
//                    handlePlayerInput(event.key.code, true, respRacer);
//                    break;
//                case sf::Event::KeyReleased:
//                    handlePlayerInput(event.key.code, false, respRacer);
//                    break;
//                case sf::Event::Closed:
//                    window.close();
//                    break;
//            }
//        }
//
//        /* */
//        if (racer._rotation > 360){
//            racer._rotation -= 360;
//        } else if (racer._rotation < 360){
//            racer._rotation += 360;
//        }
//        viewer.render(respRacer, window);
//        viewer.render(respRender, window);
//    }
//    return 0;
//}
//
//void handlePlayerInput(sf::Keyboard::Key key, bool isPressed, ResponseRacer& respRacer){
//    if (key == sf::Keyboard::S) {
//        respRacer.racer._speed.speedX++;
//        respRacer.racer._speed.speedY++;
//    } else if (key == sf::Keyboard::A) {
//        respRacer.racer._speed.speedX--;
//        respRacer.racer._speed.speedY--;
//    } else if (key == sf::Keyboard::D) {
//        respRacer.racer._rotation -=2;;
//    } else if (key == sf::Keyboard::F){
//        respRacer.racer._rotation +=2;
//    } else if (key == sf::Keyboard::Up){
//        respRacer.racer._position.first.y -=5;
//        respRacer.racer._position.first.y -=5;
//    } else if (key == sf::Keyboard::Down){
//        respRacer.racer._position.first.y +=5;
//        respRacer.racer._position.first.y +=5;
//    } else if (key == sf::Keyboard::Left){
//        respRacer.racer._position.first.x -=5;
//        respRacer.racer._position.first.x -=5;
//    } else if (key == sf::Keyboard::Right){
//        respRacer.racer._position.first.x +=5;
//        respRacer.racer._position.first.x +=5;
//    }
//};
//
//std::vector<abstractElement> makeStage(){
//    float scale = 1; // хотела сделатоь масштабирование, осознала что так просто не получится
//    std::vector<abstractElement> stage;
//    stage.push_back({line, {50,750}, {50,550}});
//    stage.push_back({line, {150,750}, {150,550}});
//    stage.push_back({arcTime, {50,550}, {350,550},{200,550}});
//    stage.push_back({arcTime, {150,550}, {200,550},{175,550}});
//    stage.push_back({arcNtime, {200,550}, {400,750},{400,550}});
//    stage.push_back({arcNtime, {350,550}, {400,600},{400,550}});
//    stage.push_back({arcNtime, {400,600}, {500,500},{400,500}});
//    stage.push_back({line, {400,750}, {500,750}});
//    stage.push_back({arcNtime, {500,750}, {600,650},{500,650}});
//    stage.push_back({line, {600,650}, {600,50}});
//    stage.push_back({line, {500,500}, {500,50}});
//    return stage;
//}