#include "drawableRacer.hpp"
#include "mechanicalValues.hpp"
#include "sfColor.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/VertexArray.hpp>

void DrawableRacer::loadSources() {
    image.loadFromFile("../media/carfire2.png");
    image.createMaskFromColor(sf::Color::Magenta);
    texture.loadFromImage(image);
    texture.setSmooth(true);
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

DrawableRacer::DrawableRacer(float width, float height, Point origin, int id, float rotation) {
    loadSources();

    unsigned int widthT = texture.getSize().x;
    unsigned int heightT = texture.getSize().y;

//    pointBottom = sf::CircleShape(2);
//    pointCenter = sf::CircleShape(2);
//    point1 = sf::CircleShape(2);
//    point2 = sf::CircleShape(2);
//    pointBottom.setFillColor(sf::Color::Blue);
//    pointCenter.setFillColor(sf::Color::Blue);
//    point1.setFillColor(sf::Color::Blue);
//    point2.setFillColor(sf::Color::Blue);

    sf::Vector2f scale = sf::Vector2f(width/(float)widthT, height/(float)heightT);

    car.setTexture(texture);
    car.setTextureRect(sf::IntRect(int(widthT/2), 0, (int)widthT / 2, (int)heightT));

    car.setScale(scale);
    car.setOrigin(origin.x / scale.x - widthT / 2, origin.y / scale.y);

    sfColor chooseColor;
    car.setColor(chooseColor.getCar(id));

    fire.setTexture(texture);
    fire.setTextureRect(sf::IntRect(0, 0, (int)widthT / 2, (int)heightT));
    fire.setOrigin(origin.x / scale.x, origin.y / scale.y);
    fire.setScale(scale);
    fire.setColor(chooseColor.fire);

//    float scale = height/(float)textureSize.y;
//
//    car.setTexture(texture);
//    car.setTextureRect(sf::IntRect(textureSize.x / 2, 0, textureSize.x / 2, textureSize.y));
//    car.setScale(width/(float)textureSize.x, height/(float)textureSize.y);
//    car.setOrigin(origin.x - width / 2, origin.y);
//    sfColor chooseColor;
//    car.setColor(chooseColor.getCar(id));
//
//    fire.setTexture(texture);
//    fire.setTextureRect(sf::IntRect(600, 100, (int)width / 2, (int)height));
    //fire.setOrigin(origin.x, origin.y);

   // fire.setColor()
//    fire.setTexture(texture);
//    fire.setTextureRect(sf::IntRect(0, 0, textureSize.x / 2, textureSize.y));
//    car.setScale(width/textureSize.x, height/textureSize.y);
//    fire.setOrigin(origin.x, origin.y);

//    setRot(rotation);
}

void DrawableRacer::draw(const Racer &racer, sf::RenderWindow &window) {
    setPos(racer._center);
    setRot(racer._rotation);
    changeFire(racer._speed);

//    pointBottom.setPosition(racer._bottomCenter.x, racer._bottomCenter.y);
//    pointCenter.setPosition(racer._center.x, racer._center.y);
//    point1.setPosition(racer._position.first.x, racer._position.first.y);
//    point2.setPosition(racer._position.second.x, racer._position.second.y);

    drawWindow(window);
}

void DrawableRacer::drawWindow(sf::RenderWindow &window) {
    window.draw(car);
    window.draw(fire);

//    window.draw(pointBottom);
//    window.draw(pointCenter);
//    window.draw(point1);
//    window.draw(point2);
}
