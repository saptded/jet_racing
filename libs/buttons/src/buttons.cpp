#include <buttons.hpp>

AbstractButton::AbstractButton(int num, sf::Text &_text, sf::RenderWindow &window) :
        id(_text.getString()) {
    float width = (float) window.getSize().x;
    float height = (float) window.getSize().y;
    Point start = {width / 4, (float) (6 - num * 2) * height / 8};
    Point finish = {3 * width / 4, (float) (6 - num * 2 + 1) * height / 8};
    drBtn = std::make_shared<DrawableButton>(start, finish, _text);
    isActive = false;
}

bool AbstractButton::getIsActive() {
    return isActive;
}

void AbstractButton::setActive() {
    isActive = true;
}

void AbstractButton::setPassive() {
    isActive = false;
}

void AbstractButton::draw(sf::RenderWindow &window) {
    drBtn->draw(isActive, window);
}

std::string AbstractButton::getId() {
    return id;
}
