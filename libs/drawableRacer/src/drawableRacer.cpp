#include "drawableRacer.hpp"
#include "mechanicalValues.hpp"
#include "sfColor.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

void DrawableRacer::loadSources(bool isOwn) { // разные текстуры для противников и себя
    if (isOwn) {
        image.loadFromFile("../media/racer.png");
//        sf::SoundBuffer soundBuffer;//создаём буфер для звука
//        soundBuffer.loadFromFile("../media/hit.ogg");//загружаем в него звук
//        hit = std::make_shared<sf::Sound>(soundBuffer);//создаем звук и загружаем в него звук из буфера
    } else {
        image.loadFromFile("../media/enemy.png");
        image.createMaskFromColor(sf::Color::Black);
    }
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

    sf::Vector2f scale = sf::Vector2f(width / (float) widthT, 1.1f * (height / (float) heightT));
    // здесь увеличивается ширина отображения

    car.setTexture(texture);
    car.setTextureRect(sf::IntRect(int(widthT / 2), 0, (int) widthT / 2, (int) heightT));

    car.setScale(scale);
    car.setOrigin(origin.x / scale.x - (float) widthT / 2, origin.y / scale.y);
    sfColor chooseColor;
    if (!isOwn) {
        car.setColor(chooseColor.getCar(id));
    }
    fire.setTexture(texture);
    fire.setTextureRect(sf::IntRect(0, 0, (int) widthT / 2, (int) heightT));
    fire.setOrigin(origin.x / scale.x, origin.y / scale.y);
    fire.setScale(scale);
    sf::Color color = chooseColor.fire;
    color.a -= 80;
    fire.setColor(color);
}

void DrawableRacer::draw(Racer &racer, sf::RenderWindow &window) {
    setPos(racer._center);
    setRot(racer._rotation);
//    if(racer.onCollision && hit && counter > 15){
//        racer.onCollision = false;
//        alreadyPlayed = true;
//        hit->play();
//        fire.setColor(sf::Color::Green);
//        counter = 0;
//    }
//    if(alreadyPlayed && counter > 5/*&& (counter > 15)*/){
//        alreadyPlayed = false;
//        fire.setColor(sf::Color::Magenta);
//    }
//    counter++;
    drawWindow(window);
}

void DrawableRacer::drawWindow(sf::RenderWindow &window) {
    window.draw(car);
    window.draw(fire);
}
