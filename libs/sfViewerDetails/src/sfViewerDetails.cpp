//
// Created by Kseny
//

#include "sfViewerDetails.hpp"
#include <SFML/Graphics/VertexArray.hpp>
#include <sfColor.hpp>

sfViewerDetails::sfViewerDetails()
        : viewWidth(float(1920)  /3)
        , viewHeight(float(1080) /3){
    bgImage.loadFromFile("/home/kseny/tp/JET/media/ogonkiDark.jpg");
    bg.setTexture(&bgImage);
    bg.setSize(sf::Vector2f(1920*1.2, 1080*1.2));
}

void sfViewerDetails::update(Racer& racer) {
    bg.setPosition(prevPos.x/4-1920/2, prevPos.y/4-1080/2);
    prevPos = sf::Vector2f(racer._center.x, racer._center.y);
    view.setCenter(prevPos);
}

void sfViewerDetails::display(sf::RenderWindow &window, int stage) {
    window.display();
    window.clear(colors.black);
    window.setView(window.getDefaultView());
//    bg.setPosition(0,0);
    window.draw(bg);
//    sf::RectangleShape rect;
//    rect.setSize(sf::Vector2f(10,10));
//    rect.setPosition(10,10);
//    rect.setFillColor(sf::Color::White);
//    window.draw(rect);
    view.setSize(viewWidth, viewHeight);
    window.setView(view);


}

