#include <STM32MP1xx_hal.h>
#include <stm32_hal_legacy.h>

#ifdef __cplusplus
extern "C"
#endif
	
// SEE: https://www.st.com/resource/en/user_manual/dm00652742-.pdf
	
void SysTick_Handler(void)
{
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}

int main(void)
{
	HAL_Init();

	__GPIOA_CLK_ENABLE();
	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.Pin = GPIO_PIN_14;

	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStructure.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);

	for (;;)
	{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_14, GPIO_PIN_SET);
		HAL_Delay(500);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_14, GPIO_PIN_RESET);
		HAL_Delay(500);
	}
}
