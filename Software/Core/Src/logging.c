#include "logging.h"
#include "stm32g0xx_hal.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

static void _logging_send_fmt_output(const char* fmt, va_list args);

typedef struct{
    UART_HandleTypeDef* huart;
    uint32_t msg_period;
    uint32_t last_tick;
}logging_subsystem_t;

// singleton
static logging_subsystem_t logging_subsystem;

void logging_subsystem_init(UART_HandleTypeDef* huart)
{
    logging_subsystem.huart = huart;
    // default value
    logging_subsystem.msg_period = 1000;
}

void logging_set_message_frequency(uint32_t period)
{
    logging_subsystem.msg_period = period;
}


void logging_send_output(const char* msg, ...)
{
    va_list args;
    va_start(args, msg);
    _logging_send_fmt_output(msg, args);
    va_end(args);
}

void logging_send_periodic_msg(uint32_t current_tick, const char* msg, ...)
{
    if(current_tick - logging_subsystem.last_tick > logging_subsystem.msg_period)
    {
        va_list args;
        va_start(args, msg);
        _logging_send_fmt_output(msg, args);
        va_end(args);
        logging_subsystem.last_tick = current_tick;
    }
}


static void _logging_send_fmt_output(const char* fmt, va_list args)
{
    char buffer[128];
    vsnprintf(buffer, sizeof(buffer), fmt, args);

    HAL_UART_Transmit(logging_subsystem.huart, (const uint8_t*) buffer, strlen(buffer), 100);
}