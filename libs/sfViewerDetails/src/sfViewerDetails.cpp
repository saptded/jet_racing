//
// Created by Kseny
//

#include "sfViewerDetails.hpp"
#include <SFML/Graphics/VertexArray.hpp>
#include <sfColor.hpp>
#include <complex>

sfViewerDetails::sfViewerDetails()
        : viewWidth(float(1920)  /3)
        , viewHeight(float(1080) /3){
    bgImage.loadFromFile("../media/ogonkiDark.jpg");
    bg.setTexture(&bgImage);
    bg.setSize(sf::Vector2f(1920*1.2, 1080*1.2));
    font.loadFromFile("../media/lines.ttf");
    text.setFont(font);
    text.setCharacterSize(30);
    text.setFillColor(colors.getCar(0));
    text.setPosition(20,20);
}

void sfViewerDetails::update(Racer& racer) {
    bg.setPosition(prevPos.x/4-1920/2, prevPos.y/4-1080/2);
    prevPos = sf::Vector2f(racer._center.x, racer._center.y);
    view.setCenter(prevPos);
    counter++;
    if(counter >= 10){
        std::string speedFloat = std::to_string( 100 * std::pow( (std::pow(racer._speed.speedX,2) + std::pow(racer._speed.speedY,2)), 0.5) );
        std::string speed = "speed:\t";
        auto ch = speedFloat.begin();
        for(int i = 0; i < 6; i++){
            speed += *ch;
            ch++;
        }
        text.setString(speed);
        counter = 0;
    }
}

void sfViewerDetails::display(sf::RenderWindow &window, int stage) {
    window.display();
    window.clear(colors.black);
    window.setView(window.getDefaultView());
//    bg.setPosition(0,0);
    window.draw(bg);
//    sf::RectangleShape rect;
    window.draw(text);
//    rect.setSize(sf::Vector2f(10,10));
//    rect.setPosition(10,10);
//    rect.setFillColor(sf::Color::White);
//    window.draw(rect);
    view.setSize(viewWidth, viewHeight);
    window.setView(view);


}

