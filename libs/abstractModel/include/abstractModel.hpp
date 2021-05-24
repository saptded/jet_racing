#pragma once

#include "mechanicalValues.hpp"
#include "observer.hpp"
#include "menuInfo.hpp"

class AbstractModel : public Observable {
public:
    virtual std::shared_ptr<RacerInfo> updateModel(Command &rotation) = 0;

private:
};
