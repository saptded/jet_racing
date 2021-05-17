#pragma once
#include <memory>
#include <utility>
#include "SFML/Graphics/RenderWindow.hpp"
#include "mechanicalValues.hpp"

class DrawableObject;

class AbstractElement {
 public:
    AbstractElement(Point start, Point end, Point center) : _start({start.x, start.y}),
        _end({end.x, end.y}),
        _center({center.x, center.y}){};
    virtual ~AbstractElement() = default;

    virtual bool intersect(Point playerTopLeft,
                           Point playerTopRight,
                           Point playerBottomLeft,
                           Point playerBottomRight) = 0;

    virtual bool isElementDynamic() = 0;

    Point _start;
    Point _end;
    Point _center;

    std::shared_ptr<DrawableObject> _drObj;
    void draw(sf::RenderWindow &window);

 private:
};
