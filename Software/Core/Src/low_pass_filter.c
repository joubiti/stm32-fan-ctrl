#include "low_pass_filter.h"

void low_pass_filter_init(lp_filter_t* filter, float alpha_cst, uint16_t period_ms)
{
    filter->alpha = alpha_cst;
    filter->last_sample = 0;
    filter->period = period_ms;
    filter->last_execution = 0;
}

uint16_t low_pass_filter_update(lp_filter_t* filter, float sample, uint32_t current_tick)
{
    // filtered_value = alpha * new_sample + (1 - alpha) * last_sample
    if(current_tick - filter->last_execution >= filter->period)
    {
        filter->last_sample = (filter->alpha * sample) + (1 - filter->alpha) * filter->last_sample;
        filter->last_execution = current_tick;
    }
    return filter->last_sample;
}