#include <stm32f4xx_ll_bus.h>
#include <stm32f4xx_ll_gpio.h>
#include <stm32f4xx_ll_utils.h>

#include <regtypes.h>

#define WAIT_FOR_HSE while (!(RCC->CR & 0x00020000))
#define WAIT_FOR_PLL while (!(RCC->CR & 0x02000000))
#define SPIN_WHILE(X) while((X))
#define SPIN_UNTIL(X) while(!(X))

// STM32F407VG

int main(void)
{
	
	RCC_AHB1ENR->GPIOA_EN = 1;
	
	RCC_CFGR->MCO1 = 3;
	RCC_CFGR->MCO1_PRE = 7;
	
	GPIOA->MODER |= 0x00020000;
	GPIOA->AFR[1] &= ~3;
	GPIOA->OSPEEDR |= 3 << 8 * 2;
	
	RCC_CR->CSS_ON = 0;
	RCC_CR->HSE_BYP = 0;
	RCC_CR->HSE_RDY = 0;
	RCC_CR->HSE_ON = 1;
	
	// Set HSE on
//	RCC->CR &= ~0x000F0000;
//	RCC->CR |=  0x00010000;
	
	WAIT_FOR_HSE;
	
	RCC_CFGR->SW = 0;
	
	RCC->PLLCFGR = 0x00402A04;
	RCC->CR |=     0x01000000;
	
	WAIT_FOR_PLL;
	
	FLASH->ACR = 0x0705;
	
	RCC_CFGR->HPRE = 0;
	RCC_CFGR->SW = 2;
	
	SPIN_WHILE(RCC_CFGR->SWS != 2);
	
	
	//LL_InitTick(16000000, 1000);

	//Warning: if the line below triggers an error, GPIOD is not connected to a AHB1 (Group 1) on this device.
	//In this case, please search the stm32xxxx_ll_bus.h file for 'PERIPH_GPIOD' to find out the correct
	//macro name and use it to replace LL_AHB1_GRP1_PERIPH_$$com.sysprogs.examples.lBedblink.LEDPORT$$ and LL_AHB1_GRP1_EnableClock() below. 
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
		//LL_GPIO_SetOutputPin(GPIOD, LL_GPIO_PIN_11);
		WRITE_REG(GPIOD->BSRR, LL_GPIO_PIN_11);
		//LL_mDelay(5);
		//LL_GPIO_ResetOutputPin(GPIOD, LL_GPIO_PIN_12);
		//LL_GPIO_ResetOutputPin(GPIOD, LL_GPIO_PIN_11);
		WRITE_REG(GPIOD->BSRR, (LL_GPIO_PIN_11 << 16));
		//LL_mDelay(5);
	}
}
