#pragma once

#include "presenter.hpp"
#include "buttons.hpp"
#include "menuInfo.hpp"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>

class Menu{
public:
    Menu(std::shared_ptr<MenuInfo>);
    std::shared_ptr<MenuInfo> run();
private:
    void display();
    void handleInput(sf::Keyboard::Key key, bool isPressed);

    std::vector<AbstractButton> buttons;
    int buttonIterator;
    void showButtons();

    bool secondStep = false;
    void startGame();
    void joinGame();
    void changeStep();

    std::vector<sf::Text> texts;
    void addText(std::string racerName);
    void printText();

    std::vector<RacerInfo> racers;
    void addRacer(/**/);

    bool ready = false;
    sf::RenderWindow window;
    sf::Font font;
    sfColor color;
};