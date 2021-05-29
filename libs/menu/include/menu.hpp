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

class AbstractMenu{
public:
    void show();
protected:

};

class Menu{
public:
    explicit Menu(std::shared_ptr<MenuInfo> info);
    std::unique_ptr<MenuInfo> run();
    void stopServer();
private:
    void runServer();
    GameServer gameServer;
    std::unique_ptr<running_server_instance_t<http_server_t<ServerTraits>>> server = nullptr;
    std::shared_ptr<GameClient<CustomRequest>> client = nullptr;
    ConnectionData data = ConnectionData{2021, "localhost"};
    bool waitingOthersBefore = false;
    bool waitingOthersAfter = false;
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
    int myId;
};