#include "../fff.h"
#include "unity.h"

#include <stdint.h>
#include <stdio.h>
#include "../lib/mocks/mock_avr_io.h"

#include "water_flow_controller.h"
// #include "json_controller.h"
// #include "connection_controller.h"

DEFINE_FFF_GLOBALS

// WATER FLOW CONTROLLER
FAKE_VOID_FUNC(water_flow_controller_init);
FAKE_VOID_FUNC(water_flow_controller_set_flow, uint8_t);
FAKE_VALUE_FUNC(uint8_t, water_flow_controller_get_flow);

void setUp(void)
{
    RESET_FAKE(water_flow_controller_init);
    RESET_FAKE(water_flow_controller_set_flow);
    RESET_FAKE(water_flow_controller_get_flow);
    FFF_RESET_HISTORY();
}

void tearDown(void)
{
}

// WATER FLOW CONTROLLER
void test_water_flow_status(void){
    water_flow_controller_init();
    TEST_ASSERT_EQUAL(1, water_flow_controller_init_fake.call_count);

    uint8_t expected_flow = 90;
    water_flow_controller_get_flow_fake.return_val = expected_flow;

    water_flow_controller_set_flow(expected_flow);

    uint8_t result = water_flow_controller_get_flow();
    TEST_ASSERT_EQUAL(expected_flow, result);
}

void test_water_flow_set_closing_less_then_0(void){
    water_flow_controller_init();
    TEST_ASSERT_EQUAL(1, water_flow_controller_init_fake.call_count);

    uint8_t invalid_flow = -20;
    uint8_t expected_flow = 0;

    water_flow_controller_set_flow(invalid_flow);

    water_flow_controller_get_flow_fake.return_val = expected_flow;

    uint8_t result = water_flow_controller_get_flow();

    TEST_ASSERT_EQUAL(0, result);
}

void test_water_flow_set_opening_more_then_100(void){
    water_flow_controller_init();
    TEST_ASSERT_EQUAL(1, water_flow_controller_init_fake.call_count);

    uint8_t invalid_flow = 120;
    uint8_t expected_flow = 100;

    water_flow_controller_set_flow(invalid_flow);

    water_flow_controller_get_flow_fake.return_val = expected_flow;

    uint8_t result = water_flow_controller_get_flow();
    TEST_ASSERT_EQUAL(100, result);
}

// JSON CONTROLLER

// CONNECTION CONTROLLER



int main(void)
{
    UNITY_BEGIN();

    // WATER FLOW CONTROLLER
    RUN_TEST(test_water_flow_status);
    RUN_TEST(test_water_flow_set_closing_less_then_0);
    RUN_TEST(test_water_flow_set_opening_more_then_100);

    return UNITY_END();
}