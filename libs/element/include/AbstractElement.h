#ifndef PROJECT_INCLUDE_ABSTRACTELEMENT_H_
#define PROJECT_INCLUDE_ABSTRACTELEMENT_H_

//#include <cstddef>
#include <memory>
#include "SFML/Graphics/RenderWindow.hpp"
#include "mechanicalValues.hpp"
//#include "drawableObject.hpp"

class DrawableObject;

//struct Point {
//    Point(float posX, float posY) : x(posX), y(posY) {}
//    float x;
//    float y;
//};

class AbstractElement {
 public:
    AbstractElement(Point start, Point end, Point center, std::shared_ptr<DrawableObject> drObj) : _start({start.x, start.y}),
                                                            _end({end.x, end.y}),
                                                            _center({center.x, center.y}),
                                                            _drObj(drObj) {};
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
    void createDrawable(int stage);
    void draw(sf::RenderWindow &window);

 private:
};

#endif  // PROJECT_INCLUDE_ABSTRACTELEMENT_H_
