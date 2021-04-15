#include "Observer.h"
#include <iostream>

void Observer::HandleEvent(ModelResponse){
    std::cout << "HandleEvent в Observer" << std::endl;
};

