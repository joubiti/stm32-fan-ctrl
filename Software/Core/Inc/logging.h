#ifndef _LOGGING_H
#define _LOGGING_H

#include "stm32g0xx_hal.h"

void logging_subsystem_init(UART_HandleTypeDef* huart);
void logging_set_message_frequency(uint32_t period);
void logging_send_output(const char* msg, ...);
void logging_send_periodic_msg(uint32_t current_tic, const char* msg, ...);

#endif