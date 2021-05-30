#include "gameTimer.hpp"

void GameTimer::timer(float want_fps) {
    sf::Int32 frameDuration = looper.getElapsedTime().asMilliseconds();
    sf::Int32 timeToSleep = int(1000.f / want_fps) - frameDuration;
    if (timeToSleep > 0) {
        sf::sleep(sf::milliseconds(timeToSleep));
    }
    looper.restart();
}
