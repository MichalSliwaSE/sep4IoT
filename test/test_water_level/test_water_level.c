#include "unity.h"
#include <stdio.h>

#include "water_level.h"

#define MAX_CHANGE 50 

void setUp(void) {
  water_level_init();
}

void tearDown(void) {}

void test_water_level_value_init()
{
    uint16_t value = water_level_measure();

    TEST_ASSERT_GREATER_THAN(0, value); 
    TEST_ASSERT_LESS_THAN(65536, value); 
}

void test_water_level_value_change()
{
    uint16_t value = water_level_measure();
    uint16_t value2 = water_level_measure();

    // Since water level changes should be close to each other,
    // we expect them not to be exactly the same
    TEST_ASSERT(value != value2);
    
    int difference = abs(value2 - value);
    TEST_ASSERT_LESS_THAN(MAX_CHANGE, difference);
}

int main(void)
{
  UNITY_BEGIN();
  RUN_TEST(test_water_level_value_init);
  RUN_TEST(test_water_level_value_change);

  return UNITY_END();
}
