#ifndef PROJECT_INCLUDE_ELEMENT_H_
#define PROJECT_INCLUDE_ELEMENT_H_

#include "AbstractElement.h"

class Line : public AbstractElement {
 public:
//    explicit Line(Point start, Point end) :
//        start({start.x, start.y}), end({end.x, end.y}), type(Type::line) {}
    explicit Line(Point start, Point end, Point center) : AbstractElement(start, end, center), type(Type::line) {}

    ~Line() override = default;

    Type getType() override;

 private:
//    Point start;
//    Point end;
    Type type;
};

class Arc : public AbstractElement {
 public:
    explicit Arc(Point start, Point end, Point center) : AbstractElement(start, end, center), type(Type::arc) {}

    ~Arc() override = default;

    Type getType() override;

 private:
//    Point start;
//    Point end;
//    Point center;
    Type type;
};

class Propeller : public AbstractElement {
 public:
//    explicit Propeller(Point start, Point end, Point center, bool isDynamic) :
//        start({start.x, start.y}), end({end.x, end.y}), center({center.x, center.y}), isDynamic(isDynamic), type(Type::propeller) {}

    explicit Propeller(Point start, Point end, Point center) : AbstractElement(start, end, center), type(Type::propeller) {}
    ~Propeller() override = default;

    Type getType() override;

 private:
//    Point start;
//    Point end;
//    Point center;
    bool isDynamic;
    Type type;
};

class Accelerator : public AbstractElement {
 public:
//    explicit Accelerator(Point start, Point end, Point center, bool isDynamic) :
//        start({start.x, start.y}), end({end.x, end.y}), center({center.x, center.y}), isDynamic(isDynamic), type(Type::accelerator) {}

    explicit Accelerator(Point start, Point end, Point center) : AbstractElement(start, end, center), type(Type::accelerator) {}
    ~Accelerator() override = default;

    Type getType() override;

 private:
//    Point start;
//    Point end;
//    Point center;
    bool isDynamic;
    Type type;
};

class Delayer : public AbstractElement {
 public:
//    explicit Delayer(Point start, Point end, Point center, bool isDynamic) :
//        start({start.x, start.y}), end({end.x, end.y}), center({center.x, center.y}), isDynamic(isDynamic), type(Type::delayer) {}

    explicit Delayer(Point start, Point end, Point center) : AbstractElement(start, end, center), type(Type::delayer) {}
    ~Delayer() override = default;

    Type getType() override;

 private:
//    Point start;
//    Point end;
//    Point center;
    bool isDynamic;
    Type type;
};

class Portal : public AbstractElement {
 public:
//    explicit Portal(Point start, Point end, Point center, bool isDynamic) :
//        start({start.x, start.y}), end({end.x, end.y}), center({center.x, center.y}), isDynamic(isDynamic), type(Type::portal) {}

    explicit Portal(Point start, Point end, Point center) : AbstractElement(start, end, center), type(Type::portal) {}
    ~Portal() override = default;

    Type getType() override;

 private:
//    Point start;
//    Point end;
//    Point center;
    bool isDynamic;
    Type type;
};

class Finish : public AbstractElement {
 public:
//    explicit Finish(Point start, Point end, Point center, bool isDynamic) :
//        start({start.x, start.y}), end({end.x, end.y}), center({center.x, center.y}), isDynamic(isDynamic), type(Type::finish) {}

    explicit Finish(Point start, Point end, Point center) : AbstractElement(start, end, center), type(Type::finish) {}
    ~Finish() override = default;

    Type getType() override;

 private:
//    Point start;
//    Point end;
//    Point center;
    bool isDynamic;
    Type type;
};

#endif  // PROJECT_INCLUDE_ELEMENT_H_
