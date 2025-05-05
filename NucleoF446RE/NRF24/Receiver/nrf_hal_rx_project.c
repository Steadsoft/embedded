#include <stdatomic.h>
#include <stdbool.h>
#include <malloc.h>
#include <stm32f4xx_hal.h>
#include <nrf24_hal_support.library.h>
#include <nrf24_package.library.h>

#define SPI_CS GPIO_PIN_4
#define NRF_CE GPIO_PIN_1


// SEE: http://blog.gorski.pm/stm32-unique-id

#ifdef __cplusplus
extern "C"
#endif
	
void SysTick_Handler(void)
{
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}

int faults = 0;

static void fault_handler(NrfDevice_ptr device_ptr, NrfErrorCode code);
void pulse_led(uint32_t interval);
void board_led_init(void);

NrfDevice device = { 0 }; 

int main(void)
{
	NrfSpiSetup spi_settings = NRF_SPI_NUCLEO_F446RE;
	NrfAuxSetup aux_settings = NRF_AUX_NUCLEO_F446RE;
	NrfReg_STATUS status;
	uint8_t this_boards_address[5];
	uint8_t ack_address[5] = { 0x33, 0x33, 0x33, 0x33, 0x33 };
	uint8_t buffer[32];
	NrfReg_ALL_REGISTERS all = { 0 };
	uint8_t payload_size = 8;
	
	HAL_Init();
	
	board_led_init();
	
	nrf24_package.Action.GetDefaultAddress(this_boards_address);
	
	/// Perform all hardware related initialization before doing anything else to the device
	
	nrf24_hal_support.ConfigureHardware(&device, &spi_settings, &aux_settings, fault_handler); 
	
	/// Force all registers into their hardware reset state and set initiall values
	
	nrf24_package.Action.ResetDevice(&device);
	nrf24_package.Action.InitializeDevice(&device);
	nrf24_package.Action.ConfigureRadio(&device, CHANNEL(9), HIGH_POWER, MED_RATE, false);
	nrf24_package.Action.ClearInterruptFlags(&device, true, true, true); // clear all three flags
	nrf24_package.Action.MaskInterrupts(&device, 0, 1, 1);
	nrf24_package.Action.SetPipeState(&device, PIPE(0), true);
	nrf24_package.Action.SetReceiveMode(&device);
	nrf24_package.Action.SetPayloadSize(&device, PIPE(0), payload_size);
	nrf24_package.Action.SetReceiveAddressLong(&device, this_boards_address, PIPE(0));
	nrf24_package.Action.SetAutoAck(&device, PIPE(0), true);

	/// Power up the device.
	
	nrf24_package.Action.PowerUpDevice(&device);
	
	nrf24_package.Action.DumpRegisters(&device);

	
	while (1)
	{
		nrf24_package.Action.WaitForRxInterrupt(&device, -1);
		nrf24_package.Command.R_RX_PAYLOAD(&device, buffer, payload_size, &status);
		pulse_led(1);
	}

	return(0);
}

void EXTI0_IRQHandler(void)
{
	NrfReg_STATUS status;
	
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
	
	nrf24_package.Read.STATUS(&device, &status);
	
	if (status.RX_DR)
	{
		status.TX_DS = 0;
		status.MAX_RT = 0;
		nrf24_package.Write.STATUS(&device, status, &status);
		nrf24_package.Action.ConfirmRxInterrupt(&device);
	}
} 

void pulse_led(uint32_t interval)
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
	HAL_Delay(interval);	
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
}

void board_led_init(void)
{
	// Enable the GPIOA clock
	__HAL_RCC_GPIOA_CLK_ENABLE();

	// Define a GPIO_InitTypeDef structure for configuration
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	// Configure pin 5 as output
	GPIO_InitStruct.Pin = GPIO_PIN_5;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP; // Push-pull output
	GPIO_InitStruct.Pull = GPIO_NOPULL; // No pull-up or pull-down resistor
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW; // Low frequency for LED

	// Initialize the GPIOA pin
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

static void fault_handler(NrfDevice_ptr device_ptr, NrfErrorCode code)
{
	faults++;
}

void __attribute__((weak)) ApplicationFaultHandler(char * LibName, char * LibMessage)
{
	faults++;
}

