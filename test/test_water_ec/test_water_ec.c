#include "unity.h"
#include <stdio.h>

#include "water_ec.h"

void setUp(void) {
  water_ec_init();
}
void tearDown(void) {}

void test_water_ec_value_init()
{
    uint16_t value = water_ec_measure();

    TEST_ASSERT_GREATER_THAN(0, value);
    TEST_ASSERT_LESS_THAN(5000, value);
}

void test_water_ec_value_change()
{
    uint16_t value = water_ec_measure();
    uint16_t value2 = water_ec_measure();

    TEST_ASSERT(value != value2);
}

int main(void)
{
  UNITY_BEGIN();
  RUN_TEST(test_water_ec_value_init);
  RUN_TEST(test_water_ec_value_change);

  return UNITY_END();
}