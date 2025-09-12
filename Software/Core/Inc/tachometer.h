/**
 * @file tachometer.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2025-09-12
 * 
 * @copyright Copyright (c) 2025
 * 
 */


 #include "stm32g0xx_hal.h"


 typedef struct{
    TIM_HandleTypeDef* htim;
    uint32_t period;
    uint32_t current_rpm;
    uint32_t last_execution;
 }tachometer_t;


/**
 * @brief Initialize the tachometer input (timer input capture mode)
 * 
 * @param tach pointer to tach object
 * @param htim pointer to timer used
 * @param period_ms refresh period in milliseconds
 */
 void tachometer_init(tachometer_t* tach, TIM_HandleTypeDef* htim, uint32_t period_ms);

/**
 * @brief Update fan RPM measurements at a specific frequency
 * 
 * @param tach 
 * @param current_tick 
 */
 void tachometer_update_rpm(tachometer_t* tach, uint32_t current_tick);