#ifndef PH_SENSOR_H
#define PH_SENSOR_H

#include <stdint.h>

typedef struct {
  float ph_value;  // Stores the mocked PH value
} ph_sensor_t;

// Function prototypes for the mock PH sensor class
float ph_sensor_read(ph_sensor_t* sensor);

#endif /* PH_SENSOR_H */