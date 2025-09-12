/**
 * @file tachometer.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2025-09-12
 * 
 * @copyright Copyright (c) 2025
 * 
 */


#include "tachometer.h"

// 1 MHz timer sampling period

static volatile uint32_t captured_value = 0;
static volatile uint32_t previous_captured_value = 0;
static volatile uint32_t current_period_us = 0;


void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim) {  // 1MHz -> 1 tick = 1 us
    if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2) {
        captured_value = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_2);
        current_period_us = (captured_value - previous_captured_value);
        previous_captured_value = captured_value;
    }
}

void tachometer_init(tachometer_t* tach, TIM_HandleTypeDef* htim, uint32_t period_ms)
{
    tach->htim = htim;
    tach->current_rpm = 0;
    tach->period = period_ms;
    tach->last_execution = 0;

    HAL_TIM_IC_Start_IT(tach->htim, TIM_CHANNEL_2);
}


void tachometer_update_rpm(tachometer_t* tach, uint32_t current_tick)
{
    if(current_tick - tach->last_execution >= tach->period)
    {
        // rpm calculations
        uint32_t period_cpy;
        __disable_irq();
        period_cpy = current_period_us;
        __enable_irq();

        tach->current_rpm = (60UL * 1000000UL) / (2UL * period_cpy);
        tach->last_execution = current_tick;
    }
}