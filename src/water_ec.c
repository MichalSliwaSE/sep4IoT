#include "water_ec.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 5000
#define NUMS_TO_GENERATE 50


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

void water_ec_init() {
    srand(time(NULL));
    for (int i = 0; i < NUMS_TO_GENERATE; i++) {
        values[i] = rand() % MAX;
    }
    qsort( values, NUMS_TO_GENERATE, sizeof(uint16_t), compare );
    curr_index = NUMS_TO_GENERATE / 2;
    curr_val = values[curr_index];
}

static void change() {
    if (rand() % 2 == 0) curr_index ++;
    else curr_index --;

    curr_val = values[curr_index];
}

uint16_t water_ec_measure() {
    change();
    return curr_val;
}