#include "drawableRacer.hpp"
#include "mechanicalValues.hpp"
#include "sfColor.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/VertexArray.hpp>

void DrawableRacer::loadSources() {

    imCar.loadFromFile("../media/fire.png");
    imCar.createMaskFromColor(sf::Color::Magenta);
    textureCar.loadFromImage(imCar);
    textureCar.setSmooth(true);

    imFire.loadFromFile("../media/fire.png");
    imFire.createMaskFromColor(sf::Color::Magenta);
    textureFire.loadFromImage(imFire);
    textureFire.setSmooth(true);
}

void DrawableRacer::setPos(const std::pair<Point, Point> &pos) {
    car.setPosition(pos.first.x, pos.first.y);
    fire.setPosition(pos.first.x, pos.first.y);
}

void DrawableRacer::setPos(const Point &center) {
    car.setPosition(center.x, center.y);
    fire.setPosition(center.x, center.y);
}

void DrawableRacer::setPos(const std::pair<Point, Point> &pos, sf::RenderWindow &window) {
    auto currentPos = window.mapCoordsToPixel(sf::Vector2f(pos.first.x, pos.first.y));
    car.setPosition((float)currentPos.x, (float)currentPos.y);
    fire.setPosition(pos.first.x, pos.first.y);
}

void DrawableRacer::setRot(const float &rotation) {
    car.setRotation(-rotation);
    fire.setRotation(-rotation);
}

void DrawableRacer::changeFire(const Speed &speed) {
    // float absSpeed = powf( (powf(speed.speedX,2) + powf(speed.speedY,2)), 0.5);
    // fire.setColor(sf::Color(255,255,255,((int)absSpeed)%225));
}

// DrawableRacer::DrawableRacer(float width, float height, int id) {
//     loadSources();
//     car.setOrigin(width / 4, height / 2);
//     car.setTexture(textureCar);
//     sfColor chooseColor;
//     car.setColor(chooseColor.getCar(id));
//     fire.setOrigin(-width / 4, height / 2);
//     fire.setTexture(textureFire);
// }

DrawableRacer::DrawableRacer(float width, float height, Point origin, int id, float rotation) {
    loadSources();

    point1 = sf::CircleShape(5);
    point2 = sf::CircleShape(5);
    point3 = sf::CircleShape(5);
    point4 = sf::CircleShape(5);

    point1.setOrigin(origin.x, origin.y);
    point2.setOrigin(origin.x, origin.y);
    point3.setOrigin(origin.x, origin.y);
    point4.setOrigin(origin.x, origin.y);

    point1.setFillColor(sf::Color::Black);
    point2.setFillColor(sf::Color::Black);
    point3.setFillColor(sf::Color::Blue);
    point4.setFillColor(sf::Color::Blue);

    car.setTexture(textureCar);
    car.setTextureRect(sf::IntRect(0, 0, (int)width / 2, (int)height));
    car.setOrigin(origin.x - width / 2, origin.y);
    sfColor chooseColor;
    car.setColor(chooseColor.getCar(id));

    fire.setTexture(textureFire);
    fire.setTextureRect(sf::IntRect(0, 0, (int)width / 2, (int)height));
    fire.setOrigin(origin.x, origin.y);

    setRot(rotation);
}

void DrawableRacer::draw(const Racer &racer, sf::RenderWindow &window) {
    setPos(racer._center);
    setRot(racer._rotation);
    setPos(racer);
    changeFire(racer._speed);
    drawWindow(window);
}

void DrawableRacer::drawWindow(sf::RenderWindow &window) {
    window.draw(car);
    window.draw(fire);

    window.draw(point1);
    window.draw(point2);
    window.draw(point3);
    window.draw(point4);
}

void DrawableRacer::setPos(const Racer& racer) {
    point1.setPosition(racer._position.first.x, racer._position.first.y);
    point2.setPosition(racer._position.second.x, racer._position.second.y);
    point3.setPosition(racer._positionExtra.first.x, racer._positionExtra.first.y);
    point4.setPosition(racer._positionExtra.second.x, racer._positionExtra.second.y);
}
