#include <STM32MP1xx_hal.h>
#include <stm32_hal_legacy.h>

#ifdef __cplusplus
extern "C"
#endif
void SysTick_Handler(void)
{
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}

int main(void)
{
	HAL_Init();

	__GPIOC_CLK_ENABLE();
	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.Pin = GPIO_PIN_12;

	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStructure);

	for (;;)
	{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12, GPIO_PIN_SET);
		HAL_Delay(500);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12, GPIO_PIN_RESET);
		HAL_Delay(500);
	}
}

static void MX_DMA_Init(void) 
{

	/* DMA controller clock enable */
	__HAL_RCC_DMA1_CLK_ENABLE();

	/* DMA interrupt init */
	/* DMA1_Stream5_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(DMA1_Stream5_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(DMA1_Stream5_IRQn);

}

