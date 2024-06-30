#ifndef PWM_H
#define PWM_H

#include "main.h"

void PWMdutyChange(TIM_HandleTypeDef *htim, uint32_t channel, uint8_t dutyCycle);

#endif
