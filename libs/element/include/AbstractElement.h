#pragma once

struct Point {
    Point(float posX, float posY)
        : x(posX)
        , y(posY) {}
    float x;
    float y;
};

class AbstractElement {
public:
    AbstractElement(Point start, Point end, Point center)
        : _start({start.x, start.y})
        , _end({end.x, end.y})
        , _center({center.x, center.y}) {}
    virtual ~AbstractElement() = default;

    virtual bool intersect(Point playerTopLeft, Point playerTopRight, Point playerBottomLeft, Point playerBottomRight) = 0;

    virtual bool isElementDynamic() = 0;

    Point _start;
    Point _end;
    Point _center;
};
