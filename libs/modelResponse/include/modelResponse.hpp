//
// Created by saptded on 15.04.2021.
//

#ifndef JET_RACING_LIBS_MODELRESPONSE_INCLUDE_MODELRESPONSE_HPP_
#define JET_RACING_LIBS_MODELRESPONSE_INCLUDE_MODELRESPONSE_HPP_

#include "racer.hpp"

enum Event { UpdateVIew, ChangeStage, Finish };

struct ModelResponse {
    Event event;
//    Map *map
    Racer *racer;
    Racer enemies[];
};

#endif //JET_RACING_LIBS_MODELRESPONSE_INCLUDE_MODELRESPONSE_HPP_
