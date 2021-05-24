#include "menu.hpp"

Menu::Menu(std::shared_ptr<MenuInfo> info): window(sf::VideoMode(1000, 800), "JetRacing") {
    if(info){
        // отобразить результаты в виде текста если они есть
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

std::shared_ptr<MenuInfo> Menu::run() {
    sf::Event event{};
    while (window.isOpen()) {
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
                    if(waitingInput && (event.text.unicode < 128) && (event.text.unicode > 40)){
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
        if(secondStep){
            // при получении инфы от сервера - добавить его
            //addRacer(/**/);
            // addText("RacerName----"); // отобразить его имя
            if(racers.size() >= 4){
                addText("ready?\tgood luck!", color.menuBright);
                //ready = true; - плохо
            }// ограничение 4 игрока
        }
        if(ready){
            return std::make_shared<MenuInfo>(racers);
        }
    }
    return nullptr;
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
            if(buttons.at(buttonIterator).getIsActive()){
                auto but = buttons.at(buttonIterator).getId();
                if(but == "start game") {
                    std::cout << "start game" << std::endl;
                    secondStep = true;
                    startGame();
                } else if (but == "join game") {
                    std::cout << "join game" << std::endl;
                    secondStep = true;
                    joinGame();
                } else if (but == "go") {
                    std::cout << "go" << std::endl;
//                    if(!buttons.at(buttonIterator).getIsActive()){
//                        ready = true;
//                    } // рабочий вариант такой
//                    if(racers.size() >= ){ // можно начать игру с (2, 3 наверное логично) игроками по кнопке
//                        // оставила 1 если вам пригодится так
//                        ready = true;
//                    }
                }
            }
            if(waitingInput && !myName.empty()){
                waitingInput = false;
                std::vector<sf::Text> newTexts;
                texts = newTexts;
                addText("you:\t" + myName, color.menuBright);
                addText("waiting others...", color.menuDark);
                buttons.at(buttonIterator).setActive();
                addRacer(/**/);
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
    // TODO
}

void Menu::joinGame() {
    changeStep();
    // TODO
}

void Menu::addRacer(/**/) {
//    RacerInfo racer;
//    racers.push_back(racer);
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

