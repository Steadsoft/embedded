#include <stdatomic.h>
#include <stdbool.h>
#include <malloc.h>
#include <stm32f4xx_hal.h>
#include <nrf24_hal_support.library.h>
#include <nrf24_package.library.h>

#define ATOMIC_FLAG_OFF (atomic_flag){0};
# define ROUNDUP(N,ALIGN)	        (((N) +  ((ALIGN)-1)) & ~((ALIGN)-1))
//#include <cmsis_gcc.h>

// SEE: http://blog.gorski.pm/stm32-unique-id

#ifdef __cplusplus
extern "C"
#endif
	
	
#define SPI_CS GPIO_PIN_4
#define NRF_CE GPIO_PIN_1
#define NRF_IR GPIO_PIN_0
	
#define elif else if	
	
void SysTick_Handler(void)
{
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}
typedef struct
{
	unsigned long fields[3];
} BoardId;



volatile uint32_t tx_ds_interrupt_count = 0;
volatile uint32_t transmit_count = 0;

volatile uint8_t tx_completed = 0;

static void fault_handler(NrfSpiDevice_ptr device_ptr, NrfErrorCode code);


void initialize_nrf24_device(NrfSpiDevice_ptr device_ptr);
void TM_NRF24L01_PowerUpRx(NrfSpiDevice_ptr device_ptr);
int get_board_id();
void spin_100_uS();
void spin_20_uS();
void spin_500_uS();

void TM_NRF24L01_PowerUpTx(NrfSpiDevice_ptr device_ptr);

void TM_NRF24L01_Transmit(NrfSpiDevice_ptr device_ptr, uint8_t * data, uint8_t len);
void EXTI0_IRQPostHandler(NrfSpiDevice_ptr device_ptr);

void spin_20_uS()
{
	for (int X = 0; X < 25; X++)
	{
		;
	}
}

void spin_100_uS()
{
	for (int X = 0; X < 122; X++)
	{
		;
	}
}

void spin_500_uS()
{
	for (int X = 0; X < 610; X++)
	{
		;
	}
}

NrfSpiDevice device = { 0 }; 

int arr[4][3] = { { 2, 3, 1 }, { 19, 12, 7 }, { 10, 9, 8 }, { 3, 11, 5 } };

int msgs_tx = 0;

int main(void)
{
	NrfReg_ALL_REGISTERS everything_before = { 0 };
	NrfReg_ALL_REGISTERS everything_after = { 0 };
	NrfReg_CONFIG cfg = { 0 };
	NrfReg_SETUP_AW aw = { 0 };
	NrfReg_STATUS status;
	NrfReg_STATUS status_mask_irq = { 0 };
	NrfReg_STATUS status_irq = { 0 };
	SPI_HandleTypeDef spi = { 0 }; 
	uint32_t state = 0;
	uint8_t buffer[32] = { 0 };
	uint8_t tx_addr[] = { 0xE7, 0xE7, 0xE7, 0xE7, 0xE7}; // this is just the default system reset value for the TX_ADDR reg

	HAL_Init();
	
	for (int X = 0; X < 32; X++) buffer[X] = 0xAA + X;
	
	/// Perform all IO related initialization
	
	nrf24_hal_support.Configure(SPI1, TIM1, NRF_IR, EXTI0_IRQn, NRF_CE, SPI_CS, &device, fault_handler); 
	
	/// Force all register into their hardware reset state.
	
	nrf24_package.Action.PowerOnReset(&device);
		
	nrf24_package.Action.Initialize(&device);
	
	nrf24_package.Action.PowerUpTx(&device, tx_addr, 100);
	

	while (1)
	{
		nrf24_package.Action.SendPayload(&device, buffer, 32);
		
		HAL_Delay(10);
	}

	return(0);
}



void EXTI0_IRQHandler(void)
{
	NrfReg_STATUS status_irq;
	
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
	
	tx_ds_interrupt_count++;
	
	nrf24_package.Read.STATUS(&device, &status_irq); // sends a NOP to read status

	// If the interrupt for TX complete, clear just that bit
	
	if (status_irq.TX_DS)
	{
		status_irq.RX_DR = 0;
		status_irq.MAX_RT = 0;
		nrf24_package.Write.STATUS(&device, status_irq, &status_irq);
		tx_completed = 1;
	}
} 


static void fault_handler(NrfSpiDevice_ptr device_ptr, NrfErrorCode code)
{
	;
}


