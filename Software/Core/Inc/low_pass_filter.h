/**
 * @file low_pass_filter.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2025-09-14
 * 
 * @copyright Copyright (c) 2025
 * 
 */


#include "stdint.h"

typedef struct{
    float alpha;
    float last_sample;
    uint16_t period;
    uint32_t last_execution;
}lp_filter_t;


void low_pass_filter_init(lp_filter_t* filter, float alpha_cst, uint16_t period_ms);
uint16_t low_pass_filter_update(lp_filter_t* filter, float sample, uint32_t current_tick);