#include "drawableRacer.hpp"
#include "mechanicalValues.hpp"
#include "sfColor.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/VertexArray.hpp>

void DrawableRacer::loadSources() {
    imCar.loadFromFile("/home/kseny/tp/JET/media/fire2.png");
    imCar.createMaskFromColor(sf::Color::Magenta);
    textureCar.loadFromImage(imCar);
    textureCar.setSmooth(true);

    imFire.loadFromFile("/home/kseny/tp/JET/media/car2.png");
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
    if(std::get<bool>(racer.finished)){

    }
    setPos(racer._center);
    setRot(racer._rotation);
    changeFire(racer._speed);
    drawWindow(window);
}

void DrawableRacer::drawWindow(sf::RenderWindow &window) {
    window.draw(car);
    window.draw(fire);
}
