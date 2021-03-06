#include "Task/LedHintTask.h"
#include "stm32f4xx.h"

static uint64_t LedHintTaskStack[256 / 8];


/**
 * @brief
 * PE10, PE11, PE12
 */
LedHintTask::LedHintTask(void) : Task("LedHint", LedHintTaskStack, sizeof (LedHintTaskStack))
{
	RCC->AHB1ENR |= 0x10;
	
	GPIOE->MODER &= ~0x3F00000;
	GPIOE->MODER |= 0x1500000;
	GPIOE->PUPDR &= ~0x3F00000;
	GPIOE->OSPEEDR |= 0x3F00000;
	GPIOE->OTYPER &= ~0x1C00;
	GPIOE->BSRRH = 0x1C00;
}

void LedHintTask::run(void)
{
	while (true)
	{
		GPIOE->BSRRL = 0xC00;
		GPIOE->BSRRH = 0x1000;
		osDelay(100);
		GPIOE->BSRRL = 0x1400;
		GPIOE->BSRRH = 0x800;
		osDelay(100);
		GPIOE->BSRRL = 0x1800;
		GPIOE->BSRRH = 0x400;
		osDelay(100);
	}
}






