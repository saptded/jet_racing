#include "libs/element/include/AbstractElement.h"
#include "libs/map/include/Map.h"

#define FILENAME "../../map.txt"

int main() {
    Map map;
    map.parseFile(FILENAME);

    return 0;
}
