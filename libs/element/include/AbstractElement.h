#pragma once

#include "SFML/Graphics/RenderWindow.hpp"
#include "interfaceCollisional.hpp"
#include "mechanicalValues.hpp"
#include "racer.hpp"
#include "racerController.hpp"
#include <memory>
#include <utility>

class DrawableObject;

class AbstractElement : Collisional {
public:
    AbstractElement(Point start, Point end, Point center)
        : _start({start.x, start.y})
        , _end({end.x, end.y})
        , _center({center.x, center.y}){};
    virtual ~AbstractElement() = default;

    virtual bool intersect(Point &playerTopLeft, Point &playerTopRight, Point &playerBottomLeft, Point &playerBottomRight, Point &playerCenter) = 0;
    void collision(Racer &racer, RacerController &controller, Command command) override = 0;
    virtual bool isElementDynamic() = 0;

    Point _start;
    Point _end;
    Point _center;

    std::shared_ptr<DrawableObject> _drObj;
    void draw(sf::RenderWindow &window);
    void init(int stage);

private:
};
