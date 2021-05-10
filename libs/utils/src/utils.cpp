//
// Created by saptded on 15.04.2021.
//

#include "utils.hpp"
#include "drawableObject.hpp"
void abstractElement::createDrawable(){
    drObj->create(*this);
};

template<>
void abstractElement::draw<sf::RenderWindow>(sf::RenderWindow& target){
    if(isDynamic){
        drObj->draw(*this, target);
    } else {
        drObj->draw(target);
    }
};
