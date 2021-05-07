#ifndef PROJECT_INCLUDE_ABSTRACTELEMENT_H_
#define PROJECT_INCLUDE_ABSTRACTELEMENT_H_

#include <cstddef>

enum Type {
    line,
    arc,
    propeller,
    accelerator,
    delayer,
    portal,
    finish
};

typedef struct Point {
    size_t x;
    size_t y;
} Point;

class AbstractElement {
 public:
    AbstractElement(Point start, Point end, Point center) : _start({start.x, start.y}), _end({end.x, end.y}), _center({center.x, center.y}) {}
    virtual ~AbstractElement() = default;
    virtual Type getType() = 0;

    Point _start;
    Point _end;
    Point _center;

 private:
    Type type{};
};

#endif  // PROJECT_INCLUDE_ABSTRACTELEMENT_H_
