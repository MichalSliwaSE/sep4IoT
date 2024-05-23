#include "co2.h"
#include <time.h>
#include "pc_comm.h"

#define MAX 2000
#define MIN 500
#define NUMS_TO_GENERATE 200

static uint16_t values[NUMS_TO_GENERATE];  
static int curr_index, curr_val;

static int compare(const void* a, const void* b)
{
    uint16_t value_a = *((const uint16_t*)a);
    uint16_t value_b = *((const uint16_t*)b);

    if (value_a == value_b)
        return 0;
    else if (value_a < value_b)
        return -1;
    else
        return 1;
}

void co2_init() {
    srand(time(NULL));
    for (int i = 0; i < NUMS_TO_GENERATE; i++) {
        values[i] = (rand() % (MAX - MIN + 1)) + MIN;
    }
    qsort(values, NUMS_TO_GENERATE, sizeof(uint16_t), compare);  
    curr_index = NUMS_TO_GENERATE / 2;
    curr_val = values[curr_index];
}

static void change() {
    if (rand() % 2 == 0) curr_index ++;
    else curr_index --;

    curr_val = values[curr_index];
}

uint16_t co2_measure() {
    change();
    return curr_val;
}

