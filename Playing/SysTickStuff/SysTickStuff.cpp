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

int main(void)
{
//	uint32_t PriorityGroup = 3;
//	uint32_t reg_value;
//	uint32_t tempo;
//	
//	uint32_t PriorityGroupTmp = (PriorityGroup & (uint32_t)0x07UL); /* only values 0..7 are used          */
//
//	reg_value  =  SCB->AIRCR; /* read old register configuration    */
//	tempo = (uint32_t)(SCB_AIRCR_VECTKEY_Msk | SCB_AIRCR_PRIGROUP_Msk);
//	reg_value &= ~(tempo); /* clear bits to change               */
//	reg_value  =  (reg_value                                   |
//	              ((uint32_t)0x5FAUL << SCB_AIRCR_VECTKEY_Pos) |
//	              (PriorityGroupTmp << SCB_AIRCR_PRIGROUP_Pos)); /* Insert write key and priority group */
//	SCB->AIRCR =  reg_value;

	
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
