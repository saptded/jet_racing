//
// Created by Kseny
//

#include "drawableRacer.hpp"
#include "mechanicalValues.hpp"
#include "sfColor.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <cmath>

void DrawableRacer::loadSources() {
    imCar.loadFromFile("../media/car2.png");
    imCar.createMaskFromColor(sf::Color::Magenta);
    textureCar->loadFromImage(imCar);
    textureCar->setSmooth(true);

    imFire.loadFromFile("../media/fire2.png");
    imFire.createMaskFromColor(sf::Color::Magenta);
    textureFire.loadFromImage(imFire);
    textureFire.setSmooth(true);
}

void DrawableRacer::setPos(const std::pair<Point, Point> &pos) {
    car.setPosition(pos.first.x, pos.first.y);
    fire.setPosition(pos.first.x, pos.first.y);
}
void DrawableRacer::setRot(const float &rotation) {
    float copiedRot = rotation;
    if (copiedRot < 0) {
        copiedRot += 180;  // вроде такого недложно случится но если засунуть в sfml rotation<0, будет sigsegv
    }
    car.setRotation(copiedRot + 90);
    fire.setRotation(copiedRot + 90);
}

void DrawableRacer::changeFire(const Speed &speed) {
    float absSpeed = powf((powf(speed.speedX, 2) + powf(speed.speedY, 2)), 0.5);
    fire.setColor(sf::Color(255, 255, 255, ((int)absSpeed) % 225));
}

DrawableRacer::DrawableRacer(float width, float height, int id) : textureCar(new sf::Texture) {
    loadSources();
    car.setOrigin(width / 4, height / 2);
    car.setTexture(*textureCar);
    sfColor chooseColor;
    car.setColor(chooseColor.getCar(id));
    fire.setOrigin(-width / 4, height / 2);
    fire.setTexture(textureFire);
}

void DrawableRacer::draw(const Racer &racer, sf::RenderWindow &window) {
    setPos(racer._position);
    setRot(racer._rotation);
    changeFire(racer._speed);
    drawWindow(window);
    std::cout << "i try" << std::endl;
}
void DrawableRacer::drawWindow(sf::RenderWindow &window) {
    window.draw(car);
    window.draw(fire);
    // std::cout << "i try" << std::endl;
}
