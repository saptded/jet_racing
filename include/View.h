#ifndef FOR_PROJECT_VIEW_H
#define FOR_PROJECT_VIEW_H

#include "Observer.h"
#include "Map.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

struct racerView {
    sf::RectangleShape car;
    sf::RectangleShape gas;
};

class View : Observer {
public:
    void HandleEvent(ModelResponse) override;
    View() = delete;
    View(sf::Window*);
    View(const View&) = delete;
    View(View&&);
    ~View();
private:
    //несколько полей связанных с SFML
    sf::Window* window;
    sf::View view;          //камера
    std::vector<sf::Shape> staticMap; // для неподвижной карты
    std::vector<sf::Shape> dynamicMap; // для движущихся объектов карты
    std::vector<racerView> cars; // для машин

    short stage;

    void update();
    void renderMap();
    void renderRacers();

    void finish();
};

#endif //FOR_PROJECT_VIEW_H
