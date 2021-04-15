#include "iostream"
#include "View.h"

#include <SFML/Graphics/RenderWindow.hpp>

int main() {
    sf::Window window;
    View view = View(&window);
    ModelResponse modelResponse;
    view.HandleEvent(modelResponse);
    return 0;
}
