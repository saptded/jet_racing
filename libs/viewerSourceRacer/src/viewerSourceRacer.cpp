//
// Created by Kseny
//

#include "viewerSourceRacer.hpp"
#include "utils.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <cmath>


ViewerSourceRacer::ViewerSourceRacer(float width, float height, int id) {
    car.setSize(sf::Vector2f(width/2, height));
    car.setOrigin(width/4, height/2);
    if(id == 0){
        car.setFillColor(sf::Color::Cyan);
    } else {
        car.setFillColor(sf::Color::Blue);
    }

    fire.setSize(sf::Vector2f(width/2, height));
    fire.setOrigin(-width/4,height/2);
    fire.setFillColor(sf::Color::Red);
}
void ViewerSourceRacer::setPos(Point& pos) {
    car.setPosition(pos.x, pos.y);
    fire.setPosition(pos.x, pos.y);
}
void ViewerSourceRacer::setRot(float rotation) {
    if (rotation < 0){
        rotation+=180; // вроде такого недложно случится но если засунуть в sfml rotation<0, будет sigsegv
    }
    car.setRotation(rotation);
    fire.setRotation(rotation);
}

void ViewerSourceRacer::drawRacer(sf::RenderWindow &window) {
    window.draw(fire);
    window.draw(car);
}
