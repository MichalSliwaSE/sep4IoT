#include "unity.h"
#include <util/delay.h>
#include <avr/io.h>
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

void test_water_temperature_is_between_0_and_40celc() {
    // water_temperature_init();
     _delay_ms(1000);

    double temperature = water_temperature_get();

    TEST_ASSERT_GREATER_THAN(0, temperature);
    TEST_ASSERT_LESS_THAN(40, temperature);
}

void test_water_temperature_change(){
    _delay_ms(1000);

    double temperature1 = water_temperature_get();
    double temperature2 = water_temperature_get();

    TEST_ASSERT_TRUE(temperature1 < temperature2 || temperature1 > temperature2);
}

int main(void){
    UNITY_BEGIN();

    RUN_TEST(test_water_temperature_is_between_0_and_40celc);
    RUN_TEST(test_water_temperature_change);

    return UNITY_END();
}
