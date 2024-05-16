
#include "unity.h"
#include <stdint.h>
#include <math.h>
#include "dht11.h"
#include <stdio.h>

void setUp(void)
{
}

void tearDown(void)
{
}

void test_dht11_status()
{
    dht11_init();
    _delay_ms(2000);
    TEST_ASSERT_EQUAL(DHT11_OK, dht11_get(NULL, NULL, NULL, NULL));
}

void test_temperature_is_22celc()
{
    dht11_init();
    _delay_ms(2000);
    uint8_t celc, celc_dec, hum_int, hum_dec;
    dht11_get(&hum_int, &hum_dec, &celc, &celc_dec);
    TEST_ASSERT_INT_WITHIN(5, 22, celc);

    char message[1024];
    sprintf(message, "INFO! dht11 measurement! Temperature %d.%d C! Humidity %d.%d%%       :1:_:PASS\n", celc, celc_dec, hum_int, hum_dec);
    TEST_MESSAGE(message); // TEST_MESSAGE("m e s s a g e :1:_:PASS\n"); // no : in the message
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_dht11_status);
    RUN_TEST(test_temperature_is_22celc);

    TEST_MESSAGE("INFO! wave your hand above the pir sensor after starwars       :1:_:PASS\n"); // no : in the message
    return UNITY_END();
}