/**
 * @file fan_speed_controller.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2025-09-13
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "fan_speed_controller.h"

#include "stdlib.h"

#define FAN_PWM_CHANNEL TIM_CHANNEL_1

/**
 * @brief Macro helper to get ARR register value from PWM duty cycle
 * 
 */
#define get_pwm_compare_value(x) (uint16_t)((x * 24999)/100)


void fan_speed_controller_init(fan_controller_t* fan, TIM_HandleTypeDef* htim)
{
    fan->htim = htim;
    fan->rpm_measured = 0;
    fan->rpm_requested = 0;

    // start PWM timer
    HAL_TIM_Base_Start(fan->htim);
    HAL_TIM_PWM_Start(fan->htim, TIM_CHANNEL_1);
}


void fan_set_rpm_percent(fan_controller_t* fan, uint8_t percent)
{
    uint8_t scaled_percent = 100 - percent;
    __HAL_TIM_SET_COMPARE(fan->htim, FAN_PWM_CHANNEL, get_pwm_compare_value(scaled_percent));
}
