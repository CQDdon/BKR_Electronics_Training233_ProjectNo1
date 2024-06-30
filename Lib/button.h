#ifndef BUTTON_H
#define BUTTON_H

#include "main.h"

typedef struct
{
	uint8_t buttonCurrentStat;
	uint8_t buttonLastStat;
	uint8_t buttonFilter;
	uint8_t isDebouncing;
	uint32_t timeDebounce;
	uint32_t timeStartPress;
	uint8_t isPressTimeOut;
	GPIO_TypeDef *buttonGPIO;
	uint16_t GPIO_Pin;
}ButtonTypedef;

void buttonHandle(ButtonTypedef *ButtonData);

void buttonInit(ButtonTypedef *ButtonData, GPIO_TypeDef *buttonGPIO, uint16_t GPIO_Pin);
#endif
