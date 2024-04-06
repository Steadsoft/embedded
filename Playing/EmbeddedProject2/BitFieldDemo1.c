#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <regtypes.h>
#include <statics.h>
#include <regdefs.h>
#include <sysdefs.h>

//int lock = 0;
//int unlocked = 0;
//int locked = 1;
//	
//char flag = __atomic_compare_exchange(&lock, &unlocked, &locked, 0, 0, 0);





static int count = 0;

void SetupSysTick();
void Page_374(void);
void BitfieldExampleA(void);
void SetupSystemClock(void);

int main(void)
{

	SetupSysTick();
	
	BitfieldExampleA();
}


void SysTick_Handler(void)
{
	count++;
}


// STM32F407VG



// This is our reference code. It causes the clock to run at 180MHz 
// and PA8 to generate that speed / 5 = 36 MHz.
// This code runs fine debug or release on the Discovery STM32F407VG
void Page_374(void)
{
//	RCC->AHB1ENR |= 1;
//
//	RCC->CFGR &= ~0x07E00000;
//	RCC->CFGR |=  0x07600000;
//	
//	GPIOA->MODER |=   0x00020000;
//	GPIOA->AFR[1] &= ~0x00000003; // F ?
//	GPIOA->OSPEEDR |= 3 << 8 * 2;
//	
//	// Set HSE on
//	RCC->CR &= ~0x000F0000;
//	RCC->CR |=  0x00010000;
//	
//	while (!(RCC->CR & 0x00020000)) ;
//	
//	RCC->CFGR &=  ~0x00000003;
//	RCC->PLLCFGR = 0x00402D04;
//	RCC->CR |=     0x01000000;
//	
//	while (!(RCC->CR & 0x02000000)) ;
//	
//	FLASH->ACR = 0x0705;
//	
//	RCC->CFGR &= ~0x000000F0;
//	RCC->CFGR |=  0x00000002;
//	
//	while ((RCC->CFGR & 0x0C) != 0x08) ;
//	
//	while (1)
//	{
//		;
//	}
}

void BitfieldExampleA()
{

	SetupSystemClock();
	
	bus.ahb1_ptr->RCC.AHB1ENR.GPIOA_EN = 1;
	bus.ahb1_ptr->RCC.AHB1ENR.GPIOD_EN = 1;

	// Setup the GPIO pins
	
	bus.ahb1_ptr->GPIO_D.MODER.MODER_12 = MODER(GENERAL);
	bus.ahb1_ptr->GPIO_D.OTYPER.OT_12 = 0;
	bus.ahb1_ptr->GPIO_D.SPEEDR.SPEED_12 = SPEEDR(LOW);
	
	bus.ahb1_ptr->GPIO_D.MODER.MODER_13 = MODER(GENERAL);
	bus.ahb1_ptr->GPIO_D.OTYPER.OT_13 = 0;
	bus.ahb1_ptr->GPIO_D.SPEEDR.SPEED_13 = SPEEDR(LOW);
	
	bus.ahb1_ptr->GPIO_D.MODER.MODER_14 = MODER(GENERAL);
	bus.ahb1_ptr->GPIO_D.OTYPER.OT_14 = 0;
	bus.ahb1_ptr->GPIO_D.SPEEDR.SPEED_14 = SPEEDR(LOW);
	
	bus.ahb1_ptr->GPIO_D.MODER.MODER_15 = MODER(GENERAL);
	bus.ahb1_ptr->GPIO_D.OTYPER.OT_15 = 0;
	bus.ahb1_ptr->GPIO_D.SPEEDR.SPEED_15 = SPEEDR(LOW);
	
	// Setup TIMER2 approx 1 Hz
	
	bus.ahb1_ptr->RCC.APB1ENR.TIM2_EN = 1;
	bus.apb1_ptr->TIM2.PSC.PSC = 1600 - 1;
	bus.apb1_ptr->TIM2.ARR.ARRH = 0;
	bus.apb1_ptr->TIM2.ARR.ARRL = 10000 - 1;
	bus.apb1_ptr->TIM2.CNT.CNT = 0;
	bus.apb1_ptr->TIM2.CR1.CEN = 1;
	
	// Loop forever and toggle the four LEDs
	
	while (1)
	{
		// The "act" of writing (rather than the value being written) 
		// sets/resets the bit when using the BSSR register.
		
		bus.ahb1_ptr->GPIO_D.BSRR.BS_12 = 1; 
		WAIT_FOR(bus.apb1_ptr->TIM2);
		bus.ahb1_ptr->GPIO_D.BSRR.BS_13 = 1; 
		WAIT_FOR(bus.apb1_ptr->TIM2);
		bus.ahb1_ptr->GPIO_D.BSRR.BS_14 = 1; 
		WAIT_FOR(bus.apb1_ptr->TIM2);
		bus.ahb1_ptr->GPIO_D.BSRR.BS_15 = 1; 
		WAIT_FOR(bus.apb1_ptr->TIM2);
		bus.ahb1_ptr->GPIO_D.BSRR.BR_15 = 1; 
		WAIT_FOR(bus.apb1_ptr->TIM2);
		bus.ahb1_ptr->GPIO_D.BSRR.BR_14 = 1; 
		WAIT_FOR(bus.apb1_ptr->TIM2);
		bus.ahb1_ptr->GPIO_D.BSRR.BR_13 = 1; 
		WAIT_FOR(bus.apb1_ptr->TIM2);
		bus.ahb1_ptr->GPIO_D.BSRR.BR_12 = 1; 
		WAIT_FOR(bus.apb1_ptr->TIM2);
	}
}

