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
uint32_t  getUniqueID();

NrfDevice device = { 0 }; 

int main(void)
{
	NrfSpiSetup spi_setup = NUCLEO_F446RE;
	NrfReg_STATUS status;
	uint8_t this_board[5];
	uint8_t buffer[32];
	NrfReg_ALL_REGISTERS all = { 0 };
	uint32_t id;

	HAL_Init();
	
	board_led_init();
	
	/// Perform all hardware related initialization before doing anything else to the device
	
	nrf24_hal_support.ConfigureHardware(&spi_setup, TIM1, PA0, EXTI0_IRQn, PA1, PB12, &device, fault_handler); 
	
	/// Force all registers into their hardware reset state.
	
	nrf24_package.Action.ResetDevice(&device);
	nrf24_package.Action.InitializeDevice(&device);
	
	/// Set the RF related settings
	
	nrf24_package.Action.ConfigureRadio(&device, 45, HIGH_POWER, MED_RATE, false);
	
	/// Set receiver oriented settings
	
	nrf24_package.Action.GetDefaultAddress(this_board);
	
	nrf24_package.Action.ConfigureReceiver(&device, this_board, 0, false, 8); 
	
	/// Power up the device.
	
	nrf24_package.Action.PowerUpDevice(&device);
	
	nrf24_package.Read.ALL_REGISTERS(&device, &all, &status);

	while (1)
	{
		nrf24_package.Action.WaitForRxInterrupt(&device, -1);
		nrf24_package.Command.R_RX_PAYLOAD(&device, buffer, 8, &status);
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

uint32_t getUniqueID() {
	uint32_t id1 = *(uint32_t*)0x1FFF7A10; // First 32 bits
	uint32_t id2 = *(uint32_t*)0x1FFF7A14; // Second 32 bits
	uint32_t id3 = *(uint32_t*)0x1FFF7A18; // Last 32 bits
	
	return id2;

}