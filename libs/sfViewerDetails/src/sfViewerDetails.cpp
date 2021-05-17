//
// Created by Kseny
//

#include "sfViewerDetails.hpp"
#include <SFML/Graphics/VertexArray.hpp>
#include <sfColor.hpp>

//void sfViewerDetails::init(sf::RenderWindow &window) {
//    view = window.getDefaultView();
//    viewWidth = float(window.getSize().x);
//    viewWidth = float(window.getSize().y);
//    std::cout << "(" << viewWidth << "x" << viewHeight << ")";
//    view.setSize(viewWidth, viewHeight);
//    window.setView(view);
//}

sfViewerDetails::sfViewerDetails(sf::RenderWindow& window){
    viewWidth = float(window.getSize().x);
    viewWidth = float(window.getSize().y);
    std::cout << "(" << viewWidth << "x" << viewHeight << ")";
    view.setSize(viewWidth, viewHeight);
    window.setView(view);
}

void sfViewerDetails::update(Racer& racer) {
    view.setCenter(sf::Vector2f(racer._position.first.x, racer._position.first.y));
}

void sfViewerDetails::display(sf::RenderWindow &window, int stage){
    window.display();
    //
    window.clear(colors.getBg(stage));
    //view.zoom(0.5f);
//    window.setView(window.getDefaultView());
//    sf::RectangleShape rect;
//    rect.setSize(sf::Vector2f(10,10));
//    rect.setPosition(10,10);
//    rect.setFillColor(sf::Color::White);
//    window.draw(rect);
    view.setSize(viewWidth, viewHeight);
    window.setView(view);
}