void SetupSystemClock()
{
	uint32_t spinner = 0;
	
	
	// RCC->CFGR &= ~0x07E00000;
	// RCC->CFGR |=  0x07600000;

	bus.ahb1_ptr->RCC.CFGR.MCO1_PRE = MCOPRE(5);
	bus.ahb1_ptr->RCC.CFGR.I2SSC = I2SSRC(PLLI2S);
	bus.ahb1_ptr->RCC.CFGR.MCO1 = MCO1(PLL);

	// GPIOA->MODER |= 0x00020000;

	bus.ahb1_ptr->GPIO_A.MODER.MODER_8 = MODER(ALTERNATE);
	
	// GPIOA->AFR[1] &= ~3; // F ? confusing because an AFRH is 4 bits
	
	bus.ahb1_ptr->GPIO_A.AFRH.AFRH_8 = 0;
	
	// 	GPIOA->OSPEEDR |= 3 << 8 * 2;

	bus.ahb1_ptr->GPIO_A.SPEEDR.SPEED_8 = SPEEDR(HIGH);
	
	// RCC->CR &= ~0x000F0000;
	// RCC->CR |=  0x00010000;

	bus.ahb1_ptr->RCC.CR.CSS_ON = 0;
	bus.ahb1_ptr->RCC.CR.HSE_BYP = 0;
	bus.ahb1_ptr->RCC.CR.HSE_RDY = 0;
	bus.ahb1_ptr->RCC.CR.HSE_ON = 1;
	
	COUNT_UNTIL(bus.ahb1_ptr->RCC.CR.HSE_RDY, &spinner);

	//	RCC->CFGR &=  ~0x00000003;
	//	RCC->PLLCFGR = 0x00402D04;
	//	RCC->CR |=     0x01000000;
	
	bus.ahb1_ptr->RCC.CFGR.SW = 0;
	
	bus.ahb1_ptr->RCC.PLLCFGR.PLL_M = 4;
	bus.ahb1_ptr->RCC.PLLCFGR.PLL_N = 180;
	bus.ahb1_ptr->RCC.PLLCFGR.PLL_SRC = 1;
	bus.ahb1_ptr->RCC.CR.PLL_ON = 1;
	
	COUNT_UNTIL(bus.ahb1_ptr->RCC.CR.PLL_RDY, &spinner);
	
	// FLASH->ACR = 0x0705;
	
	bus.ahb1_ptr->FLASH.ACR.LATENCY = 5;
	bus.ahb1_ptr->FLASH.ACR.PRFTEN = 1;
	bus.ahb1_ptr->FLASH.ACR.ICEN = 1;
	bus.ahb1_ptr->FLASH.ACR.DCEN = 1;
	
	//	RCC->CFGR &= ~0x000000F0;
	//	RCC->CFGR |=  0x00000002;

	bus.ahb1_ptr->RCC.CFGR.HPRE = 0;
	bus.ahb1_ptr->RCC.CFGR.SW = SW(PLL);
	
	COUNT_UNTIL(bus.ahb1_ptr->RCC.CFGR.SWS == SWS(PLL), &spinner);

}

void SetupSysTick()
{

	SCB_AIRCR_Reg aircr;
	
	bus.syst_ptr->CTRL.ENABLE = 0;
	
	// Must be written a single 32 bit write.
	
	aircr = bus.scb_ptr->AIRCR;
	aircr.VECTKEY = SCB_AIRCR_VECTKEY;
	aircr.PRIGROUP = 3;
	bus.scb_ptr->AIRCR = aircr;
	
	bus.syst_ptr->LOAD.ALLBITS = 16000;
	
	bus.scb_ptr->SHPR.PRI_15 = 15; // NVIC_SetPriority
	
	bus.syst_ptr->VAL.ALLBITS = 0;
	
	bus.syst_ptr->CTRL.TICKINT = 1;
	bus.syst_ptr->CTRL.CLKSOURCE = 1;
	bus.syst_ptr->CTRL.ENABLE = 1;
}