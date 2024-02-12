#include <stm32f4xx_ll_bus.h>
#include <stm32f4xx_ll_gpio.h>
#include <stm32f4xx_ll_utils.h>

#include <stdlib.h>
//#define WAIT_FOR_HSE while (!(RCC->CR & 0x00020000))
//#define WAIT_FOR_PLL while (!(RCC->CR & 0x02000000))
#define SPIN_WHILE(X) while((X))
#define SPIN_UNTIL(X) while(!(X))

#define SPEEDR_LOW 0
#define SPEEDR_MEDIUM 1
#define SPEEDR_HIGH 2
#define SPEEDR_VERY_HIGH = 3

#define SPEEDR(X) SPEEDR_ ## X

#define MCOPRE_NONE 0
#define MCOPRE_2 4
#define MCOPRE_3 5
#define MCOPRE_4 6
#define MCOPRE_5 7

#define MCOPRE(X) MCOPRE_ ## X

#define MCO1_HSI 0
#define MCO1_LSE 1
#define MCO1_HSE 2
#define MCO1_PLL 3

#define MCO1(X) MCO1_ ## X

#define I2SSRC_PLLI2S 0
#define I2SSRC_EXTERNAL 1

#define I2SSRC(X) I2SSRC_ ## X

#define SW_HSI 0
#define SW_HSE 1
#define SW_PLL 2

#define SW(X) SW_ ## X

#define SWS_HSI 0
#define SWS_HSE 1
#define SWS_PLL 2

#define SWS(X) SWS_ ## X


#define MODER_INPUT 0
#define MODER_GENERAL 1
#define MODER_ALTERNATE 2
#define MODER_ANALOG 3

#define MODER(X) MODER_ ## X


// STM32F407VG

void Page_374(void);
void UseBitfields(void);

int main(void)
{
	UseBitfields();
}

// This is our reference code. It causes the clock to run at 180MHz 
// and PA8 to generate that speed / 5 = 36 MHz.
// This code runs fine debug or release on the Discovery STM32F407VG
void Page_374(void)
{
	RCC->AHB1ENR |= 1;

	RCC->CFGR &= ~0x07E00000;
	RCC->CFGR |=  0x07600000;
	
	GPIOA->MODER |=   0x00020000;
	GPIOA->AFR[1] &= ~0x00000003; // F ?
	GPIOA->OSPEEDR |= 3 << 8 * 2;
	
	// Set HSE on
	RCC->CR &= ~0x000F0000;
	RCC->CR |=  0x00010000;
	
	while (!(RCC->CR & 0x00020000)) ;
	
	RCC->CFGR &=  ~0x00000003;
	RCC->PLLCFGR = 0x00402D04;
	RCC->CR |=     0x01000000;
	
	while (!(RCC->CR & 0x02000000)) ;
	
	FLASH->ACR = 0x0705;
	
	RCC->CFGR &= ~0x000000F0;
	RCC->CFGR |=  0x00000002;
	
	while ((RCC->CFGR & 0x0C) != 0x08) ;
	
	while (1)
	{
		;
	}
}

#include <regtypes.h>

void UseBitfields()
{
	AHB1_Bus_ptr ahb1_ptr = (AHB1_Bus_ptr)(AHB1PERIPH_BASE);
	APB1_Bus_ptr apb1_ptr = (APB1_Bus_ptr)(APB1PERIPH_BASE);
	
	ahb1_ptr->RCC.AHB1ENR.GPIOA_EN = 1;
	ahb1_ptr->RCC.AHB1ENR.GPIOD_EN = 1;
	
	// RCC->CFGR &= ~0x07E00000;
	// RCC->CFGR |=  0x07600000;

	ahb1_ptr->RCC.CFGR.MCO1_PRE = MCOPRE(5);
	ahb1_ptr->RCC.CFGR.I2SSC = I2SSRC(PLLI2S);
	ahb1_ptr->RCC.CFGR.MCO1 = MCO1(PLL);

	// GPIOA->MODER |= 0x00020000;

	ahb1_ptr->GPIO_A.MODER.MODER_8 = MODER(ALTERNATE);
	
	// GPIOA->AFR[1] &= ~3; // F ? confusing because an AFRH is 4 bits
	
	ahb1_ptr->GPIO_A.AFRH.AFRH_8 = 0;
	
	// 	GPIOA->OSPEEDR |= 3 << 8 * 2;

	ahb1_ptr->GPIO_A.SPEEDR.SPEED_8 = SPEEDR(HIGH);
	
	// RCC->CR &= ~0x000F0000;
	// RCC->CR |=  0x00010000;

	ahb1_ptr->RCC.CR.CSS_ON = 0;
	ahb1_ptr->RCC.CR.HSE_BYP = 0;
	ahb1_ptr->RCC.CR.HSE_RDY = 0;
	ahb1_ptr->RCC.CR.HSE_ON = 1;
	
	SPIN_UNTIL(ahb1_ptr->RCC.CR.HSE_RDY);

	//	RCC->CFGR &=  ~0x00000003;
	//	RCC->PLLCFGR = 0x00402D04;
	//	RCC->CR |=     0x01000000;
	
	ahb1_ptr->RCC.CFGR.SW = 0;
	ahb1_ptr->RCC.PLLCFGR.PLL_M = 4;
	ahb1_ptr->RCC.PLLCFGR.PLL_N = 180;
	ahb1_ptr->RCC.PLLCFGR.PLL_SRC = 1;
	ahb1_ptr->RCC.CR.PLL_ON = 1;
	
	SPIN_UNTIL(ahb1_ptr->RCC.CR.PLL_RDY);
	
	// FLASH->ACR = 0x0705;
	
	ahb1_ptr->FLASH.ACR.LATENCY = 5;
	ahb1_ptr->FLASH.ACR.PRFTEN = 1;
	ahb1_ptr->FLASH.ACR.ICEN = 1;
	ahb1_ptr->FLASH.ACR.DCEN = 1;
	
	//	RCC->CFGR &= ~0x000000F0;
	//	RCC->CFGR |=  0x00000002;

	ahb1_ptr->RCC.CFGR.HPRE = 0;
	ahb1_ptr->RCC.CFGR.SW = SW(PLL);
	
	SPIN_UNTIL(ahb1_ptr->RCC.CFGR.SWS == SWS(PLL));
	
	ahb1_ptr->GPIO_D.MODER.MODER_12 = MODER(GENERAL);
	ahb1_ptr->GPIO_D.OTYPER.OT_12 = 0;
	ahb1_ptr->GPIO_D.SPEEDR.SPEED_12 = SPEEDR(LOW);
	
	while (1)
	{
		ahb1_ptr->GPIO_D.BSRR.BS_12 = 1;   // The "act" of writing (rather than the value being written) sets the bit 
		
		for (unsigned int X = 0; X < 2000000; X++)
		{
		}
		
		ahb1_ptr->GPIO_D.BSRR.BR_12 = 1;  // The "act" of writing (rather than the value being written) resets the bit 
		
		for (unsigned int X = 0; X < 2000000; X++)
		{
		}
	}
}