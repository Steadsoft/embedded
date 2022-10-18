#include <stm32f4xx_hal.h>
#include <stm32_hal_legacy.h>

#ifdef __cplusplus
extern "C"
#endif
	
	

void SysTick_Handler(void)
{
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}

GPIO_PinState invert(GPIO_PinState * state);
/*
User LD2: the green LED is a user LED connected to ARDUINO® signal D13 corresponding
to STM32 I/O PA5 (pin 21) or PB13 (pin 34) depending on the STM32 target. Refer to
Table 11 to Table 23 when:
• the I/O is HIGH value, the LED is on
• the I/O is LOW, the LED is off 
• the I O is LOW, the LED is off 
• the I O is LOW, the LED is off 
*/
	
int main(void)
{
	HAL_Init();
	
	__GPIOA_CLK_ENABLE();
	__GPIOB_CLK_ENABLE();
	__GPIOC_CLK_ENABLE();

	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	
	GPIO_InitStructure.Pin = GPIO_PIN_0;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.Pin = GPIO_PIN_1;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.Pin = GPIO_PIN_4;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.Pin = GPIO_PIN_0;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_InitStructure.Pin = GPIO_PIN_1;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	GPIO_InitStructure.Pin = GPIO_PIN_0;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStructure);

	GPIO_PinState state = GPIO_PIN_RESET;
	
	while (true)
	{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, invert(&state));
		HAL_Delay(120);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, invert(&state));
		
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, invert(&state));
		HAL_Delay(120);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, invert(&state));

		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, invert(&state));
		HAL_Delay(120);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, invert(&state));

		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, invert(&state));
		HAL_Delay(120);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, invert(&state));

		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, invert(&state));
		HAL_Delay(120);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, invert(&state));

		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, invert(&state));
		HAL_Delay(120);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, invert(&state));
	}
}

GPIO_PinState invert(GPIO_PinState * state)
{
	if (*state == GPIO_PIN_RESET)
	{
		*state = GPIO_PIN_SET;
		return *state;
	}
	
	*state = GPIO_PIN_RESET;
	return *state;
}