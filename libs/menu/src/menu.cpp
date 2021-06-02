#include "menu.hpp"
#include <customDeserialization.h>
#include <deserialization.h>
#include <SFML/Window/Event.hpp>
#include <gameTimer.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

Menu::Menu(std::shared_ptr<MenuInfo>& info, servs _servers) :
        window(sf::VideoMode(1920, 1080), "JetRacing") {
    if (_servers.first != nullptr) {
        server = std::move(_servers.first);
        gameServer = std::move(_servers.second);
    }
    if (info != nullptr) {
        client = std::move(info->client);
        waitingOthersAfter = true;
    }
    sound.openFromFile("../media/vhoh.ogg");//загружаем файл для обратного отсчета
    bgImage.loadFromFile("../media/helmet_dark_right.jpg");
    bg.setTexture(&bgImage);
    float scale = 1080/(float)bgImage.getSize().y;
    bg.setSize(sf::Vector2f((float)bgImage.getSize().x/scale, 1080));
    bg.setPosition(0,0);
    soundVhoh();
}

std::unique_ptr<MenuInfo> Menu::run() {

    if (waitingOthersAfter) {
        makeResults();
    } else {
        makeStartButtons();
    }

    sf::Event event{};
    while (window.isOpen()) {
        if (waitingOthersAfter) {
            addNewEnded(); // получение информации от сервера и вывод результатов игроков
        }
        if (waitingOthersBefore) {
            addNewPlayers(); // получение от сервера информации о подключенных игроках.
            // Здесь изменить, чтобы нельзя было стартовать одному
        }
        if (ready) {
            buttons.clear();
            texts.clear();
            showCounter();
            client->sendFlag(true);
            window.close();
            return std::make_unique<MenuInfo>(myName, myId, client);
        }
        display();
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::KeyPressed:
                    handleInput(event.key.code, true);
                    break;
                case sf::Event::KeyReleased:
                    handleInput(event.key.code, false);
                    break;
                case sf::Event::TextEntered:
                    // побуквенный ввод и отображение
                    if(     waitingInput &&
                            ((event.text.unicode <= 122) && (event.text.unicode >= 97)) ||   // английские строчные буквы
                            ((event.text.unicode <= 57) && (event.text.unicode >= 48))       // цифры
                            ){
                        if (!buttons.at(buttonIterator).getIsActive()) {
                            buttons.at(buttonIterator).setActive();
                        }
                        myName.push_back(static_cast<char>(event.text.unicode));
                        texts.pop_back();
                        addText(myName + "_", color.menuBright); // курсор :)
                    }
                    break;
                case sf::Event::Closed:
                    window.close();
                    return nullptr;
            }
        }
    }
    return nullptr;
}

void Menu::makeResults() {
    font.loadFromFile("../media/lines.ttf");
    sf::Text gotIt("got\tit", font);
    addText("results", color.menuBright);
    gotIt.setCharacterSize(50);
    buttons = {
            AbstractButton(0, gotIt, window),
    };
    buttonIterator = 0;
    buttons.at(0).setPassive();
}

void Menu::handleInput(sf::Keyboard::Key key, bool isPressed) {
    if (key == sf::Keyboard::Up) {
        if (isPressed) {
            if (buttonIterator + 1 < buttons.size()) {
                buttons.at(buttonIterator).setPassive();
                ++buttonIterator;
                buttons.at(buttonIterator).setActive();
            }
        }
    } else if (key == sf::Keyboard::Down) {
        if (isPressed) {
            if (buttonIterator > 0) {
                buttons.at(buttonIterator).setPassive();
                --buttonIterator;
                buttons.at(buttonIterator).setActive();
            }
        }
    } else if (key == sf::Keyboard::Enter) {
        if (isPressed) {
            absButtonPressed();
        }
    }
}

void Menu::absButtonPressed() {
    if (waitingInput && !myName.empty()) {
        soundVhoh();
        client = std::make_shared<GameClient<CustomRequest>>(data);
        myId = client->join<CustomDeserialization>(myName);
        racers = 1;
        waitingOthersBefore = true;
        waitingInput = false;
        std::vector<sf::Text> newTexts;
        texts = newTexts;
        if (!server) {
            auto gotRacers = client->getUpdates<CustomDeserialization>();
            addText("creator:\t" + std::string(gotRacers.at(0).username), color.menuBright);
            racers++;
            for (int i = 1; i <= gotRacers.size() - 2; i++) {
                if (gotRacers.at(i).username != myName) {
                    addText("other:\t" + std::string(gotRacers.at(i).username), color.menuBright);
                    racers++;
                }
            }
        }
        addText("you:\t" + myName, color.menuBright);
        addText("waiting others...", color.menuDark);
        buttons.at(buttonIterator).setPassive();
    } else if (buttons.at(buttonIterator).getIsActive()) {
        auto but = buttons.at(buttonIterator).getId();
        if (but == "start game") {
            soundVhoh();
            startGame();
        } else if (but == "join game") {
            soundVhoh();
            joinGame();
        } else if (but == "go") {
            ready = true;
        } else if (but == "got\tit") {
            std::cout << "got it" << std::endl;
            texts.clear();
            stopServer();
            showMoved("come\tback\t!", 2.5f);
            window.close();
        }
    }
}

void Menu::makeStartButtons() {
    font.loadFromFile("../media/lines.ttf");
    sf::Text stGame("start game", font);
    sf::Text joinGame("join game", font);
    stGame.setCharacterSize(50);
    joinGame.setCharacterSize(50);
    buttons = {
            AbstractButton(0, joinGame, window),
            AbstractButton(1, stGame, window),
    };
    buttonIterator = 0;
    buttons.at(buttonIterator).setActive();
}

