#pragma once

#include "presenter.hpp"
#include "buttons.hpp"
#include "menuInfo.hpp"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <memory.h>

class Menu{
public:
    explicit Menu(std::shared_ptr<RacerInfo> info);
    void run();
    void stopServer();
private:
    void runServer();

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

    std::shared_ptr<RacerInfo> info;
};