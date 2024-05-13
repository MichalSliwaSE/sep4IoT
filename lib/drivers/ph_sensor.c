#include "ph_sensor.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

// Simulated range for pH levels
#define MIN_PH 0
#define MAX_PH 14

// Function to generate a random pH value between MIN_PH and MAX_PH
static uint16_t generate_random_ph() {
    static uint16_t prev_ph = 7; // Start with a pH of 7
    uint16_t new_ph;

    // Generate a new pH value within the range, ensuring small increments
    do {
        // Calculate a new pH value with a maximum change of +/-1 from the previous value
        int change = rand() % 3 - 1; // -1, 0, or 1
        new_ph = prev_ph + change;

        // Ensure the new pH value is within the valid range
        if (new_ph < MIN_PH)
            new_ph = MIN_PH;
        else if (new_ph > MAX_PH)
            new_ph = MAX_PH;
    } while (new_ph == prev_ph); // Repeat if the new pH value is the same as the previous one

    prev_ph = new_ph; // Update the previous pH value for the next measurement
    return new_ph;
}

void ph_sensor_init() {
    srand(time(NULL));
}

uint16_t ph_sensor_measure() {
    return generate_random_ph();
}
