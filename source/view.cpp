#include "View.h"
#include "iostream"

void View::HandleEvent(ModelResponse){
    std::cout << "HandleEvent во View" << std::endl;

};

View::View(sf::Window* given_window){
    window = given_window;
    stage = 1;
    std::cout << "Конструктор View" << std::endl;
};

void View::update(){
    std::cout << "update во View" << std::endl;
};
void View::renderMap(){
    std::cout << "renderMap во View" << std::endl;
};
void View::renderRacers(){
    std::cout << "renderRacers во View" << std::endl;
};

void View::finish(){
    std::cout << "finish во View" << std::endl;
};

