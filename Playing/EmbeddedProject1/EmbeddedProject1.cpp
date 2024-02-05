//#include <stm32f4xx_hal.h>
//#include <stm32_hal_legacy.h>

#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "system_stm32f4xx.h"

// Target board is STM32F4DISCOVERY MCU is STM32F407VG

void Set(uint16_t Pin);
void Reset(uint16_t Pin);
static TIM_HandleTypeDef s_TimerInstance = { 
	.Instance = TIM2
};

#ifdef __cplusplus
extern "C" void SysTick_Handler(void)
{
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}

extern "C" void TIM2_IRQHandler()
{
	HAL_TIM_IRQHandler(&s_TimerInstance);
}
#else
void SysTick_Handler(void)
{
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}
void TIM2_IRQHandler()
{
	HAL_TIM_IRQHandler(&s_TimerInstance);
}
#endif

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_11);
}
static int timerValue;

void InitializeTimer()
{
	__TIM2_CLK_ENABLE();
	s_TimerInstance.Init.Prescaler = 8;
	s_TimerInstance.Init.CounterMode = TIM_COUNTERMODE_UP;
	s_TimerInstance.Init.Period = 1;
	s_TimerInstance.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	s_TimerInstance.Init.RepetitionCounter = 0;
	HAL_TIM_Base_Init(&s_TimerInstance);
	HAL_TIM_Base_Start_IT(&s_TimerInstance);
}

int main(void)
{
	//
	    //  Uncomment this line to see the effect of
	    //  the clock change.
	    //
	    //SystemInit();
	    //
	    //  Initialise the peripheral clock.
	    //
	RCC->AHB1ENR |= RCC_AHB1Periph_GPIOD;
	//
	//  Initialise the GPIO port.
	//
	GPIOD->MODER |= GPIO_Mode_OUT;
	GPIOD->OSPEEDR |= GPIO_Speed_100MHz;
	GPIOD->OTYPER |= GPIO_OType_PP;
	GPIOD->PUPDR |= GPIO_PuPd_NOPULL;
	//
	//  Toggle Port D, pin 0 indefinitely.
	//
	while (1)
	{
		GPIOD->BSRRL = GPIO_Pin_0;
		GPIOD->BSRRH = GPIO_Pin_0;
	}	
}

int oldmain(void)
{
	HAL_Init();
	InitializeTimer();
	
	int x = HSE_VALUE;
	
	__GPIOD_CLK_ENABLE();

	GPIO_InitTypeDef BLUE;
	GPIO_InitTypeDef ORANGE;
	GPIO_InitTypeDef RED;
	GPIO_InitTypeDef GREEN;
	GPIO_InitTypeDef SCOPE;
	SCOPE.Pin = GPIO_PIN_11;
	SCOPE.Mode = GPIO_MODE_OUTPUT_PP;
	SCOPE.Speed = GPIO_SPEED_FREQ_LOW;
	SCOPE.Pull = GPIO_NOPULL;

	GREEN.Pin = GPIO_PIN_12;
	GREEN.Mode = GPIO_MODE_OUTPUT_PP;
	GREEN.Speed = GPIO_SPEED_FREQ_HIGH;
	GREEN.Pull = GPIO_NOPULL;
	
	ORANGE.Pin = GPIO_PIN_13;
	ORANGE.Mode = GPIO_MODE_OUTPUT_PP;
	ORANGE.Speed = GPIO_SPEED_FREQ_HIGH;
	ORANGE.Pull = GPIO_NOPULL;
	
	RED.Pin = GPIO_PIN_14;
	RED.Mode = GPIO_MODE_OUTPUT_PP;
	RED.Speed = GPIO_SPEED_FREQ_HIGH;
	RED.Pull = GPIO_NOPULL;
	
	BLUE.Pin = GPIO_PIN_15;
	BLUE.Mode = GPIO_MODE_OUTPUT_PP;
	BLUE.Speed = GPIO_SPEED_FREQ_HIGH;
	BLUE.Pull = GPIO_NOPULL;
	
	HAL_GPIO_Init(GPIOD, &SCOPE);
	HAL_GPIO_Init(GPIOD, &GREEN);
	HAL_GPIO_Init(GPIOD, &ORANGE);
	HAL_GPIO_Init(GPIOD, &RED);
	HAL_GPIO_Init(GPIOD, &BLUE);

	uint16_t pin;
	
	HAL_NVIC_SetPriority(TIM2_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(TIM2_IRQn);
	
	for (;;)
	{
		
//		if (__HAL_TIM_GET_FLAG(&s_TimerInstance, TIM_FLAG_UPDATE) != RESET)
//		{
//			__HAL_TIM_CLEAR_IT(&s_TimerInstance, TIM_IT_UPDATE);
//			HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_11);
//		}		
		
//		timerValue = __HAL_TIM_GET_COUNTER(&s_TimerInstance); 
//		
//		if (timerValue == 8)
//			Set(GPIO_PIN_11);
//		
//		if (timerValue == 10)
//			Reset(GPIO_PIN_11);

//		Set(GPIO_PIN_12);
//		Set(GPIO_PIN_13);
//		Set(GPIO_PIN_14);
//		Set(GPIO_PIN_15);
//		HAL_Delay(2);
////		Reset(GPIO_PIN_11);
//		Reset(GPIO_PIN_12);
//		Reset(GPIO_PIN_13);
//		Reset(GPIO_PIN_14);
//		Reset(GPIO_PIN_15);
//		HAL_Delay(2);
	}
}

void Set(uint16_t Pin)
{
	HAL_GPIO_WritePin(GPIOD, Pin, GPIO_PIN_SET);
}

void Reset(uint16_t Pin)
{
	HAL_GPIO_WritePin(GPIOD, Pin, GPIO_PIN_RESET);
}