void Menu::changeStep() {
    sf::Text stGame("go", font);
    stGame.setCharacterSize(50);
    AbstractButton btn(0, stGame, window);
    btn.setPassive();
    std::vector<AbstractButton> newButtons = {btn};
    buttons = newButtons;
    buttonIterator = 0;

    texts.clear();
    addText("enter your name", color.menuDark);
    addText("", color.menuDark); // нужно чтобы в цикле с буквами всегла удалять последний текст, не проверяя
    waitingInput = true;
}

void Menu::addNewPlayers() {
    if (client->getFlag<CustomDeserialization>()) {
        ready = true;
    }
    auto upds = client->getUpdates<CustomDeserialization>();
    if/*((upds.size() > 1)&&*/(!buttons.at(buttonIterator).getIsActive()) {
        buttons.at(buttonIterator).setActive();
    }
    if (upds.size() > racers) {
        addText("other: " + upds.at(upds.size() - 1).username, color.menuBright);
        racers++;
    }
}

void Menu::addNewEnded() {
    auto upds = client->getUpdates<CustomDeserialization>();
    for (auto got: upds) {
        if (got.stage == -1) {
            bool alreadyShown = false;
            for (auto &old: endedRacers) {
                if (old == got.username) {
                    alreadyShown = true;
                    break;
                }
            }
            if (!alreadyShown) {
                std::string racer = got.username;
                racer += "\t:\t";
                racer += std::to_string((int)got.speed);
                addTextRightOriented(racer, color.menuBright);
                endedRacers.emplace_back(got.username);
                counterOfEnded++;
            }
        }
    }
    if (counterOfEnded == upds.size()) {
        waitingOthersAfter = false;
        buttons.at(buttonIterator).setActive();
        stopServer();
        client = nullptr;
    }
}

void Menu::startGame() {
    changeStep();
    runServer();
}

void Menu::joinGame() {
    changeStep();
}

void Menu::addText(std::string text_, sf::Color &color_) {
    sf::Text text(text_, font);
    text.setFillColor(color_);
    text.setCharacterSize(50);
    text.setOrigin(text.getLocalBounds().width / 2, -text.getLocalBounds().height / 2);
    float topMargin = (float) text.getLocalBounds().height*2;
    text.setPosition((float) window.getSize().x / 2, (float) texts.size() * topMargin + topMargin/2);
    texts.push_back(text);
}

void Menu::addTextRightOriented(std::string text_, sf::Color &color_) {
    sf::Text text(text_, font);
    text.setFillColor(color_);
    text.setCharacterSize(50);
    text.setOrigin(text.getLocalBounds().width, -text.getLocalBounds().height / 2);
    float topMargin = (float) window.getSize().y / 12;
    text.setPosition((float) window.getSize().x / 2 + texts.at(0).getLocalBounds().width / 2, (float) texts.size() * topMargin + topMargin);
    texts.push_back(text);
}

void Menu::printText() {
    for (auto &txt: texts) {
        window.draw(txt);
    }
}

void Menu::showButtons() {
    for (auto &but: buttons) {
        but.draw(window);
    }
}

void Menu::display() {
    window.clear();
    window.draw(bg);
    showButtons();
    printText();
    window.display();
    timer.timer();
}

void Menu::stopServer() {
    if (server) {
        server->stop(); // очищение http-server
        gameServer->close(); // очистка игрового сервера. не путать с low level http server
    }
    server = nullptr;
    gameServer = std::make_shared<GameServer>();
}

void Menu::runServer() {
    server = startServer(*gameServer, data);
}

void Menu::showCounter() {
    texts.clear();
    addText("a\t-\trotate\tleft", color.white);
    for(int i = 0; i < 10; i++){
        addText("", color.white);
    }
    addText("d\t-\trotate\tright", color.white);
    bgImage.loadFromFile("../media/ogonki.jpg");
    bg.setTexture(&bgImage);
    float scale = 1080/(float)bgImage.getSize().y;
    bg.setSize(sf::Vector2f(1920,1080));
    //bg.setScale(sf::Vector2f((float)bgImage.getSize().x*scale, (float)bgImage.getSize().y*scale));
    bg.setPosition(0,0);
    showMoved("3", 5.f);
    showMoved("2", 5.f);
    showMoved("1", 5.f);
}

void Menu::showMoved(std::string str, float speed){
    sf::Text text = sf::Text(str, font);
    text.setCharacterSize(80);
    float margin = window.getSize().y/4;
    text.setPosition(window.getSize().x/2, margin);
    sf::Color colorHere = sf::Color::White;
    GameTimer gameTimer;
    int height = window.getSize().y - text.getLocalBounds().height - 2*margin;
    int timeToStop = 20;
    int time = 0;
    float centralPos = (height+2*margin)/2 - text.getLocalBounds().height/2;
    sound.play();
    while(text.getPosition().y < (float)height+margin-4){
        text.move(0,speed);
        double sinus = sin((text.getPosition().y - margin)*M_PI/(height));
        colorHere.a = 225 * sinus;
        text.setCharacterSize(80 + 20 * sinus);
        text.setOrigin(text.getLocalBounds().width/2, 0);
        text.setFillColor(colorHere);
        if (text.getPosition().y > centralPos && time < timeToStop){
            text.move(0, -speed);
            time++;
        }
        window.clear();
        window.draw(bg);
        printText();
        window.draw(text);
        window.display();
        gameTimer.timer();
    }
}

void Menu::soundVhoh() {
    window.clear();
    window.draw(bg);
    window.display();
    hit.openFromFile("../media/hit.ogg");
    hit.play();
    GameTimer gameTimer;
    for(int i = 0; i < 60; i++){
        gameTimer.timer();
    }
}



