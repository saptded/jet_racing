#pragma once

#include <utility>

#include "AbstractElement.h"
#include "drawableObjects.hpp"
#include "mechanicalValues.hpp"

class Idle : public AbstractElement {
public:
    //    explicit Idle(Point start, Point end, Point center, std::shared_ptr<DrawableObject>& drObj)
    //        : AbstractElement(start, end, center, std::shared_ptr<DrawableObject>(nullptr)) {};
    explicit Idle(Point start, Point end, Point center)
        : AbstractElement(start, end, center){};
    ~Idle() override = default;

    bool intersect(Point playerTopLeft, Point playerTopRight, Point playerBottomLeft, Point playerBottomRight) override;
    void collision(Racer &racer, const RacerController &controller) override {};
    bool isElementDynamic() override;
};

class Line : public AbstractElement {
public:
    explicit Line(Point start, Point end, Point center, std::shared_ptr<DrawableObject> drObj)
        : AbstractElement(start, end, center, std::move(drObj)){};
    explicit Line(Point start, Point end, Point center)
        : AbstractElement(start, end, center){};
    ~Line() override = default;

    bool intersect(Point playerTopLeft, Point playerTopRight, Point playerBottomLeft, Point playerBottomRight) override;

    void collision(Racer &racer, const RacerController &controller) override;

    bool isElementDynamic() override;
};

class Arc : public AbstractElement {
public:
    explicit Arc(Point start, Point end, Point center, std::shared_ptr<DrawableObject> drObj)
        : AbstractElement(start, end, center, std::move(drObj)){};
    ~Arc() override = default;

    bool intersect(Point playerTopLeft, Point playerTopRight, Point playerBottomLeft, Point playerBottomRight) override;
    void collision(Racer &racer, const RacerController &controller) override {};
    bool isElementDynamic() override;
};

class Rectangle : public AbstractElement {
public:
    Rectangle(Point start, Point end, Point center)
        : AbstractElement(start, end, center) {}
    ~Rectangle() override = default;

    bool intersect(Point playerTopLeft, Point playerTopRight, Point playerBottomLeft, Point playerBottomRight) override;
    void collision(Racer &racer, const RacerController &controller) override {};
};

class Propeller : public Rectangle {
public:
    explicit Propeller(Point start, Point end, Point center, bool isDynamic)
        : Rectangle(start, end, center) {}
    ~Propeller() override = default;
    void collision(Racer &racer, const RacerController &controller) override {};

    bool isElementDynamic() override;

private:
    bool isDynamic;
};

class Accelerator : public Rectangle {
public:
    explicit Accelerator(Point start, Point end, Point center)
        : Rectangle(start, end, center) {}
    ~Accelerator() override = default;
    void collision(Racer &racer, const RacerController &controller) override {};

    bool isElementDynamic() override;
};

class Delayer : public Rectangle {
public:
    explicit Delayer(Point start, Point end, Point center)
        : Rectangle(start, end, center) {}
    ~Delayer() override = default;
    void collision(Racer &racer, const RacerController &controller) override {};

    bool isElementDynamic() override;
};

class Portal : public Rectangle {
public:
    explicit Portal(Point start, Point end, Point center)
        : Rectangle(start, end, center) {}
    ~Portal() override = default;
    void collision(Racer &racer, const RacerController &controller) override {};

    bool isElementDynamic() override;
};

class Finish : public Rectangle {
public:
    explicit Finish(Point start, Point end, Point center)
        : Rectangle(start, end, center) {}
    ~Finish() override = default;
    void collision(Racer &racer, const RacerController &controller) override {};

    bool isElementDynamic() override;
};
