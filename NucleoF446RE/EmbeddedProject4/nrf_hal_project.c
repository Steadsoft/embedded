#include <stm32f4xx_hal.h>
#include <nrf24_package.macros.h>
#include <nrf24_package.library.h>
#include <nrf24_hal_support.library.h>


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


int interrupt_count = 0;

void initialize_nrf24_device(NrfSpiDevice_ptr device_ptr);
void TM_NRF24L01_PowerUpRx(NrfSpiDevice_ptr device_ptr);
int get_board_id();
void sleep_100_uS();

void TM_NRF24L01_PowerUpTx(NrfSpiDevice_ptr device_ptr);

void TM_NRF24L01_Transmit(NrfSpiDevice_ptr device_ptr, uint8_t * data, uint8_t len);


void sleep_100_uS()
{
	for (int X = 0; X < 122; X++)
	{
		;
	}
}

int main(void)
{
	NrfReg_ALL_REGISTERS everything_before = { 0 };
	NrfReg_ALL_REGISTERS everything_after = { 0 };
	SPI_HandleTypeDef spi = { 0 }; 
	NrfSpiDevice device = { 0 }; 
	NrfIoDescriptor descriptor = { 0 };
	NrfReg_CONFIG cfg = { 0 };
	NrfReg_SETUP_AW aw = { 0 };
	NrfReg_STATUS status;
	uint32_t state;
	uint8_t buffer[32];
	
	HAL_Init();
	
	for (int X = 0; X < 32; X++)
	{
		buffer[X] = 0xAA;
	}
	
	HAL_Delay(1000);
	
	int board = get_board_id();
	
	// Perform all IO related initialization
	
	nrf24_hal_support.init_spi(&spi);
	nrf24_hal_support.init_control_pins();
	nrf24_hal_support.init_device(&spi, &device, &descriptor);
	
	// Snapshot all regsiters
	
	nrf24_package.GetRegister.ALL_REGISTERS(&device, &everything_before, &status);
	
	// Force all register into their hardware reset state.
	
	nrf24_package.DeviceControl.PowerOnReset(&device);
	
	// Snapshot all regsiters
	
	nrf24_package.GetRegister.ALL_REGISTERS(&device, &everything_after, &status);
		
	initialize_nrf24_device(&device);
	
	while (1)
	{
		HAL_Delay(50);
		
		TM_NRF24L01_Transmit(&device, buffer, 32);
		
		sleep_100_uS();
		
		nrf24_package.GetRegister.STATUS(&device, &status);
		
		while (status.TX_DS == 0 || status.MAX_RT == 1)
		{
			nrf24_package.GetRegister.STATUS(&device, &status);
		}
		
	}
	
	// Slowly flash the Nucleo's LED to indicate that command sending is over.

	nrf24_hal_support.flash_led_forever(1000);

	return(0);
}

void TM_NRF24L01_Transmit(NrfSpiDevice_ptr device_ptr, uint8_t * data, uint8_t len)
{
	NrfReg_STATUS status;
	nrf24_hal_support.spi_ce_lo(device_ptr->io_ptr);

	TM_NRF24L01_PowerUpTx(device_ptr);
	
	nrf24_package.DeviceControl.FlushTxFifo(device_ptr, &status);
	
	nrf24_package.DeviceControl.WriteTxPayload(device_ptr, data, len, &status);
	
	nrf24_hal_support.spi_ce_hi(device_ptr->io_ptr);
}

