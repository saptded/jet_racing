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

void DrawableRacer::loadSources() {
    imCar.loadFromFile("media/car2.png");
    imCar.createMaskFromColor(sf::Color::Magenta);
    textureCar.loadFromImage(imCar);
    textureCar.setSmooth(true);

    imFire.loadFromFile("media/fire2.png");
    imFire.createMaskFromColor(sf::Color::Magenta);
    textureFire.loadFromImage(imFire);
    textureFire.setSmooth(true);
}

void DrawableRacer::setPos(std::pair<Point,Point>& pos) {
    car.setPosition(pos.first.x, pos.first.y);
    fire.setPosition(pos.first.x, pos.first.y);
}
void DrawableRacer::setRot(float& rotation) {
    if (rotation < 0){
        rotation+=180; // вроде такого недложно случится но если засунуть в sfml rotation<0, будет sigsegv
    }
    car.setRotation(rotation);
    fire.setRotation(rotation);
}

void DrawableRacer::changeFire(Speed& speed){
    //
}

void DrawableRacer::create(Racer &racer) {
    loadSources();
    car.setOrigin(racer._width/4, racer._height/2);
    car.setTexture(textureCar);
    if(racer._id == 0){
        car.setColor(sf::Color::Red);
    } else {
        car.setColor(sf::Color::Blue);
    }
    fire.setOrigin(-racer._width/4,racer._height/2);
    fire.setTexture(textureFire);
}
void DrawableRacer::draw(Racer &racer, sf::RenderWindow &window) {
    setPos(racer._position);
    setRot(racer._rotation);
    changeFire(racer._speed);
    drawWindow(window);
}
void DrawableRacer::drawWindow(sf::RenderWindow &window) {
    window.draw(car);
    window.draw(fire);
}
