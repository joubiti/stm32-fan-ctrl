/**
 * @file pid_controller.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2025-09-13
 * 
 * @copyright Copyright (c) 2025
 * 
 */


#include "pid_controller.h"

void pid_controller_init(pid_controller_t* pid, float Kp, float Ki, float Kd, uint32_t period_ms)
{
    pid->period = period_ms;
    pid->Kp = Kp;
    pid->Ki = Ki;
    pid->Kd = Kd;
    pid->dt = (pid->period/1000.0f);
    pid->last_execution = 0;
    pid->last_err = 0;
}


uint8_t pid_controller_step(pid_controller_t* pid, uint32_t measure, uint32_t target, uint32_t current_tick)
{
    if(current_tick - pid->last_execution >= pid->period)
    {
        // PID is: Kp * e + Ki * integral(e) * dt + Kd * derivative(e)/dt
        // In discrete time, integral(e) can be accumulation of past samples, derivate can be difference
        int32_t err = target - measure;
        // Proportional term
        float P = pid->Kp * err;
        // Integral term
        pid->integral += err * pid->Ki * pid->dt;
        // Anti-windup clamp
        if (pid->integral > 100.0f) pid->integral = 100.0f;
        if (pid->integral < 0.0f) pid->integral = 0.0f;
        // Derivative term
        float D = pid->Kd * (err - pid->last_err)/pid->dt;

        float output = P + pid->integral + D;
        // Clamp output to 0–100% duty cycle
        if (output > 100.0f) output = 100.0f;
        if (output < 0.0f) output = 0.0f;

        pid->last_err = err;
        pid->last_execution = current_tick;

        return (uint8_t)output;
    }
    else
        return PID_NO_UPDATE;
}