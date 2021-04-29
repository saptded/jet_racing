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

#define PI 3.14159


ViewerSourceRacer::ViewerSourceRacer(Point point) {
    float length = fabs(points[1].x - points[0].x);
    float height = fabs(points[0].y - points[1].y);
    car.setSize(sf::Vector2f(length, height/2));
    car.setOrigin(length,0);
    car.setFillColor(sf::Color::Cyan);
    car.setPosition(points[0].x, points[0].y);

    fire.setSize(sf::Vector2f(length, height/2));
    fire.setOrigin(length,-height/2);
    fire.setPosition(points[0].x, points[0].y);
    fire.setFillColor(sf::Color::Red);

    zeroAngle = countAngle(points);
}
void ViewerSourceRacer::setPos(float x, float y) {
    car.setPosition(x, y);
    fire.setPosition(x, y);
}
void ViewerSourceRacer::setRot(Point * points) {
    car.setRotation(countAngle(points) - zeroAngle);
    fire.setRotation(countAngle(points) - zeroAngle);
}
float ViewerSourceRacer::countAngle(Point *p) {
    float angl = atan2f(p[1].x-p[0].x, p[1].y-p[0].y) * 180 / PI;
    if (angl < 0){
        angl +=180;
    }
    return angl;
}
void ViewerSourceRacer::drawRacer(sf::RenderWindow &window) {
    window.draw(fire);
    window.draw(car);
}
