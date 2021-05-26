#pragma once
#include <string>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

#include "sfColor.hpp"

class AbstractButton{
public:
    AbstractButton() = delete;
    AbstractButton(int num, sf::Text& _text, sf::RenderWindow& window);
    std::string getId();
    bool getIsActive();
    void setActive();
    void setPassive();
    void draw(sf::RenderWindow& window);
private:
    bool isActive;
    sf::Text text;
    //sf::Font   font;
    sf::RectangleShape rect;
    std::string id;
    sfColor color;
};