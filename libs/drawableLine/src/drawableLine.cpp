//
// Created by Kseny
//

#include "drawableLine.hpp"

//void DrawableLine::draw(abstractElement& element,  sf::RenderWindow& window){
//    window.draw(lines);
//}
void DrawableLine::create(abstractElement& line) {
    lines = sf::VertexArray(sf::Lines, 2);
    lines[0].position = sf::Vector2f(line.start.x, line.start.y);
    lines[0].color = sf::Color::Black;
    lines[1].position = sf::Vector2f(line.end.x, line.end.y);
    lines[1].color = sf::Color::Black;
}
//void DrawableLine::create(std::weak_ptr<abstractElement> element) {
//    lines = sf::VertexArray(sf::Lines, 2);
//    lines[0].position = sf::Vector2f(element.lock()->start.x, element.lock()->start.y);
//    lines[0].color = sf::Color::Blue;
//    lines[1].position = sf::Vector2f(element.lock()->end.x, element.lock()->end.y);
//    lines[1].color = sf::Color::Black;
//}
void DrawableLine::draw(sf::RenderWindow &window) {
    window.draw(lines);
}
