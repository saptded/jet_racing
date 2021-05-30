#include <buttons.hpp>
#include "sfColor.hpp"

AbstractButton::AbstractButton(int num, sf::Text& _text, sf::RenderWindow& window):
text(_text), id(_text.getString()) {
    rect.setFillColor(sf::Color::Transparent);
    float width = (float)window.getSize().x;
    float height = (float)window.getSize().y;
    rect.setSize(sf::Vector2f (width/2, height/8));
    rect.setPosition(width/4, (6 - num*2)*height/8);

    text.setOrigin(text.getLocalBounds().width/2, -text.getLocalBounds().height/2);
    text.setPosition(width/2, (6 - num*2)*height/8);
    num == 0 ? isActive = true : isActive = false;
    if(isActive){
        rect.setOutlineThickness(5);
        rect.setOutlineColor(color.white);
        text.setFillColor(color.white);
    } else {
        rect.setOutlineThickness(2);
        rect.setOutlineColor(color.menuDark);
        text.setFillColor(color.menuDark);
    }
}

bool AbstractButton::getIsActive() {
    return isActive;
}

void AbstractButton::setActive() {
    rect.setOutlineThickness(5);
    rect.setOutlineColor(color.menuBright);
    text.setFillColor(color.menuBright);
    isActive = true;
}

void AbstractButton::setPassive() {
    rect.setOutlineThickness(2);
    rect.setOutlineColor(color.menuDark);
    text.setFillColor(color.menuDark);
    isActive = false;
}

void AbstractButton::draw(sf::RenderWindow& window) {
    window.draw(rect);
    window.draw(text);
}

std::string AbstractButton::getId() {
    return id;
}

