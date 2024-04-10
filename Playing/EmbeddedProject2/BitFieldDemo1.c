#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <regtypes.h>
//#include <statics.h>
#include <regdefs.h>
#include <sysdefs.h>
#include <startup.library.h>

//int lock = 0;
//int unlocked = 0;
//int locked = 1;
//	
//char flag = __atomic_compare_exchange(&lock, &unlocked, &locked, 0, 0, 0);

#define RAM_START         (0x20000000u)
#define RAM_SIZE          (112 * 1024) // 112 KB
#define MAIN_STACK        (RAM_START + RAM_SIZE)
#define TASK_STACK_SIZE   (1024u)
#define TASK_NUMBER_MAX   (16)


static int count = 0;

void SetupSysTick();
void Page_374(void);
void BitfieldExampleA(void);
void SetupSystemClock(void);

//int main(void)
//{
//	//SetupSysTick();
//	BitfieldExampleA();
//}


//void SysTick_Handler(void)
//{
//	count++;
//}
//

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
	bus.scb_ptr->SHPR.PRI_15 = 15; // NVIC_SetPriority
	
	bus.syst_ptr->LOAD.ALLBITS = 16000;
	bus.syst_ptr->VAL.ALLBITS = 0;
	bus.syst_ptr->CTRL.TICKINT = 1;
	bus.syst_ptr->CTRL.CLKSOURCE = 1;
	bus.syst_ptr->CTRL.ENABLE = 1;
}

/* Debug Exception and Monitor Control Register base address */
#define DEMCR                 *((volatile uint32_t*) 0xE000EDFCu)
/* ITM register addresses */
#define ITM_STIMULUS_PORT0    *((volatile uint32_t*) 0xE0000000u)
#define ITM_TRACE_EN          *((volatile uint32_t*) 0xE0000E00u)
/* System Handler control and state register */
#define SHCSR                 *((volatile uint32_t*) 0xE000ED24u)
/* SysTick register address */
#define SCSR                  *((volatile uint32_t*) 0xE000E010u)
#define SRVR                  *((volatile uint32_t*) 0xE000E014u)

/* Send a char through ITM */
void ITM_SendChar(uint8_t ch) {
	// read FIFO status in bit [0]:
	while (!(ITM_STIMULUS_PORT0 & 1)) ;
	// write to ITM stimulus port0
	ITM_STIMULUS_PORT0 = ch;
}

/* Override low-level _write system call */
int _write(int file, char *ptr, int len) {
	int DataIdx;
	for (DataIdx = 0; DataIdx < len; DataIdx++) {
		ITM_SendChar(*ptr++);
	}
	return len;
}

/* RAM */
//#define RAM_START         (0x20000000u)
//#define RAM_SIZE          (128 * 1024) // 128 KB
//
///* Stacks */
//#define MAIN_STACK        (RAM_START + RAM_SIZE)
//#define TASK_NUMBER_MAX   (16)
//#define TASK_STACK_SIZE   (1024u)

uint32_t __uCurrentTaskIdx = 0;
uint32_t __puTasksPSP[TASK_NUMBER_MAX] = { 0 };

/* Scheduler */
uint32_t get_current_psp() {
	return __puTasksPSP[__uCurrentTaskIdx];
}

void save_current_psp(uint32_t psp) {
	__puTasksPSP[__uCurrentTaskIdx] = psp;
}

void select_next_task() {
	/* Round-Robin scheduler */
	__uCurrentTaskIdx++;
	// check if a task is register at current slot
	if (__uCurrentTaskIdx >= TASK_NUMBER_MAX || __puTasksPSP[__uCurrentTaskIdx] == 0) {
		__uCurrentTaskIdx = 0;
	}
}

void start_scheduler() {
	printf("Start Scheduler!\n");

	// start with the first task
	__uCurrentTaskIdx = 0;

	// prepare PSP of the first task
	__asm volatile("BL get_current_psp"); // return PSP in R0
	__asm volatile("MSR PSP, R0"); // set PSP

	// change to use PSP
	__asm volatile("MRS R0, CONTROL");
	__asm volatile("ORR R0, R0, #2"); // set bit[1] SPSEL
	__asm volatile("MSR CONTROL, R0");

	// start SysTick
	// clear and set the period
	SRVR &= ~0xFFFFFFFF;
	SRVR |= 16000 - 1; // 1000 Hz ~ 1 ms
	// enable SysTick
	SCSR |= (1 << 1); // enable SysTick Exception request
	SCSR |= (1 << 2); // select system clock
	SCSR |= (1 << 0); // start

	// Move to Unprivileged level
	__asm volatile("MRS R0, CONTROL");
	__asm volatile("ORR R0, R0, #1"); // Set bit[0] nPRIV
	__asm volatile("MSR CONTROL, R0");
	// right after here, access is limited

	// get the handler of the first task by tracing back from PSP which is at R4 slot
	void(*handler)() = (void(*))((uint32_t*)__puTasksPSP[__uCurrentTaskIdx])[14];

	// execute the handler
	handler();
}

