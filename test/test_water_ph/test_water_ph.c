#include "unity.h"
#include <stdio.h>

#include "ph_sensor.h"

void setUp(void) {
  ph_sensor_init();
}

void tearDown(void) {}

void test_ph_value_init() {
    int value = ph_sensor_measure();

    TEST_ASSERT_TRUE(value >= 0);
    TEST_ASSERT_TRUE(value <= 14);
}

void test_ph_value_change() {
    int value = ph_sensor_measure();
    int value2 = ph_sensor_measure();

    TEST_ASSERT_NOT_EQUAL(value, value2);
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_ph_value_init);
  RUN_TEST(test_ph_value_change);

  return UNITY_END();
}