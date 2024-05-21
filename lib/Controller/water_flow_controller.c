#include "water_flow_controller.h"
#include "servo.h"
#include <math.h>

static uint8_t water_flow_pct;

void water_flow_controller_init()
{
    water_flow_pct = 0;
};

void water_flow_controller_set_flow(uint8_t percentage)
{
    if (percentage > 100) water_flow_pct = 100;

    else if (percentage < 0) water_flow_pct = 0;

    else water_flow_pct = percentage;
    
    uint8_t angle = floor(180 * (percentage / 100));
    servo(angle);
};

uint8_t water_flow_controller_get_flow()
{
    return water_flow_pct;
};