void initialize_nrf24_device(NrfSpiDevice_ptr device_ptr)
{
	NrfReg_STATUS status;
	NrfReg_RX_PW rx_pw = { 0 };
	NrfReg_CONFIG configuration = { 0 };
	NrfReg_RF_SETUP rf_setup = { 0 };
	NrfReg_EN_AA en_aa = { 0 };
	NrfReg_EN_RXADDR en_rxaddr = { 0 };
	NrfReg_SETUP_RETR setup_retr = { 0 };
	NrfReg_DYNPD dynpd = { 0 };
	
	// Set channel
	
	/* Set pipeline to max possible 32 bytes */
	
	rx_pw.RX_PW_LEN = 32;
	
	nrf24_package.SetRegister.RX_PW(device_ptr, rx_pw, 0, &status);
	nrf24_package.SetRegister.RX_PW(device_ptr, rx_pw, 1, &status);
	nrf24_package.SetRegister.RX_PW(device_ptr, rx_pw, 2, &status);
	nrf24_package.SetRegister.RX_PW(device_ptr, rx_pw, 3, &status);
	nrf24_package.SetRegister.RX_PW(device_ptr, rx_pw, 4, &status);
	nrf24_package.SetRegister.RX_PW(device_ptr, rx_pw, 5, &status);

	/* Set RF settings (2mbps, output power) */
	
	rf_setup.RF_DR_HIGH = 1; // 2 Mbps
	rf_setup.RF_PWR = 3; // 0 dBm
	
	nrf24_package.SetRegister.RF_SETUP(device_ptr, rf_setup, &status);
	
	/* Enable auto-acknowledgment for all pipes */
	
//	en_aa.ENAA_P0 = 1;
//	en_aa.ENAA_P1 = 1;
//	en_aa.ENAA_P2 = 1;
//	en_aa.ENAA_P3 = 1;
//	en_aa.ENAA_P4 = 1;
//	en_aa.ENAA_P5 = 1;
	
	nrf24_package.SetRegister.EN_AA(device_ptr, en_aa, &status);
	
	/* Enable RX addresses */
	
	en_rxaddr.ERX_P0 = 1;
	en_rxaddr.ERX_P0 = 1;
	en_rxaddr.ERX_P0 = 1;
	en_rxaddr.ERX_P0 = 1;
	en_rxaddr.ERX_P0 = 1;
	en_rxaddr.ERX_P0 = 1;

	nrf24_package.SetRegister.EN_RXADDR(device_ptr, en_rxaddr, &status);
	
	/* Auto retransmit delay: 1000 (4x250) us and Up to 15 retransmit trials */
	
	setup_retr.ARC = 15;
	setup_retr.ARD = 3;
	
	nrf24_package.SetRegister.SETUP_RETR(device_ptr, setup_retr, &status);
	
	/* Dynamic length configurations: No dynamic length */
	
	nrf24_package.SetRegister.DYNPD(device_ptr, dynpd, &status);
	
	// Clear FIFOs
	
	nrf24_package.DeviceControl.FlushRxFifo(device_ptr, &status);
	nrf24_package.DeviceControl.FlushTxFifo(device_ptr, &status);
	
	// Clear interrupts
	
	NrfReg_STATUS int_status;

	int_status.RX_DR = 1;
	int_status.TX_DS = 1;
	int_status.MAX_RT = 1;

	nrf24_package.SetRegister.STATUS(device_ptr, status, &status);
	
	TM_NRF24L01_PowerUpRx(device_ptr);
	
	
	
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
	
	config.PWR_UP = 1;
	config.PRIM_RX = 1;
	
	nrf24_package.UpdateRegister.CONFIG(device_ptr, config, config_mask, &status);

	nrf24_hal_support.spi_ce_hi(device_ptr->io_ptr);
}

void 
TM_NRF24L01_PowerUpTx(NrfSpiDevice_ptr device_ptr)	
{
	NrfReg_STATUS status;
	NrfReg_CONFIG config = { 0 };
	NrfReg_CONFIG config_mask = { 0 };
	
	// Clear interrupts
	
	status.RX_DR = 1;
	status.TX_DS = 1;
	status.MAX_RT = 1;
	
	nrf24_package.SetRegister.STATUS(device_ptr, status, &status);
	
	// Set mode to TX

	config_mask.PWR_UP = 1;
	config_mask.PRIM_RX = 1;
	
	config.PWR_UP = 1;
	config.PRIM_RX = 0;
	
	nrf24_package.UpdateRegister.CONFIG(device_ptr, config, config_mask, &status);
}

void EXTI0_IRQHandler(void)
{
	interrupt_count++;
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
} 