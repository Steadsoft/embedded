//#include <stm32f4xx_ll_bus.h>
//#include <stm32f4xx_ll_gpio.h>
//#include <stm32f4xx_ll_utils.h>

#include <stdint.h>
#include <stdlib.h>

#include <regtypes.h>

//int lock = 0;
//int unlocked = 0;
//int locked = 1;
//	
//char flag = __atomic_compare_exchange(&lock, &unlocked, &locked, 0, 0, 0);


// Simply runs a loop while or until some condition is true
#define SPIN_WHILE(X) while((X))
#define SPIN_UNTIL(X) while(!(X))
#define DAWDLE(Y) for (unsigned int X = 0; X < Y; X++){}

// Runs a loop while or until some condition is true and increments 
// a counter which is useful when debugging to see the number of actual iterations.
#define COUNT_WHILE(X,Y) (*Y)=0;while((X))(*Y)++;
#define COUNT_UNTIL(X,Y) (*Y)=0;while(!(X))(*Y)++;

#define WAIT_FOR(T) {while (T.SR.UIF == 0); T.SR.UIF = 0;}


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


#define MODER(X) MODER_ ## X

#define MODER_INPUT 0
#define MODER_GENERAL 1
#define MODER_ALTERNATE 2
#define MODER_ANALOG 3


// This is helpful but only useable of the X is constant.
#define MODERBIT(Y) MODER_ ## Y
// e.g. 	ahb1_ptr->GPIO_D.MODER.MODERBIT(12)  = MODER(GENERAL);

static AHB1_Bus_ptr ahb1_ptr;
static APB1_Bus_ptr apb1_ptr;
static SYST_Regset_ptr syst_ptr;
static SCB_Regset_ptr scb_ptr;

static int count = 0;

void InitStaticPointers()
{
	ahb1_ptr = (AHB1_Bus_ptr)(0x40020000);
	apb1_ptr = (APB1_Bus_ptr)(0x40000000);
	syst_ptr = (SYST_Regset_ptr)(0xE000E010);
	scb_ptr = (SCB_Regset_ptr)(0xE000ED00);
}

void SysTick_Handler(void)
{
	count++;
}


// STM32F407VG

void Page_374(void);
void BitfieldExampleA(void);
void SetupSystemClock(void);
void SetupSysTick();

int main(void)
{
	InitStaticPointers();
	
	SetupSysTick();
	
	BitfieldExampleA();
}

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
	
	ahb1_ptr->RCC.AHB1ENR.GPIOA_EN = 1;
	ahb1_ptr->RCC.AHB1ENR.GPIOD_EN = 1;

	// Setup the GPIO pins
	
	ahb1_ptr->GPIO_D.MODER.MODER_12 = MODER(GENERAL);
	ahb1_ptr->GPIO_D.OTYPER.OT_12 = 0;
	ahb1_ptr->GPIO_D.SPEEDR.SPEED_12 = SPEEDR(LOW);
	
	ahb1_ptr->GPIO_D.MODER.MODER_13 = MODER(GENERAL);
	ahb1_ptr->GPIO_D.OTYPER.OT_13 = 0;
	ahb1_ptr->GPIO_D.SPEEDR.SPEED_13 = SPEEDR(LOW);
	
	ahb1_ptr->GPIO_D.MODER.MODER_14 = MODER(GENERAL);
	ahb1_ptr->GPIO_D.OTYPER.OT_14 = 0;
	ahb1_ptr->GPIO_D.SPEEDR.SPEED_14 = SPEEDR(LOW);
	
	ahb1_ptr->GPIO_D.MODER.MODER_15 = MODER(GENERAL);
	ahb1_ptr->GPIO_D.OTYPER.OT_15 = 0;
	ahb1_ptr->GPIO_D.SPEEDR.SPEED_15 = SPEEDR(LOW);
	
	// Setup TIMER2 approx 1 Hz
	
	ahb1_ptr->RCC.APB1ENR.TIM2_EN = 1;
	apb1_ptr->TIM2.PSC.PSC = 1600 - 1;
	apb1_ptr->TIM2.ARR.ARRH = 0;
	apb1_ptr->TIM2.ARR.ARRL = 10000 - 1;
	apb1_ptr->TIM2.CNT.CNT = 0;
	apb1_ptr->TIM2.CR1.CEN = 1;
	
	// Loop forever and toggle the four LEDs
	
	while (1)
	{
		// The "act" of writing (rather than the value being written) 
		// sets/resets the bit when using the BSSR register.
		
		ahb1_ptr->GPIO_D.BSRR.BS_12 = 1; 
		WAIT_FOR(apb1_ptr->TIM2);
		ahb1_ptr->GPIO_D.BSRR.BS_13 = 1; 
		WAIT_FOR(apb1_ptr->TIM2);
		ahb1_ptr->GPIO_D.BSRR.BS_14 = 1; 
		WAIT_FOR(apb1_ptr->TIM2);
		ahb1_ptr->GPIO_D.BSRR.BS_15 = 1; 
		WAIT_FOR(apb1_ptr->TIM2);
		ahb1_ptr->GPIO_D.BSRR.BR_15 = 1; 
		WAIT_FOR(apb1_ptr->TIM2);
		ahb1_ptr->GPIO_D.BSRR.BR_14 = 1; 
		WAIT_FOR(apb1_ptr->TIM2);
		ahb1_ptr->GPIO_D.BSRR.BR_13 = 1; 
		WAIT_FOR(apb1_ptr->TIM2);
		ahb1_ptr->GPIO_D.BSRR.BR_12 = 1; 
		WAIT_FOR(apb1_ptr->TIM2);
	}
}



