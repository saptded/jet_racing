#ifndef FOR_PROJECT_OBSERVER_H
#define FOR_PROJECT_OBSERVER_H

#include "ModelResponse.h"

class Observer {
public:
    virtual void HandleEvent(ModelResponse);
};

#endif //FOR_PROJECT_OBSERVER_H
