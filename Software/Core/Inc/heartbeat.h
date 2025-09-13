/**
 * @file heartbeat.h
 * @author github.com/joubiti
 * @brief Heartbeat LED module
 * @version 0.1
 * @date 2025-09-13
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef _HEARTBEAT_H
#define _HEARTBEAT_H

#include "stdint.h"


typedef struct{
    uint16_t period_ms;
    uint32_t last_tick;
}heartbeat_led_t;

/**
 * @brief Initialize heartbeat LED with specified blinking period
 * 
 * @param led 
 * @param period 
 */
void heartbeat_initialize(heartbeat_led_t* led, uint16_t period);

/**
 * @brief Turn on heartbeat LED
 * 
 * @param led 
 */
void heartbeat_on(heartbeat_led_t* led);

/**
 * @brief Turn off heartbeat LED
 * 
 * @param led 
 */
void heartbeat_off(heartbeat_led_t* led);

/**
 * @brief Toggle heartbeat LED
 * 
 * @param led 
 * @param current_tick 
 */
void heartbeat_toggle(heartbeat_led_t* led, uint32_t current_tick);

/**
 * @brief Set heartbeat LED blinking period
 * 
 * @param led 
 * @param period 
 */
void heartbeat_set_period(heartbeat_led_t* led, uint16_t period);

#endif