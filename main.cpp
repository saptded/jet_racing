//
// Created by Kseny
//

#include "modelResponse.hpp"
#include "viewer.hpp"
#include <SFML/Window/Event.hpp>

void handlePlayerInput(sf::Keyboard::Key key, bool isPressed, ResponseRacer& respRacer);

int main() {

    float width_car = 80;
    float height_car_fire = 320;
    Point points[2];
    points[0] = {400,40};
    points[1] = {points[0].x-width_car, points[0].y-height_car_fire};
    Speed speed = {10, 10};
    ResponseRacer respRacer{
        points, speed, 0
    };

    std::vector<ResponseRacer> respRacerVec;
    respRacerVec.push_back(respRacer);
    std::vector<abstractElement> stage;
    ResponseInit respInit {
        respRacerVec, stage
    };

    sf::RenderWindow window(sf::VideoMode(800, 500), "Tile");
    Viewer viewer;
    viewer.render(respInit, window);

    ResponseRender respRender;
    while(window.isOpen()){

        /* Да здравствует грамотное разделение н функции! */
        sf::Event event;
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
    } else if (key == sf::Keyboard::Up){
        respRacer.points[0].y -=5;
        respRacer.points[1].y -=5;
    } else if (key == sf::Keyboard::Down){
        respRacer.points[0].y +=5;
        respRacer.points[1].y +=5;
    }
//        else if (key == sf::Keyboard::Left)
//            mineMap.getBoy()->setMoving(1, isPressed);
//
//        else if (key == sf::Keyboard::Right)
//            mineMap.getBoy()->setMoving(3, isPressed);
};

rotate(){

}