void init_task(void(*handler)) {
	int i = 0;

	// find an empty slot
	for (; i < TASK_NUMBER_MAX; i++) {
		if (__puTasksPSP[i] == 0) break;
	}

	if (i >= TASK_NUMBER_MAX) {
		printf("Can not register a new task anymore!\n");
		return;
	}
	else {
		printf("Register a task %p at slot %i\n", handler, i);
	}

	// calculate new PSP
	uint32_t* psp = (uint32_t*)(MAIN_STACK - (i + 1)*TASK_STACK_SIZE);

	// fill dummy stack frame
	*(--psp) = 0x01000000u; // Dummy xPSR, just enable Thumb State bit;
	*(--psp) = (uint32_t) handler; // PC
	*(--psp) = 0xFFFFFFFDu; // LR with EXC_RETURN to return to Thread using PSP
	*(--psp) = 0x12121212u; // Dummy R12
	*(--psp) = 0x03030303u; // Dummy R3
	*(--psp) = 0x02020202u; // Dummy R2
	*(--psp) = 0x01010101u; // Dummy R1
	*(--psp) = 0x00000000u; // Dummy R0
	*(--psp) = 0x11111111u; // Dummy R11
	*(--psp) = 0x10101010u; // Dummy R10
	*(--psp) = 0x09090909u; // Dummy R9
	*(--psp) = 0x08080808u; // Dummy R8
	*(--psp) = 0x07070707u; // Dummy R7
	*(--psp) = 0x06060606u; // Dummy R6
	*(--psp) = 0x05050505u; // Dummy R5
	*(--psp) = 0x04040404u; // Dummy R4

	// save PSP
	__puTasksPSP[i] = (uint32_t)psp;
}

/* Context Switching run here */
//__attribute__((naked)) 
	void SysTick_Handler() {
	// save LR back to main, must do this firstly
	__asm volatile("PUSH {LR}");

	printf("****\n");

	/* Save the context of current task */

	// get current PSP
	__asm volatile("MRS R0, PSP");
	// save R4 to R11 to PSP Frame Stack
	__asm volatile("STMDB R0!, {R4-R11}"); // R0 is updated after decrement
	// save current value of PSP
	__asm volatile("BL save_current_psp"); // R0 is first argument

	/* Do scheduling */

	// select next task
	__asm volatile("BL select_next_task");

	/* Retrieve the context of next task */

	// get its past PSP value
	__asm volatile("BL get_current_psp"); // return PSP is in R0
	// retrieve R4-R11 from PSP Fram Stack
	__asm volatile("LDMIA R0!, {R4-R11}"); // R0 is updated after increment
	// update PSP
	__asm volatile("MSR PSP, R0");

	// exit
	__asm volatile("POP {LR}");
	__asm volatile("BX LR");
}

/* Fault Handlers */
void HardFault_Handler() {
	printf("Exception: HardFault_Handler\n");
	while (1) ;
}

void MemManage_Handler() {
	printf("Exception: MemManage_Handler\n");
	while (1) ;
}

void BusFault_Handler() {
	printf("Exception: BusFault_Handler\n");
	while (1) ;
}

void UsageFault_Handler() {
	printf("Exception: Usage Fault\n");
	while (1) ;
}

/* Tasks */
void task1_main(void) {
	while (1) {
		printf("1111\n");
	}
}

void task2_main(void) {
	while (1) {
		printf("2222\n");
	}
}

void task3_main(void) {
	while (1) {
		printf("3333\n");
	}
}

void task4_main(void) {
	while (1) {
		printf("4444\n");
	}
}

int main(void)
{
	// Enable TRCENA
	DEMCR |= (1 << 24);
	// Enable stimulus port 0
	ITM_TRACE_EN |= (1 << 0);

	/***************
	 * Fault traps *
	 ***************/
	// Enable Fault Handlers
	SHCSR |= (1 << 16); // Memory Fault
	SHCSR |= (1 << 17); // Bus Fault
	SHCSR |= (1 << 18); // Usage Fault

	/*************
	 * SCHEDULER *
	 *************/
	init_task(task1_main);
	init_task(task2_main);
	init_task(task3_main);
	init_task(task4_main);

	SetupSysTick();
	
	start_scheduler();

	// should never go here
	for (;;) ;
}
