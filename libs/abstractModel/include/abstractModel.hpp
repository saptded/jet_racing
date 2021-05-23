#pragma once

#include "mechanicalValues.hpp"
#include "observer.hpp"

class AbstractModel : public Observable {
public:
    virtual void updateModel(Command &rotation){};

private:
};
