//
// Created by Kseny
//

#include "drawableRacer.hpp"
#include "utils.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <cmath>

void drawableRacer::loadSources() {
    imCar.loadFromFile("media/car2.png");
    imCar.createMaskFromColor(sf::Color::Magenta);
    textureCar.loadFromImage(imCar);
    textureCar.setSmooth(true);

    imFire.loadFromFile("media/fire2.png");
    imFire.createMaskFromColor(sf::Color::Magenta);
    textureFire.loadFromImage(imFire);
    textureFire.setSmooth(true);
}

drawableRacer::drawableRacer(float width, float height, int id) {
    loadSources();
    car.setOrigin(width/4, height/2);
    car.setTexture(textureCar);
    if(id == 0){
        car.setColor(sf::Color::Red);
    } else {
        car.setColor(sf::Color::Blue);
    }
    fire.setOrigin(-width/4,height/2);
    fire.setTexture(textureFire);
}
void drawableRacer::setPos(std::pair<Point,Point>& pos) {
    car.setPosition(pos.first.x, pos.first.y);
    fire.setPosition(pos.first.x, pos.first.y);
}
void drawableRacer::setRot(float rotation) {
    if (rotation < 0){
        rotation+=180; // вроде такого недложно случится но если засунуть в sfml rotation<0, будет sigsegv
    }
    car.setRotation(rotation);
    fire.setRotation(rotation);
}

void drawableRacer::changeFire(Speed speed){
    //
}

void drawableRacer::drawRacer(sf::RenderWindow &window) {
    window.draw(fire);
    window.draw(car);
}
