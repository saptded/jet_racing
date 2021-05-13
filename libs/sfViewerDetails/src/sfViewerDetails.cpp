//
// Created by Kseny
//

#include "sfViewerDetails.hpp"
#include <SFML/Graphics/VertexArray.hpp>
#include <sfColor.hpp>

void sfViewerDetails::init(Racer& racer, sf::RenderWindow &window) {
    view = sf::View();
}
void sfViewerDetails::update(Racer& racer) {
    // view
    view.setCenter(sf::Vector2f(racer._position.first.x, racer._position.first.y));
    view.setSize(1200,1000);
    //view.setRotation(racer._rotation);
}
void sfViewerDetails::display(sf::RenderWindow &window, int stage){
    window.display();
    window.clear(colors.getBg(stage));
    //view.zoom(0.5f);
    //window.setView(view);
}
