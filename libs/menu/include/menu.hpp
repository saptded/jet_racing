#pragma once

#include "presenter.hpp"
#include "buttons.hpp"
#include "menuInfo.hpp"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>

class Menu{
public:
    Menu(std::shared_ptr<RacerInfo>);
    std::shared_ptr<RacerInfo> run();
private:
    void display();
    void handleInput(sf::Keyboard::Key key, bool isPressed);

    std::vector<AbstractButton> buttons;
    int buttonIterator = 0;
    void showButtons();

    bool secondStep = false;
    void startGame();
    void joinGame();
    void changeStep();

    std::vector<sf::Text> texts;
    void addText(std::string text_, sf::Color& color);
    void printText();

    std::string myName;
    bool waitingInput = false;

    std::vector<RacerInfo> racers;
    void addRacer(/**/);

    bool ready = false;
    sf::RenderWindow window;
    sf::Font font;
    sfColor color;
};