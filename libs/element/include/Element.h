#ifndef PROJECT_INCLUDE_ELEMENT_H_
#define PROJECT_INCLUDE_ELEMENT_H_

#include "AbstractElement.h"

class Idle : public AbstractElement {
 public:
    explicit Idle(Point start, Point end, Point center) : AbstractElement(start, end, center) {}
    ~Idle() override = default;

    bool intersect(Point playerStart, Point playerEnd) override;
    bool isElementDynamic() override;
};


class Line : public AbstractElement {
 public:
    explicit Line(Point start, Point end, Point center) : AbstractElement(start, end, center) {}
    ~Line() override = default;

    bool intersect(Point playerStart, Point playerEnd) override;
    bool isElementDynamic() override;
};

class Arc : public AbstractElement {
 public:
    explicit Arc(Point start, Point end, Point center) : AbstractElement(start, end, center) {}
    ~Arc() override = default;

    bool intersect(Point playerStart, Point playerEnd) override;
    bool isElementDynamic() override;
};

class Rectangle : public AbstractElement {
 public:
    Rectangle(Point start, Point end, Point center) : AbstractElement(start, end, center) {}
    ~Rectangle() override = default;

    bool intersect(Point playerStart, Point playerEnd) override;
};

class Propeller : public Rectangle {
 public:
    explicit Propeller(Point start, Point end, Point center, bool isDynamic) : Rectangle(start, end, center) {}
    ~Propeller() override = default;

    bool isElementDynamic() override;

 private:
    bool isDynamic;
};

class Accelerator : public Rectangle {
 public:
    explicit Accelerator(Point start, Point end, Point center) : Rectangle(start, end, center) {}
    ~Accelerator() override = default;

    bool isElementDynamic() override;
};

class Delayer : public Rectangle {
 public:
    explicit Delayer(Point start, Point end, Point center) : Rectangle(start, end, center) {}
    ~Delayer() override = default;

    bool isElementDynamic() override;
};

class Portal : public Rectangle {
 public:
    explicit Portal(Point start, Point end, Point center) : Rectangle(start, end, center) {}
    ~Portal() override = default;

    bool isElementDynamic() override;
};

class Finish : public Rectangle {
 public:
    explicit Finish(Point start, Point end, Point center) : Rectangle(start, end, center) {}
    ~Finish() override = default;

    bool isElementDynamic() override;
};

#endif  // PROJECT_INCLUDE_ELEMENT_H_
