#pragma once

#include "buttons.hpp"
#include "menuInfo.hpp"
#include "presenter.hpp"
#include <customRequest.h>
#include <GameClient.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <memory.h>
#include <GameServer.hpp>
#include <startServer.h>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/Music.hpp>
#include <gameTimer.hpp>

typedef std::pair<std::shared_ptr<running_server_instance_t<http_server_t<ServerTraits>>>, std::shared_ptr<GameServer>> servs;

class Menu {
public:
    Menu(std::shared_ptr<MenuInfo>& info, servs servers);
    std::unique_ptr<MenuInfo> run();
    servs getServer() {
        return std::make_pair(server, gameServer);
    };
private:
    // различные состояния меню
        // до самой игры
    void changeStep(); // вызывается после выбора start game или join
    bool waitingInput = false; // true, пока игрок вводит имя
    void startGame();
    void joinGame();
    bool waitingOthersBefore = false;
    void addNewPlayers(); // ожидание других игроков
    int racers = 1; // подсчет количества подключенных игроков до начала игры
    bool ready = false;
        // после
    void makeResults();
    int counterOfEnded = 0;
    bool waitingOthersAfter = false;
    std::vector<std::string> endedRacers;
    void addNewEnded();

    // необходимое для подключения сервера
    void runServer();
    void stopServer();
    std::shared_ptr<GameServer> gameServer = std::make_shared<GameServer>();
    std::shared_ptr<running_server_instance_t<http_server_t<ServerTraits>>> server = nullptr;
    std::shared_ptr<GameClient<CustomRequest>> client = nullptr;
    ConnectionData data = ConnectionData{8080, "localhost"};

    // подготовка возвращаемого значения
    std::string myName; // вводится пользователем
    uint8_t myId; // возвращается сервером
    std::shared_ptr<MenuInfo> info;

    // обработка ввода
    void handleInput(sf::Keyboard::Key key, bool isPressed);
    void absButtonPressed();

    // отображение на экране
    void makeStartButtons();
    void display();

    std::vector<AbstractButton> buttons;
    int buttonIterator = 0; // в один момент времени активна одна кнопка
    void showButtons();

    std::vector<sf::Text> texts;
    void addText(std::string text_, sf::Color &color);
    void addTextRightOriented(std::string text_, sf::Color &color);
    void printText();

    void soundVhoh();

    //обратный отсчет(попытка анимации)
    void showCounter();
    void showMoved(std::string str, float speed);

    sf::RenderWindow window;
    sf::Font font;
    sfColor color;

    sf::Music sound;
    sf::Music hit;

    sf::Texture bgImage;
    sf::RectangleShape bg;

    GameTimer timer;
};