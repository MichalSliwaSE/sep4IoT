#include "unity.h"
#include <stdio.h>
#include "co2.h"

void setUp(void) {
  co2_init();
}

void tearDown(void) {}

void test_co2_valid_range()
{
    uint16_t value = co2_measure();

    TEST_ASSERT_GREATER_THAN(499, value);
    TEST_ASSERT_LESS_THAN(2001, value);
}

void test_co2_change()
{
    uint16_t value = co2_measure();
    uint16_t value2 = co2_measure();

    TEST_ASSERT(value != value2);
}

int main(void)
{
  UNITY_BEGIN();
  RUN_TEST(test_co2_valid_range);
  RUN_TEST(test_co2_change);

  return UNITY_END();
}