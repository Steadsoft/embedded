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

// Flash the onboard LED on a Nucleo F446RE

int main(void)
{
	unsigned long ID1 = (*(unsigned long *)0x1FFF7A10);
	unsigned long ID2 = (*(unsigned long *)0x1FFF7A14);
	unsigned long ID3 = (*(unsigned long *)0x1FFF7A18);

	uint32_t ID = DBGMCU->IDCODE;

	HAL_Init();

	__GPIOA_CLK_ENABLE();
	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.Pin = GPIO_PIN_5;
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);

	for (;;)
	{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
		HAL_Delay(500);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
		HAL_Delay(500);
	}
}
