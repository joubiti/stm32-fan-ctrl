/**
 * @file pid_controller.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2025-09-13
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "stdint.h"

#define PID_NO_UPDATE 0xFF

typedef struct{
    float Kp;
    float Ki;
    float Kd;
    uint32_t last_execution;
    int32_t last_err;
    float integral;
    float dt;
    uint32_t period;
}pid_controller_t;


/**
 * @brief Initialize the PID controller with the given coefficients and control frequency
 * 
 * @param pid 
 * @param Kp 
 * @param Ki 
 * @param Kd 
 * @param period_ms 
 */
void pid_controller_init(pid_controller_t* pid, float Kp, float Ki, float Kd, uint32_t period_ms);


/**
 * @brief Run PID controller at specified frequency
 * 
 * @param measure 
 * @param target 
 * @param current_tick 
 * @return uint8_t
 */
uint8_t pid_controller_step(pid_controller_t* pid, uint32_t measure, uint32_t target, uint32_t current_tick);