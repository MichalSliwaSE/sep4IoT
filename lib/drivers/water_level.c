#include "water_level.h"
#include <stdlib.h>
#include <time.h>

#define INITIAL_LEVEL 1000
#define MAX_CHANGE 50

static uint16_t current_level;

void water_level_init(void) {
    srand(time(NULL));
    current_level = INITIAL_LEVEL;
}

uint16_t water_level_measure(void) {
    int change = (rand() % (2 * MAX_CHANGE + 1)) - MAX_CHANGE;
    int new_level = current_level + change;

    if (new_level < 0) {
        new_level = 0;
    } else if (new_level > UINT16_MAX) {
        new_level = UINT16_MAX;
    }

    current_level = (uint16_t)new_level;
    return current_level;
}
