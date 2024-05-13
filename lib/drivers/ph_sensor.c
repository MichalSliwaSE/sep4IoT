#include <stdlib.h>
#include "ph_sensor.h"

float ph_sensor_read(ph_sensor_t* sensor) {
  // Simulate reading a random PH value between 0 and 14
  return (float)rand() / (float)RAND_MAX * 14.0f;
}
