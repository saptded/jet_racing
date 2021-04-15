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
    AbstractElement() = default;
    virtual ~AbstractElement() = default;
    virtual Type getType() = 0;
 private:
    Type type{};
};


#endif  // PROJECT_INCLUDE_ABSTRACTELEMENT_H_
