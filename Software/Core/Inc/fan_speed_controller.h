/**
 * @file fan_speed_controller.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2025-09-13
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "stm32g0xx_hal.h"

typedef struct{
    TIM_HandleTypeDef* htim;
    uint16_t rpm_requested;
    uint16_t rpm_measured;
}fan_controller_t;


/**
 * @brief Initialize the fan speed controller using the 25 KHz PWM timer
 * 
 * @param htim 
 */
void fan_speed_controller_init(fan_controller_t* fan, TIM_HandleTypeDef* htim);

/**
 * @brief Sets current fan RPM as (0 -> 100%) of max possible fan RPM
 * 
 * @param percent 
 */
void fan_set_rpm_percent(fan_controller_t* fan, uint8_t percent);

/**
 * @brief Sets current fan RPM
 * 
 * @param rpm 
 */
void fan_set_rpm(fan_controller_t* fan, uint16_t rpm);