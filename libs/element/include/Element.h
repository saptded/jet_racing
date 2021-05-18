#pragma once

#include <vector>
#include <drawableObjects.hpp>

#include "AbstractElement.h"

class Line : public AbstractElement {
public:
    explicit Line(Point start, Point end, Point center)
        : AbstractElement(start, end, center) {
        _drObj = std::make_shared<DrawableLine>(start, end, center);
    };
    ~Line() override = default;

//    void collision(Racer &racer, const RacerController &controller) override;

    bool intersect(Point &playerTopLeft, Point &playerTopRight, Point &playerBottomLeft, Point &playerBottomRight) override;

    bool isElementDynamic() override;
};

class Arc : public AbstractElement {
public:
    explicit Arc(Point start, Point end, Point center)
        : AbstractElement(start, end, center){
        _drObj = std::make_shared<DrawableArc>(start, end, center);
    };
    ~Arc() override = default;

    bool intersect(Point &playerTopLeft, Point &playerTopRight, Point &playerBottomLeft, Point &playerBottomRight) override;
    std::vector<Line> getApproximatedArc(int iteration, float radius, const Arc &arc);
    bool isElementDynamic() override;
};

class Rectangle : public AbstractElement {
public:
    Rectangle(Point start, Point end, Point center)
        : AbstractElement(start, end, center) {}
    ~Rectangle() override = default;


    bool intersect(Point &playerTopLeft, Point &playerTopRight, Point &playerBottomLeft, Point &playerBottomRight) override;
    void collision(Racer &racer, const RacerController &controller) override {};
};

class Propeller : public Rectangle {
public:
    explicit Propeller(Point start, Point end, Point center, bool isDynamic)
        : Rectangle(start, end, center), isDynamic(false) {
        _drObj = std::make_shared<DrawablePropeller>(start, end, center);
    }

    ~Propeller() override = default;
    void collision(Racer &racer, const RacerController &controller) override {};

    bool isElementDynamic() override;

private:
    bool isDynamic;
};

class Accelerator : public Rectangle {
public:
    explicit Accelerator(Point start, Point end, Point center)
        : Rectangle(start, end, center) {
        _drObj = std::make_shared<DrawableAccelerator>(start, end, center);
    }
    ~Accelerator() override = default;
    void collision(Racer &racer, const RacerController &controller) override {};

    bool isElementDynamic() override;
};

class Delayer : public Rectangle {
public:
    explicit Delayer(Point start, Point end, Point center)
        : Rectangle(start, end, center) {
        _drObj = std::make_shared<DrawableDelayer>(start, end, center);
    }
    ~Delayer() override = default;
    void collision(Racer &racer, const RacerController &controller) override {};

    bool isElementDynamic() override;
};

class Portal : public Rectangle {
public:
    explicit Portal(Point start, Point end, Point center)
        : Rectangle(start, end, center) {
        _drObj = std::make_shared<DrawablePortal>(start, end, center);
    }
    ~Portal() override = default;
    void collision(Racer &racer, const RacerController &controller) override {};

    bool isElementDynamic() override;
};

class Finish : public Rectangle {
public:
    explicit Finish(Point start, Point end, Point center)
        : Rectangle(start, end, center) {
        _drObj = std::make_shared<DrawableFinish>(start, end, center);
    }
    ~Finish() override = default;
    void collision(Racer &racer, const RacerController &controller) override {};

    bool isElementDynamic() override;
};
