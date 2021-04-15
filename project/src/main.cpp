#include "../include/AbstractElement.h"
#include "../include/Map.h"

#define FILENAME "../../map.txt"

int main() {
    Map map;
    map.parseFile(FILENAME);

    return 0;
}
