//
// Created by Kseny
//

#include "drawableLine.hpp"

void DrawableLine::create(abstractElement& line, int stage) {
    lines = sf::VertexArray(sf::Lines, 2);
    lines[0].position = sf::Vector2f(line.start.x, line.start.y);
    lines[0].color = sf::Color::Magenta;
    lines[1].position = sf::Vector2f(line.end.x, line.end.y);
    lines[1].color = sf::Color::Magenta;
}

void DrawableLine::draw(sf::RenderWindow &window) {
    window.draw(lines);
}
