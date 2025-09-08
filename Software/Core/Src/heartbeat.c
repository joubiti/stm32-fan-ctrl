#include "heartbeat.h"
#include "stm32g0xx_hal.h"

#define HEARTBEAT_GPIO_PORT GPIOB
#define HEARTBEAT_GPIO_PIN  GPIO_PIN_13


void heartbeat_initialize(heartbeat_led_t* led, uint16_t period)
{
    heartbeat_set_period(led, period);
}

void heartbeat_set_period(heartbeat_led_t* led, uint16_t period)
{
    led->period_ms = period;
}

void heartbeat_on(heartbeat_led_t* led)
{
    HAL_GPIO_WritePin(HEARTBEAT_GPIO_PORT, HEARTBEAT_GPIO_PIN, 1);
}

void heartbeat_off(heartbeat_led_t* led)
{
    HAL_GPIO_WritePin(HEARTBEAT_GPIO_PORT, HEARTBEAT_GPIO_PIN, 0);
}

void heartbeat_toggle(heartbeat_led_t* led, uint32_t current_tick)
{
    if(current_tick - led->last_tick >= led->period_ms)
    {
        HAL_GPIO_TogglePin(HEARTBEAT_GPIO_PORT, HEARTBEAT_GPIO_PIN);
        led->last_tick = current_tick;
    }
}
