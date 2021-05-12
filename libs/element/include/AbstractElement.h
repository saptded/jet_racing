#ifndef PROJECT_INCLUDE_ABSTRACTELEMENT_H_
#define PROJECT_INCLUDE_ABSTRACTELEMENT_H_

#include <cstddef>

struct Point {
    Point(size_t posX, size_t posY) : x(posX), y(posY) {}
    size_t x;
    size_t y;
};

class AbstractElement {
 public:
    AbstractElement(Point start, Point end, Point center) : _start({start.x, start.y}),
                                                            _end({end.x, end.y}),
                                                            _center({center.x, center.y}) {}
    virtual ~AbstractElement() = default;

    virtual bool intersect(Point playerTopLeft,
                           Point playerTopRight,
                           Point playerBottomLeft,
                           Point playerBottomRight) = 0;

    virtual bool isElementDynamic() = 0;

    Point _start;
    Point _end;
    Point _center;

 private:
};

#endif  // PROJECT_INCLUDE_ABSTRACTELEMENT_H_
