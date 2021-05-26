#pragma once

#include "buttons.hpp"
#include "menuInfo.hpp"
#include "presenter.hpp"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <memory.h>

class AbstractMenu{
public:
    void show();
protected:

};

class Menu{
public:
    explicit Menu(std::shared_ptr<MenuInfo> info);
    std::unique_ptr<MenuInfo> run();
private:
    int racers = 1;

    void display();
    void handleInput(sf::Keyboard::Key key, bool isPressed);

    std::vector<AbstractButton> buttons;
    int buttonIterator = 0;
    void showButtons();

    void startGame();
    void joinGame();
    void changeStep();

    std::vector<sf::Text> texts;
    void addText(std::string text_, sf::Color& color);
    void printText();

    std::string myName;
    bool waitingInput = false;

    bool ready = false;
    sf::RenderWindow window;
    sf::Font font;
    sfColor color;

    std::shared_ptr<MenuInfo> info;
};