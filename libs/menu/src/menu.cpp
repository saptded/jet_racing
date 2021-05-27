#include "menu.hpp"
#include <customDeserialization.h>
#include <deserialization.h>
#include <serialization.h>
#include <stdint.h>


Menu::Menu(std::shared_ptr<MenuInfo> info): window(sf::VideoMode(1000, 800), "JetRacing") {
    if(info != nullptr){
        // отобразить результаты в виде текста если они есть
        addText("results", color.menuDark);
        auto racerNames = client->getUpdates<CustomDeserialization>();
        for(auto it: info->results) {
            std::string racer = racerNames.at(it.first).username;
            racer += "\t:\t";
            racer += std::to_string(it.second);
            addText(racer, color.menuBright);
        }
    }
    sf::Text stGame ("start game", font);
    sf::Text joinGame ("join game", font);
    if(!font.loadFromFile("../media/lines.ttf")){
        //
    } else {
        stGame.setFont(font);
        stGame.setCharacterSize(50);
        joinGame.setFont(font);
        joinGame.setCharacterSize(50);
    }
    buttons = {
            AbstractButton(0, stGame, window),
            AbstractButton(1, joinGame, window),
    };
}

std::unique_ptr<MenuInfo> Menu::run() {
    sf::Event event{};
    while (window.isOpen()) {
        if(waitingOthers){
            if(client->getFlag<CustomDeserialization>()) return std::make_unique<MenuInfo>(myName, myId, client);
            auto upds = client->getUpdates<CustomDeserialization>();
            if/*((upds.size() > 1)&&*/(!buttons.at(buttonIterator).getIsActive()){
                buttons.at(buttonIterator).setActive();
            };
            if(upds.size() > racers){
                addText("other: " + upds.at(upds.size()-1).username, color.menuBright);
                racers++;
            }
        }
        if(ready){
            client->sendFlag(true);
            return std::make_unique<MenuInfo>(myName, myId, client);
        }
        display();
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::KeyPressed:
                    handleInput(event.key.code, true);
                    break;
                case sf::Event::KeyReleased:
                    handleInput(event.key.code, false);
                    break;
                case sf::Event::TextEntered:
                    if(waitingInput && (event.text.unicode <= 122) && (event.text.unicode >= 97)){
                        if(!buttons.at(buttonIterator).getIsActive()){
                            buttons.at(buttonIterator).setActive();
                        }
                        myName.push_back(static_cast<char>(event.text.unicode));
                        texts.pop_back();
                        addText(myName+ "_", color.menuBright);
                    }
                    break;
                case sf::Event::Closed:
                    window.close();
                    return nullptr;
            }
        }
    }
}

void Menu::handleInput(sf::Keyboard::Key key, bool isPressed){
    if (key == sf::Keyboard::Up) {
        if(isPressed){
            if(buttonIterator > 0){
                buttons.at(buttonIterator).setPassive();
                --buttonIterator;
                buttons.at(buttonIterator).setActive();
            }
        }
    } else if (key == sf::Keyboard::Down) {
        if(isPressed){
                if(buttonIterator+1 < buttons.size()){
                    buttons.at(buttonIterator).setPassive();
                    ++buttonIterator;
                    buttons.at(buttonIterator).setActive();
                }
        }
    } else if (key == sf::Keyboard::Enter){
        if(isPressed){
            if(waitingInput && !myName.empty()){
                client = std::make_shared<GameClient<CustomRequest>>(data);
                myId = client->join<CustomDeserialization>(myName);
                waitingOthers = true;
                waitingInput = false;
                std::vector<sf::Text> newTexts;
                texts = newTexts;
                if(!server){
                    auto gotRacers = client->getUpdates<CustomDeserialization>();
                    addText("creator:\t" + std::string(gotRacers.at(0).username), color.menuBright);
                    for(int i = 1; i <= gotRacers.size() - 2 ; i++){
                        addText("other:\t" + std::string(gotRacers.at(i).username), color.menuBright);
                    }
                    racers++;
                }
                addText("you:\t" + myName, color.menuBright);
                addText("waiting others...", color.menuDark);
                buttons.at(buttonIterator).setPassive();
            } else if(buttons.at(buttonIterator).getIsActive()){
                auto but = buttons.at(buttonIterator).getId();
                if(but == "start game") {
                    std::cout << "start game" << std::endl;
                    startGame();
                } else if (but == "join game") {
                    std::cout << "join game" << std::endl;
                    joinGame();
                } else if (but == "go") {
                    std::cout << "go" << std::endl;
                    ready = true; // по кнопке go завершается метод run
                }
            }
        }
    }
}

void Menu::changeStep(){
    sf::Text stGame ("go", font);
    stGame.setCharacterSize(50);
    AbstractButton btn(0, stGame, window);
    btn.setPassive();
    std::vector<AbstractButton> newButtons = { btn };
    buttons = newButtons;
    buttonIterator = 0;

    // если в texts уже будут лежать результаты, надо обнулить ее. Можно наверно элегантнее
    std::vector<sf::Text> newTexts;
    texts = newTexts;
    addText("enter your name", color.menuDark);
    addText("_", color.menuBright);
    waitingInput = true;
}

void Menu::startGame() {
    changeStep();
    runServer();
}

void Menu::joinGame() {
    changeStep();
}


void Menu::addText(std::string text_, sf::Color& color_) {
    sf::Text text (text_, font);
    text.setFillColor(color_);
    text.setCharacterSize(50);
    text.setOrigin(text.getLocalBounds().width/2, -text.getLocalBounds().height/2);
    float topMargin = (float)window.getSize().y/12;
    text.setPosition((float)window.getSize().x/2, (float)texts.size()*topMargin + topMargin);
    texts.push_back(text);
}

void Menu::printText() {
    for(auto &txt: texts){
        window.draw(txt);
    }
}

void Menu::showButtons() {
    for(auto &but: buttons){
        but.draw(window);
    }
}

void Menu::display() {
    window.clear();
    showButtons();
    printText();
    window.display();
}

void Menu::stopServer() {
    if(server){
        server->stop(); // очищение http-server
        gameServer.close(); // очистка игрового сервера. не путать с low level http server
    }
}

void Menu::runServer() {
    server = startServer(gameServer, data);
}

