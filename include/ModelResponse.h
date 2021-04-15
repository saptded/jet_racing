#ifndef FOR_PROJECT_MODELRESPONSE_H
#define FOR_PROJECT_MODELRESPONSE_H

#include <vector>
#include "Map.h"
#include "Racer.h"

enum Event {
    UpdateView,
    ChangeStage,
    Finish
};

struct ModelResponse {
    Event event;
    Map* map;
    Racer* racer;
    std::vector<Racer> enemies;
};

#endif //FOR_PROJECT_MODELRESPONSE_H
