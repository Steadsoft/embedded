#include <stdatomic.h>
#include <stdbool.h>
#include <malloc.h>
#include <stm32f4xx_hal.h>
#include <nrf24_package.library.h>
#include <nrf24_hal_support.library.h>

#define ATOMIC_FLAG_OFF (atomic_flag){0};
# define ROUNDUP(N,ALIGN)	        (((N) +  ((ALIGN)-1)) & ~((ALIGN)-1))
//#include <cmsis_gcc.h>

// SEE: http://blog.gorski.pm/stm32-unique-id

#ifdef __cplusplus
extern "C"
#endif
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

volatile uint8_t tx_ds_irq_clear_pending = 0;
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
	NrfIoDescriptor descriptor = { 0 };
	uint32_t state = 0;
	uint8_t buffer[32] = { 0 };
	//uint8_t[4] send_polls = 0;
	
	HAL_Init();
	
	tx_ds_irq_clear_pending = 0;
	
	for (int X = 0; X < 32; X++)
	{
		buffer[X] = 0xAA;
	}
	
	HAL_Delay(1000);
	
	int board = get_board_id();
	
	/// Perform all IO related initialization
	
	nrf24_hal_support.init_spi(&spi); /// currently hard coded to use SPI1
	nrf24_hal_support.init_control_pins(); /// currently hard coded to use GPIOA
	nrf24_hal_support.init_device(&spi, &device, &descriptor); //// currently hard coded to use GPIOA
	

	/// Snapshot all regsiters
	
	nrf24_package.GetRegister.ALL_REGISTERS(&device, &everything_before, &status);
	
	/// Force all register into their hardware reset state.
	
	nrf24_package.DeviceControl.PowerOnReset(&device);
	
	/// Snapshot all regsiters
	
	nrf24_package.GetRegister.ALL_REGISTERS(&device, &everything_after, &status);
		
	nrf24_package.DeviceControl.Initialize(&device);
	
	nrf24_package.DeviceControl.PowerUpTx(&device);

	nrf24_package.GetRegister.STATUS(&device, &status);
	
	status_irq = nrf24_package.EmptyRegister.STATUS;
	status_mask_irq = nrf24_package.EmptyRegister.STATUS;
	status_mask_irq.TX_DS = 1; // Update TX_DS set it to OFF

	while (1)
	{
		for (int X = 0; X < 610; X++)
		{
			if (tx_ds_irq_clear_pending)
				break;
		}

		if (tx_ds_irq_clear_pending)
		{
			EXTI0_IRQPostHandler(&device);
		}
		
		TM_NRF24L01_Transmit(&device, buffer, 32);
		
		HAL_Delay(10);

	}

	return(0);
}

void TM_NRF24L01_Transmit(NrfSpiDevice_ptr device_ptr, uint8_t * data, uint8_t len)
{
	NrfReg_STATUS status;
	
	nrf24_package.DeviceControl.FlushTxFifo(device_ptr, &status);
	
	nrf24_package.DeviceControl.WriteTxPayload(device_ptr, data, len, &status);
	
	// We must now pulse CE high for > 10 uS for RF transmision to begin.
	
	nrf24_hal_support.spi_ce_hi(device_ptr->io_ptr);
	spin_20_uS(); 
	nrf24_hal_support.spi_ce_lo(device_ptr->io_ptr);
	sent_messages_count++;
}

void TM_NRF24L01_PowerUpRx(NrfSpiDevice_ptr device_ptr)
{
	NrfReg_STATUS status;
	NrfReg_CONFIG config = { 0 };
	NrfReg_CONFIG config_mask = { 0 };
	
	nrf24_hal_support.spi_ce_lo(device_ptr->io_ptr);
	
	nrf24_package.DeviceControl.FlushRxFifo(device_ptr, &status);
	
	status.RX_DR = 1;
	status.TX_DS = 1;
	status.MAX_RT = 1;
	
	nrf24_package.SetRegister.STATUS(device_ptr, status, &status);
	
	config_mask.PWR_UP = 1;
	config_mask.PRIM_RX = 1;
	config_mask.MASK_MAX_RT = 1;
	config_mask.MASK_RX_DR = 1;
	config_mask.MASK_TX_DS = 1;

	config.PWR_UP = 1;
	config.PRIM_RX = 1;
	
	config.MASK_MAX_RT = 1;
	config.MASK_RX_DR = 1;
	config.MASK_TX_DS = 0; // Data sent interrupt will be generated (not masked, not inhibited)
	
	nrf24_package.UpdateRegister.CONFIG(device_ptr, config, config_mask, &status);

	nrf24_hal_support.spi_ce_hi(device_ptr->io_ptr);
}


void EXTI0_IRQHandler(void)
{
	tx_ds_irq_clear_pending = 1;
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
} 

void EXTI0_IRQPostHandler(NrfSpiDevice_ptr device_ptr)
{
	NrfReg_STATUS status_irq;
	
	tx_ds_interrupt_count++;
	
	nrf24_package.GetRegister.STATUS(device_ptr, &status_irq);

	if (status_irq.TX_DS)
	{
		nrf24_package.SetRegister.STATUS(device_ptr, status_irq, &status_irq);
	}
	
	tx_ds_irq_clear_pending = 0;
}


