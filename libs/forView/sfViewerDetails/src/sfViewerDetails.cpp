//
// Created by Kseny
//

#include "sfViewerDetails.hpp"
#include <SFML/Graphics/VertexArray.hpp>
#include <complex>
#include <sfColor.hpp>

sfViewerDetails::sfViewerDetails(float _windowWidth, float _windowHeight)
        : windowWidth(_windowWidth), windowHeight(_windowHeight),
          viewWidth(_windowWidth / 3), viewHeight(_windowHeight / 3) {
    bgImage.loadFromFile("../media/ogonkiDark.jpg");
    bg.setTexture(&bgImage);
    bg.setSize(sf::Vector2f(windowWidth * 1.2, windowHeight * 1.2));
    font.loadFromFile("../media/lines.ttf");
    // текст
    text.setFont(font);
    text.setCharacterSize(30);
    text.setFillColor(colors.white);
    text.setPosition(10, 10);
}

void sfViewerDetails::update(Racer &racer) {
    bg.setPosition(prevPos.x / 4 - windowWidth / 2, prevPos.y / 4 - windowHeight / 2);
    prevPos = sf::Vector2f(racer._center.x, racer._center.y);
    view.setCenter(prevPos);
    counter++;
    if (counter >= 10) {
        std::string speedFloat = std::to_string(
                100 * std::pow((std::pow(racer._speed.speedX, 2) + std::pow(racer._speed.speedY, 2)), 0.5));
        std::string speed = "speed:\t";
        auto ch = speedFloat.begin();
        for (int i = 0; i < 6; i++) {
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
    window.draw(bg);
    //window.draw(text);

    view.setSize(viewWidth, viewHeight);
    window.setView(view);
}