void SetupSystemClock()
{
	uint32_t spinner = 0;
	
	
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
	
	COUNT_UNTIL(ahb1_ptr->RCC.CR.HSE_RDY, &spinner);

	//	RCC->CFGR &=  ~0x00000003;
	//	RCC->PLLCFGR = 0x00402D04;
	//	RCC->CR |=     0x01000000;
	
	ahb1_ptr->RCC.CFGR.SW = 0;
	
	ahb1_ptr->RCC.PLLCFGR.PLL_M = 4;
	ahb1_ptr->RCC.PLLCFGR.PLL_N = 180;
	ahb1_ptr->RCC.PLLCFGR.PLL_SRC = 1;
	ahb1_ptr->RCC.CR.PLL_ON = 1;
	
	COUNT_UNTIL(ahb1_ptr->RCC.CR.PLL_RDY, &spinner);
	
	// FLASH->ACR = 0x0705;
	
	ahb1_ptr->FLASH.ACR.LATENCY = 5;
	ahb1_ptr->FLASH.ACR.PRFTEN = 1;
	ahb1_ptr->FLASH.ACR.ICEN = 1;
	ahb1_ptr->FLASH.ACR.DCEN = 1;
	
	//	RCC->CFGR &= ~0x000000F0;
	//	RCC->CFGR |=  0x00000002;

	ahb1_ptr->RCC.CFGR.HPRE = 0;
	ahb1_ptr->RCC.CFGR.SW = SW(PLL);
	
	COUNT_UNTIL(ahb1_ptr->RCC.CFGR.SWS == SWS(PLL), &spinner);

}

void SetupSysTick()
{

	SCB_AIRCR_Reg aircr;
	
	syst_ptr->CTRL.ENABLE = 0;
	
	// Must be written a single 32 bit write.
	
	aircr = scb_ptr->AIRCR;
	aircr.VECTKEY = SCB_AIRCR_VECTKEY;
	aircr.PRIGROUP = 3;
	scb_ptr->AIRCR = aircr;
	
	syst_ptr->LOAD.ALLBITS = 16000;
	
	scb_ptr->SHPR.PRI_15 = 15; // NVIC_SetPriority
	
	syst_ptr->VAL.ALLBITS = 0;
	
	syst_ptr->CTRL.TICKINT = 1;
	syst_ptr->CTRL.CLKSOURCE = 1;
	syst_ptr->CTRL.ENABLE = 1;
}