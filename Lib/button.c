#include "button.h"

uint8_t check = 0;

__weak void buttonPress(ButtonTypedef *ButtonData)
{
	// ham xu ly nhan (luon thuc hien)
}
__weak void buttonPressShort(ButtonTypedef *ButtonData)
{
	// ham xu ly nhan nhanh
}
__weak void buttonRelease(ButtonTypedef *ButtonData)
{
	// ham xu ly tha (luon thuc hien)
}
__weak void buttonPressTimeout(ButtonTypedef *ButtonData)
{
	// ham xu ly nhan giu
}

// set data cho struct
void setButtonData(ButtonTypedef *ButtonData)
{
	ButtonData->buttonCurrentStat = 1;
	ButtonData->buttonLastStat = 1;
	ButtonData->buttonFilter = 1;
}

void buttonHandle(ButtonTypedef *ButtonData)
{
	//set data ban dau
	if(check == 1) goto checkDone;
	
	setButtonData(ButtonData);
	check = 1;
	checkDone:;
	
	// loc nhieu
	uint8_t stat = HAL_GPIO_ReadPin(ButtonData->buttonGPIO, ButtonData->GPIO_Pin); 
	// reset timeDebounce khi nhan ra co su thay doi trang thai
	if(stat != ButtonData->buttonFilter) 
	{
		ButtonData->buttonFilter = stat;
		ButtonData->isDebouncing = 1;
		ButtonData->timeDebounce = HAL_GetTick();
	}
	// sau 15ms ko xuat hien nhieu thi xac nhan trang thai hien tai
	if(ButtonData->isDebouncing && (HAL_GetTick() - ButtonData->timeDebounce >= 15)) 
	{
		ButtonData->buttonCurrentStat = ButtonData->buttonFilter;
		ButtonData->isDebouncing = 0;
	}
	// xu ly cac truong hop nhan nha
	if(ButtonData->buttonCurrentStat != ButtonData->buttonLastStat)
	{
		// nhan xuong
		if(ButtonData->buttonCurrentStat == 0)
		{
			// xac nhan da nhan xuong
			ButtonData->isPressTimeOut = 1; 
			//thuc hien ham buttonPress khi nhan nut
			buttonPress(ButtonData);
			// tinh thoi gian nhan
			ButtonData->timeStartPress = HAL_GetTick();
		}
		// nha nut
		else 
		{
			// nhan nha ngay lap tuc (<1000)
			if(HAL_GetTick() - ButtonData->timeStartPress <= 2000)
				// ham cho lenh nhan nha nhan
				buttonPressShort(ButtonData);
			//thuc hien ham nha nut
			buttonRelease(ButtonData);
			ButtonData->isPressTimeOut = 0;
		}
		ButtonData->buttonLastStat = ButtonData->buttonCurrentStat;
	}
	// ham nhan giu nut
	if(ButtonData->isPressTimeOut && (HAL_GetTick() - ButtonData->timeStartPress >= 2000))
	{
		buttonPressTimeout(ButtonData);
		ButtonData->isPressTimeOut = 0;
	}
}

//khai bao GPIO va chan cho nut
void buttonInit(ButtonTypedef *ButtonData, GPIO_TypeDef *buttonGPIO, uint16_t GPIO_Pin)
{
	ButtonData->buttonGPIO = buttonGPIO;
	ButtonData->GPIO_Pin = GPIO_Pin;
}
