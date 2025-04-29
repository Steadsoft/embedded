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
void GPIOA_Pin5_Init(void);

NrfDevice device = { 0 }; 

int main(void)
{
	NrfReg_STATUS status;
	NrfSpiSetup spi_setup = { 0 };
	uint8_t address[] = { 0xE7, 0xE7, 0xE7, 0xE7, 0xE7 }; // this is just the default system reset value for the RX_ADDR_P0 reg
	uint8_t buffer[32];

	HAL_Init();
	
	GPIOA_Pin5_Init();
	
	// Perform all IO related initialization
	
	spi_setup.sck_pin  = PB13;
	spi_setup.miso_pin = PB14;
	spi_setup.mosi_pin = PB15;
	spi_setup.pin_alt  = GPIO_AF5_SPI2;
	spi_setup.spi      = SPI2;;
	
	nrf24_hal_support.ConfigureDevice(&spi_setup, TIM1, PA0, EXTI0_IRQn, PA1, PB12, &device, fault_handler); 
	
	// Force all register into their hardware reset state.
	
	nrf24_package.Action.ResetDevice(&device);
		
	nrf24_package.Action.InitializeDevice(&device);
	
	nrf24_package.Action.ConfigureReceiver(&device, address, 1, 100, 32, MIN_RATE); 
	
	while (1)
	{
		nrf24_package.Action.WaitForRxInterrupt(&device, -1);
		nrf24_package.Command.R_RX_PAYLOAD(&device, buffer, 32, &status);
		pulse_led(10);
	}

	return(0);
}

void ApplicationFaultHandler(char * LibName)
{
	uint8_t data;
	data = 1;
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

void GPIOA_Pin5_Init(void)
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