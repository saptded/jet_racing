#ifndef PROJECT_INCLUDE_ABSTRACTELEMENT_H_
#define PROJECT_INCLUDE_ABSTRACTELEMENT_H_

#include <cstddef>

typedef struct Point {
    Point(size_t p_x, size_t p_y) : x(p_x), y(p_y) {}
    size_t x;
    size_t y;
} Point;

class AbstractElement {
 public:
    AbstractElement(Point start, Point end, Point center) : _start({start.x, start.y}),
                                                            _end({end.x, end.y}),
                                                            _center({center.x, center.y}) {}
    virtual ~AbstractElement() = default;

    virtual bool intersect(Point playerA, Point playerB, Point playerC, Point playerD) = 0;
    virtual bool isElementDynamic() = 0;

    Point _start;
    Point _end;
    Point _center;

 private:
};

#endif  // PROJECT_INCLUDE_ABSTRACTELEMENT_H_
