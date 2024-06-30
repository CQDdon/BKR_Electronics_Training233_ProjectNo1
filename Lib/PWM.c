#include "PWM.h"

void PWMdutyChange(TIM_HandleTypeDef *htim, uint32_t channel, uint8_t dutyCycle) {
    // Giai han gia tri dutyCycle tu 0 den 100
    if (dutyCycle > 100) {
        dutyCycle = 100;
    }
    
    // Tinh toan giá tri tuong ung voi duty cycle
    uint32_t pulse = (htim->Init.Period + 1) * dutyCycle / 100;
    
    // Cap nhat giá tri CCR tuong ung voi kenh PWM
    switch (channel) {
        case TIM_CHANNEL_1:
            htim->Instance->CCR1 = pulse;
            break;
        case TIM_CHANNEL_2:
            htim->Instance->CCR2 = pulse;
            break;
        case TIM_CHANNEL_3:
            htim->Instance->CCR3 = pulse;
            break;
        case TIM_CHANNEL_4:
            htim->Instance->CCR4 = pulse;
            break;
        default:
            break;
    }
    
    HAL_TIM_PWM_Start(htim, channel);
}
