#include "Element.h"

Type Line::getType() {
    return Type::line;
}

Type Arc::getType() {
    return Type::arc;
}

Type Propeller::getType() {
    return Type::propeller;
}

Type Accelerator::getType() {
    return Type::accelerator;
}

Type Delayer::getType() {
    return Type::delayer;
}

Type Finish::getType() {
    return Type::finish;
}

Type Portal::getType() {
    return Type::portal;
}
