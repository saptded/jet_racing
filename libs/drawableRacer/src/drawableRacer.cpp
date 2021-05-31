#include "drawableRacer.hpp"
#include "mechanicalValues.hpp"
#include "sfColor.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/VertexArray.hpp>

void DrawableRacer::loadSources(bool isOwn) {
    if(isOwn){
        image.loadFromFile("../media/carfire2.png");
    } else {
        image.loadFromFile("../media/firecar.png");
    }
    //image.createMaskFromColor(sf::Color::Magenta);
    texture.loadFromImage(image);
    texture.setSmooth(true);
}

void DrawableRacer::setPos(const Point &center) {
    car.setPosition(center.x, center.y);
    fire.setPosition(center.x, center.y);
}

void DrawableRacer::setRot(const float &rotation) {
    car.setRotation(-rotation);
    fire.setRotation(-rotation);
}

DrawableRacer::DrawableRacer(float width, float height, Point origin, int id, float rotation, bool isOwn) {
    loadSources(isOwn);
    unsigned int widthT = texture.getSize().x;
    unsigned int heightT = texture.getSize().y;

    sf::Vector2f scale = sf::Vector2f(width/(float)widthT, 1.1f*(height/(float)heightT));
    // здесь увеличивается ширина отображения

    car.setTexture(texture);
    car.setTextureRect(sf::IntRect(int(widthT/2), 0, (int)widthT / 2, (int)heightT));

    car.setScale(scale);
    car.setOrigin(origin.x / scale.x - (float)widthT / 2, origin.y / scale.y);
    sfColor chooseColor;
    if(!isOwn){
        car.setColor(chooseColor.getCar(id));
    }
    fire.setTexture(texture);
    fire.setTextureRect(sf::IntRect(0, 0, (int)widthT / 2, (int)heightT));
    fire.setOrigin(origin.x / scale.x, origin.y / scale.y);
    fire.setScale(scale);
    fire.setColor(chooseColor.fire);
}

void DrawableRacer::draw(const Racer &racer, sf::RenderWindow &window) {
    setPos(racer._center);
    setRot(racer._rotation);
    drawWindow(window);
}

void DrawableRacer::drawWindow(sf::RenderWindow &window) {
    window.draw(car);
    window.draw(fire);
}
