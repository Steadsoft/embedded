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
volatile uint32_t sent_messages_count = 0;

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
	//uint8_t[4] send_polls = 0;
	int spins = 0;
	
	HAL_Init();
	


	tx_completed = 0;
	
	short Y = 0;
	
	for (int X = 0; X < 32; X++)
	{
		buffer[X] = 0xAA + Y;
		Y++;
	}
	
	HAL_Delay(1000);
	
	int board = get_board_id();
	
	/// Perform all IO related initialization
	
	nrf24_hal_support.Configure(SPI1_BASE, NRF_IR, EXTI0_IRQn, NRF_CE, SPI_CS, &device, fault_handler); 
	
	/// Force all register into their hardware reset state.
	
	nrf24_package.Action.PowerOnReset(&device);
		
	nrf24_package.Action.Initialize(&device);
	
	while (1)
	{
		nrf24_package.Action.PulseCE(&device);
		
		HAL_Delay(1);
	}
	
	nrf24_package.Action.PowerUpTx(&device);

	while (1)
	{
		
		TM_NRF24L01_Transmit(&device, buffer, 32);
		
		spins = 0;
		
		while (tx_completed == 0)
		{
			spins++;
		}
		
		HAL_Delay(1);
	}

	return(0);
}

void TM_NRF24L01_Transmit(NrfSpiDevice_ptr device_ptr, uint8_t * data, uint8_t len)
{
	NrfReg_STATUS status;
	
	tx_completed = 0;
	
	nrf24_package.Command.W_TX_PAYLOAD(device_ptr, data, len, &status);
	
	// We must now pulse CE high for > 10 uS for RF transmision to begin. See Page 23 of chip manual.
	
	nrf24_hal_support.Activate(device_ptr);
	
	//__HAL_TIM_SET_COUNTER
	
	spin_100_uS(); 
	nrf24_hal_support.Deactivate(device_ptr);
	sent_messages_count++;
}

void TM_NRF24L01_PowerUpRx(NrfSpiDevice_ptr device_ptr)
{
	NrfReg_STATUS status;
	NrfReg_CONFIG config = { 0 };
	NrfReg_CONFIG config_mask = { 0 };
	
	nrf24_hal_support.Deactivate(device_ptr);
	
	nrf24_package.Command.FLUSH_RX(device_ptr, &status);
	
	// Clear all three interrupt flags in case any are on
	
	status.RX_DR = 1;
	status.TX_DS = 1;
	status.MAX_RT = 1;
	
	nrf24_package.Write.STATUS(device_ptr, status, &status);
	
	// Indicate which config bits to update
	
	config_mask.PWR_UP = 1;
	config_mask.PRIM_RX = 1;
	config_mask.MASK_MAX_RT = 1;
	config_mask.MASK_RX_DR = 1;
	config_mask.MASK_TX_DS = 1;

	// Set the config bits
	
	config.PWR_UP = 1; // power up the device, this will cause the device to eneter Standby-1 mode
	config.PRIM_RX = 0; // set to TX mode
	config.MASK_MAX_RT = 1; // disable this interrupt
	config.MASK_RX_DR = 1;  // disable this interrupt
	config.MASK_TX_DS = 0;  // Data sent interrupt will be generated (not masked, not inhibited)
	
	nrf24_package.Update.CONFIG(device_ptr, config, config_mask, &status);

	nrf24_hal_support.Activate(device_ptr);
}


void EXTI0_IRQHandler(void)
{
	NrfReg_STATUS status_irq;
	
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
	
	tx_ds_interrupt_count++;
	
	nrf24_package.Read.STATUS(&device, &status_irq);

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


