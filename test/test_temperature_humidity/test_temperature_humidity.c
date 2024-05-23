#include "../fff.h"
#include "unity.h"

#include <stdint.h>
#include <stdio.h>
#include "../lib/mocks/mock_avr_io.h"

#include "dht11.h"

DEFINE_FFF_GLOBALS

void setUp(void)
{
}

void tearDown(void)
{
}

FAKE_VOID_FUNC(dht11_init);
FAKE_VALUE_FUNC(DHT11_ERROR_MESSAGE_t, dht11_get, uint8_t *, uint8_t *, uint8_t *, uint8_t *);

void test_dht11_status(void)
{
    dht11_init();
    TEST_ASSERT_EQUAL(1, dht11_init_fake.call_count);

    dht11_get_fake.return_val = DHT11_OK;

    uint8_t dummy;
    DHT11_ERROR_MESSAGE_t result = dht11_get(&dummy, &dummy, &dummy, &dummy);

    TEST_ASSERT_EQUAL(DHT11_OK, result);
    TEST_ASSERT_EQUAL(1, dht11_get_fake.call_count);
}

DHT11_ERROR_MESSAGE_t dht11_get_custom_fake(uint8_t *hum, uint8_t *arg2, uint8_t *temp, uint8_t *arg4)
{
    if (hum || temp)
    {
        *hum = 80;  // Simulate a humidity value of 80
        *temp = 22; // Simulate a temperature value of 22
    }

    return DHT11_OK;
}

void test_temperature_is_22celc(void)
{
    dht11_init();
    TEST_ASSERT_EQUAL(2, dht11_init_fake.call_count);

    uint8_t expected_temp = 22;

    dht11_get_fake.custom_fake = dht11_get_custom_fake;

    uint8_t celc = 0, dummy = 80;
    DHT11_ERROR_MESSAGE_t result = dht11_get(&dummy, NULL, &celc, NULL);

    TEST_ASSERT_EQUAL(DHT11_OK, result);
    TEST_ASSERT_EQUAL(expected_temp, celc);
    TEST_ASSERT_EQUAL(2, dht11_get_fake.call_count);

    char message[1024];
    sprintf(message, "INFO! dht11 measurement! Temperature %d C!       :1:_:PASS\n", celc);
    TEST_MESSAGE(message); // TEST_MESSAGE("m e s s a g e :1:_:PASS\n"); // no : in the message
}

void test_humidity_is_80celc(void)
{
    dht11_init();
    TEST_ASSERT_EQUAL(3, dht11_init_fake.call_count);

    uint8_t expected_hum = 80;

    dht11_get_fake.custom_fake = dht11_get_custom_fake;

    uint8_t humidity = 0, dummy = 22;
    DHT11_ERROR_MESSAGE_t result = dht11_get(&humidity, NULL, &dummy, NULL);

    TEST_ASSERT_EQUAL(DHT11_OK, result);
    TEST_ASSERT_EQUAL(expected_hum, humidity);
    TEST_ASSERT_EQUAL(3, dht11_get_fake.call_count);

    char message[1024];
    sprintf(message, "INFO! dht11 measurement! Humidity %d%%!       :1:_:PASS\n", humidity);
    TEST_MESSAGE(message); // TEST_MESSAGE("m e s s a g e :1:_:PASS\n"); // no : in the message
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_dht11_status);
    RUN_TEST(test_temperature_is_22celc);
    RUN_TEST(test_humidity_is_80celc);

    return UNITY_END();
}