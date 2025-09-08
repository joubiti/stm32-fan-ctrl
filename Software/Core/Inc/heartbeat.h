#ifndef _HEARTBEAT_H
#define _HEARTBEAT_H

#include "stdint.h"


typedef struct{
    uint16_t period_ms;
    uint32_t last_tick;
}heartbeat_led_t;

void heartbeat_initialize(heartbeat_led_t* led, uint16_t period);

void heartbeat_on(heartbeat_led_t* led);
void heartbeat_off(heartbeat_led_t* led);

void heartbeat_toggle(heartbeat_led_t* led, uint32_t current_tick);
void heartbeat_set_period(heartbeat_led_t* led, uint16_t period);

#endif