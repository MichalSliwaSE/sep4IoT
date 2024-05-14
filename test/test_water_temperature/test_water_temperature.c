#include "unity.h"
#include <stdint.h>
#include <math.h>
#include <stdio.h>

#include "../lib/drivers/water_temperature.h"

void setUp(void)
{
    water_temperature_init();
}

void tearDown(void)
{
}

void test_water_temperature_is_between_0_and_31celc() {
    double temperature = water_temperature_get();

    TEST_ASSERT_GREATER_THAN(0, temperature);
    TEST_ASSERT_LESS_THAN(31, temperature);
}

void test_water_temperature_change(){
    double temperature1 = water_temperature_get();
    double temperature2 = water_temperature_get();

    TEST_ASSERT_TRUE(temperature1 != temperature2);
}

int main(void){
    UNITY_BEGIN();

    RUN_TEST(test_water_temperature_is_between_0_and_31celc);
    RUN_TEST(test_water_temperature_change);

    return UNITY_END();
}
