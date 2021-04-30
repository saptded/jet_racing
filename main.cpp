//
// Created by Kseny
//

#include "modelResponse.hpp"
#include "viewer.hpp"
#include <SFML/Window/Event.hpp>
#include <cmath>

#define PI 3.14159
static float calcRadius(Point& one, Point& two){
    return sqrtf(powf(one.x-two.x, 2) + powf(one.y-two.y, 2));
}
static float getAngle(Point& rad, Point& center){
    float angle;
    if(rad.y - center.y == 0){
        if(rad.x > center.x){
            angle = 0;
        } else {
            angle = PI;
        }
        return angle;
    } else if (rad.x - center.x == 0){
        if(rad.y > center.y){
            angle = PI/2;
        } else {
            angle = -PI/2;
        }
        return angle;
    }
    angle = acosf((rad.x - center.x)/ calcRadius(rad, center));
    if (rad.y < center.y){
        std::cout << "angle from acos " << angle << std::endl;
        angle = 2*PI-angle;
    }
    return angle;
};

void handlePlayerInput(sf::Keyboard::Key key, bool isPressed, ResponseRacer& respRacer);
std::vector<abstractElement> makeStage();
int maihn(){
    Point rad = {1,-1};
    Point center = {0, 0};
    float angle = getAngle(rad, center);
    std::cout << angle << std::endl;
    std::cout << cosf(angle) << std::endl;
}

int main() {

    auto stage = makeStage();

    float height_car = 80;
    float width_car_fire = 320;
    Point point = {100, 100};
    Speed speed = {10, 10};

    std::vector<ResponseRacer> respRacerVec;
    ResponseRacer respRacer{
        point, speed, 0, 0
    };
    respRacerVec.push_back(respRacer);
    for(int i = 1; i < 4; i++){
        point.x+=200;
        point.y+=100;
        ResponseRacer respRacerEnemy{
            point, speed, 0, i
        };
        respRacerVec.push_back(respRacerEnemy);
    }

    sf::RenderWindow window(sf::VideoMode(1200, 1000), "Tile");
    Viewer viewer;
    ResponseInit respInit {
        width_car_fire, height_car, respRacerVec, stage
    };
    viewer.render(respInit, window);
    viewer.render(respRacer, window);
    ResponseEnemies respEnemies;
    respEnemies.enemies = respRacerVec; // по идее здесь в векторе не должно быть самогого игрока!
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
        if (respRacer.rotation > 360){
            respRacer.rotation -= 360;
        } else if (respRacer.rotation < 360){
            respRacer.rotation += 360;
        }
        viewer.render(respRacer, window);
        viewer.render(respRender, window);
    }
    return 0;
}

void handlePlayerInput(sf::Keyboard::Key key, bool isPressed, ResponseRacer& respRacer){
    if (key == sf::Keyboard::S) {
        respRacer.speed.speedX++;
        respRacer.speed.speedY++;
        std::cout << respRacer.speed.speedX << " " << respRacer.speed.speedY;
    } else if (key == sf::Keyboard::A) {
        respRacer.speed.speedX--;
        respRacer.speed.speedY--;
    } else if (key == sf::Keyboard::D) {
        respRacer.rotation -=2;;
    } else if (key == sf::Keyboard::F){
        respRacer.rotation +=2;
    } else if (key == sf::Keyboard::Up){
        respRacer.point.y -=5;
        respRacer.point.y -=5;
    } else if (key == sf::Keyboard::Down){
        respRacer.point.y +=5;
        respRacer.point.y +=5;
    } else if (key == sf::Keyboard::Left){
        respRacer.point.x -=5;
        respRacer.point.x -=5;
    } else if (key == sf::Keyboard::Right){
        respRacer.point.x +=5;
        respRacer.point.x +=5;
    }
};

std::vector<abstractElement> makeStage(){
    float scale = 1; // хотела сделатоь масштабирование, осознала что так просто не получится
    std::vector<abstractElement> stage;
    stage.push_back({line, {50,750}, {50,550}});
    stage.push_back({line, {150,750}, {150,550}});
    stage.push_back({arcTime, {50,550}, {350,550},{200,550}});
    stage.push_back({arcTime, {150,550}, {200,550},{175,550}});
    stage.push_back({arcNtime, {200,550}, {400,750},{400,550}});
    stage.push_back({arcNtime, {350,550}, {400,600},{400,550}});
    stage.push_back({arcNtime, {400,600}, {500,500},{400,500}});
    stage.push_back({line, {400,750}, {500,750}});
    stage.push_back({arcNtime, {500,750}, {600,650},{500,650}});
    stage.push_back({line, {600,650}, {600,50}});
    stage.push_back({line, {500,500}, {500,50}});
    return stage;
}