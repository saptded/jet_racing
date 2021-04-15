#ifndef PROJECT_INCLUDE_ELEMENT_H_
#define PROJECT_INCLUDE_ELEMENT_H_

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

class Element {
 public:
    Element() = default;
    virtual ~Element() = default;
    virtual Type getType() = 0;
 private:
    Type type{};
};

class Line : public Element {
 public:
    explicit Line(Point start, Point end) : start({start.x, start.y}), end({end.x, end.y}), type(Type::line) {}
    ~Line() override = default;

    Type getType() override;

 private:
    Point start;
    Point end;
    Type type;
};

class Arc : public Element {
 public:
    explicit Arc(Point start, Point end, Point center) :
    start({start.x, start.y}), end({end.x, end.y}), center({center.x, center.y}), type(Type::arc) {}

    ~Arc() override = default;

    Type getType() override;

 private:
    Point start;
    Point end;
    Point center;
    Type type;
};

class Propeller : public Element {
 public:
    explicit Propeller(Point start, Point end, Point center) :
    start({start.x, start.y}), end({end.x, end.y}), center({center.x, center.y}), type(Type::propeller) {}

    ~Propeller() override = default;

    Type getType() override;

 private:
    Point start;
    Point end;
    Point center;
    Type type;
};

class Accelerator : public Element {
 public:
    explicit Accelerator(Point start, Point end, Point center) :
        start({start.x, start.y}), end({end.x, end.y}), center({center.x, center.y}), type(Type::accelerator) {}

    ~Accelerator() override = default;

    Type getType() override;

 private:
    Point start;
    Point end;
    Point center;
    Type type;
};

class Delayer : public Element {
 public:
    explicit Delayer(Point start, Point end, Point center) :
        start({start.x, start.y}), end({end.x, end.y}), center({center.x, center.y}), type(Type::delayer) {}

    ~Delayer() override = default;

    Type getType() override;

 private:
    Point start;
    Point end;
    Point center;
    Type type;
};

class Portal : public Element {
 public:
    explicit Portal(Point start, Point end, Point center) :
        start({start.x, start.y}), end({end.x, end.y}), center({center.x, center.y}), type(Type::portal) {}

    ~Portal() override = default;

    Type getType() override;

 private:
    Point start;
    Point end;
    Point center;
    Type type;
};

class Finish : public Element {
 public:
    explicit Finish(Point start, Point end, Point center) :
        start({start.x, start.y}), end({end.x, end.y}), center({center.x, center.y}), type(Type::finish) {}

    ~Finish() override = default;

    Type getType() override;

 private:
    Point start;
    Point end;
    Point center;
    Type type;
};


#endif  // PROJECT_INCLUDE_ELEMENT_H_
