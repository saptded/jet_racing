//
// Created by Kseny
//

#include "sfViewerDetails.hpp"
#include <SFML/Graphics/VertexArray.hpp>
#include <sfColor.hpp>

sfViewerDetails::sfViewerDetails(sf::RenderWindow& window){  // не используется
//   viewWidth = float(window.getSize().x*1.2);
//  viewWidth = float(window.getSize().y*1.2);
    view.setSize(viewWidth, viewHeight);
    window.setView(view);
}

void sfViewerDetails::update(Racer& racer) {
    view.setCenter(sf::Vector2f(racer._center.x, racer._center.y));
}

void sfViewerDetails::display(sf::RenderWindow &window, int stage){
    window.display();
    window.clear(colors.getBg(stage));
//    window.setView(window.getDefaultView());
//    sf::RectangleShape rect;
//    rect.setSize(sf::Vector2f(10,10));
//    rect.setPosition(10,10);
//    rect.setFillColor(sf::Color::White);
//    window.draw(rect);
    view.setSize(viewWidth, viewHeight);
    window.setView(view);
}
