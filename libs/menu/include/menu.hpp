#pragma once

#include "buttons.hpp"
#include "menuInfo.hpp"
#include "presenter.hpp"
#include <customRequest.h>
#include <GameClient.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <memory.h>
#include <startServer.h>

class Menu{
    GameServer gameServer;
    std::unique_ptr<running_server_instance_t<http_server_t<ServerTraits>>> server;
    GameClient<CustomRequest> gameClient;
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