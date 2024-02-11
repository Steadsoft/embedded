#include <stm32f4xx_ll_bus.h>
#include <stm32f4xx_ll_gpio.h>
#include <stm32f4xx_ll_utils.h>

#include <regtypes.h>
#include <stdlib.h>
#define WAIT_FOR_HSE while (!(RCC->CR & 0x00020000))
#define WAIT_FOR_PLL while (!(RCC->CR & 0x02000000))
#define SPIN_WHILE(X) while((X))
#define SPIN_UNTIL(X) while(!(X))

// STM32F407VG

int main(void)
{
	RCC_Registers_ptr rcc_ptr = (RCC_Registers_ptr)(RCC_BASE);
	AHB1_ptr ahb1_ptr = (AHB1_ptr)AHB1PERIPH_BASE;
	APB1_ptr apb1_ptr = (APB1_ptr)(APB1PERIPH_BASE);
	
	void *p = &(ahb1_ptr->CRC);
	void *q = &(ahb1_ptr->RCC);
	void *e = &(ahb1_ptr->GPIO_K);
	
	rcc_ptr->APB1ENR.TIM2_EN = 1;
	
	apb1_ptr->TIM2.Registers.PSC.PSC = 1600 - 1;
	apb1_ptr->TIM2.Registers.CCMR1_OCR.OC1FE = 1;
	
	void * ppp = &(apb1_ptr->TIM2.Registers.PSC);
	
	rcc_ptr->AHB1ENR.GPIOA_EN = 1;
	
	ahb1_ptr->GPIO_A.MODER.MODER_11 = 3;
	
	ahb1_ptr->RCC.AHB1ENR.GPIOA_EN = 1;
	
	ahb1_ptr->RCC.CFGR.MCO1 = 3;
	
	ahb1_ptr->RCC.CFGR.MCO1_PRE = 7;
	
	ahb1_ptr->GPIO_A.MODER.MODER_8 = 2;
	ahb1_ptr->GPIO_A.AFRH.AFRH_8 = 0;
	ahb1_ptr->GPIO_A.SPEEDR.SPEED_8 = 0;
	
	ahb1_ptr->RCC.CR.CSS_ON = 0;
	ahb1_ptr->RCC.CR.HSE_BYP = 0;
	ahb1_ptr->RCC.CR.HSE_RDY = 0;
	ahb1_ptr->RCC.CR.HSE_ON = 1;
	
	SPIN_UNTIL(ahb1_ptr->RCC.CR.HSE_RDY);

	ahb1_ptr->RCC.CFGR.SW = 0;
	ahb1_ptr->RCC.PLLCFGR.PLL_M = 4;
	ahb1_ptr->RCC.PLLCFGR.PLL_N = 168;
	ahb1_ptr->RCC.PLLCFGR.PLL_SRC = 1;
	ahb1_ptr->RCC.CR.PLL_ON = 1;
	
	SPIN_UNTIL(ahb1_ptr->RCC.CR.PLL_RDY);
	
	FLASH->ACR = 0x0705;
	
	ahb1_ptr->RCC.CFGR.HPRE = 0;
	ahb1_ptr->RCC.CFGR.SW = 2;
	
	SPIN_UNTIL(ahb1_ptr->RCC.CFGR.SWS == 2);
	
	
	ahb1_ptr->RCC.AHB1ENR.GPIOD_EN = 1;
	
	ahb1_ptr->GPIO_D.MODER.MODER_12 = 1;
	ahb1_ptr->GPIO_D.OTYPER.OT_12 = 0;
	ahb1_ptr->GPIO_D.SPEEDR.SPEED_12 = 0;
		
	ahb1_ptr->GPIO_D.MODER.MODER_11 = 1;
	ahb1_ptr->GPIO_D.OTYPER.OT_11 = 0;
	ahb1_ptr->GPIO_D.SPEEDR.SPEED_11 = 0;

	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOD);
	
	LL_GPIO_SetPinMode(GPIOD, LL_GPIO_PIN_12, LL_GPIO_MODE_OUTPUT);
	LL_GPIO_SetPinOutputType(GPIOD, LL_GPIO_PIN_12, LL_GPIO_OUTPUT_PUSHPULL);
	LL_GPIO_SetPinSpeed(GPIOD, LL_GPIO_PIN_12, LL_GPIO_SPEED_FREQ_LOW);
	
	LL_GPIO_SetPinMode(GPIOD, LL_GPIO_PIN_11, LL_GPIO_MODE_OUTPUT);
	LL_GPIO_SetPinOutputType(GPIOD, LL_GPIO_PIN_11, LL_GPIO_OUTPUT_PUSHPULL);
	LL_GPIO_SetPinSpeed(GPIOD, LL_GPIO_PIN_11, LL_GPIO_SPEED_FREQ_LOW);

	for (;;)
	{
		//LL_GPIO_SetOutputPin(GPIOD, LL_GPIO_PIN_12);
		LL_GPIO_SetOutputPin(GPIOD, LL_GPIO_PIN_11);
		//WRITE_REG(GPIOD->BSRR, LL_GPIO_PIN_11);
		//LL_mDelay(5);
		//LL_GPIO_ResetOutputPin(GPIOD, LL_GPIO_PIN_12);
		LL_GPIO_ResetOutputPin(GPIOD, LL_GPIO_PIN_11);
		//WRITE_REG(GPIOD->BSRR, (LL_GPIO_PIN_11 << 16));
		//LL_mDelay(5);
	}
}
