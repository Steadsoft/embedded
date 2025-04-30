#include <stdatomic.h>
#include <stdbool.h>
#include <malloc.h>
#include <stm32f4xx_hal.h>
#include <nrf24_hal_support.library.h>
#include <nrf24_package.library.h>

#define SPI_CS GPIO_PIN_4
#define NRF_CE GPIO_PIN_1
#define NRF_IR GPIO_PIN_0

// SEE: http://blog.gorski.pm/stm32-unique-id

#ifdef __cplusplus
extern "C"
#endif
	
#define elif else if	
	
void SysTick_Handler(void)
{
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}

int faults = 0;


static void fault_handler(NrfDevice_ptr device_ptr, NrfErrorCode code);

void EXTI0_IRQPostHandler(NrfDevice_ptr device_ptr);


NrfDevice device = { 0 }; 

int arr[4][3] = { { 2, 3, 1 }, { 19, 12, 7 }, { 10, 9, 8 }, { 3, 11, 5 } };

int msgs_tx = 0;

int main(void)
{
	NrfSpiSetup spi_setup = { 0 };
	uint8_t buffer[32] = { 0 };
	uint8_t * payload = "I AM A MESSAGE WITH LENGTH OF 32";

	uint8_t address[] = { 0xE7, 0xE7, 0xE7, 0xE7, 0xE7}; // this is just the default system reset value for the TX_ADDR reg
	
	for (int X = 0; X < 32; X++) buffer[X] = 0xAA + X;
	
	HAL_Init();
		
	/// Perform all IO related initialization
	
	spi_setup.miso_pin = PA6;
	spi_setup.mosi_pin = PA7;
	spi_setup.sck_pin  = PA5;
	spi_setup.pin_alt  = GPIO_AF5_SPI1;
	spi_setup.spi      = SPI1;
	
	nrf24_hal_support.ConfigureDevice(&spi_setup, TIM1, PA0, EXTI0_IRQn, PA1, PA4, &device, fault_handler); 
	
	/// Force all registers into their hardware reset state.
	
	nrf24_package.Action.ResetDevice(&device);
	nrf24_package.Action.InitializeDevice(&device);
	nrf24_package.Action.PowerUpDevice(&device);

	while (1)
	{
		nrf24_package.Action.ConfigureTransmitter(&device, address, 110, LOW_POWER, MIN_RATE);
		nrf24_package.Action.SendPayload(&device, payload, 32); // Literature indicates that reducing the size of the payload can improve range.
		nrf24_package.Action.WaitForTxInterrupt(&device,2000);		
		
		HAL_Delay(250);
		
		nrf24_package.Action.ConfigureTransmitter(&device, address, 100, LOW_POWER, MIN_RATE);
		nrf24_package.Action.SendPayload(&device, payload, 32); // Literature indicates that reducing the size of the payload can improve range.
		nrf24_package.Action.WaitForTxInterrupt(&device,2000);		
		
		HAL_Delay(250);
	}

	return(0);
}


void EXTI0_IRQHandler(void)
{
	NrfReg_STATUS status_irq;
	
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
	
	nrf24_package.Read.STATUS(&device, &status_irq); // sends a NOP to read status

	// If the interrupt for TX complete, clear just that bit
	
	if (status_irq.TX_DS)
	{
		status_irq.RX_DR = 0;
		status_irq.MAX_RT = 0;
		nrf24_package.Update.STATUS(&device, status_irq, status_irq);
		nrf24_package.Action.ConfirmTxInterrupt(&device);
	}
} 

static void fault_handler(NrfDevice_ptr device_ptr, NrfErrorCode code)
{
	faults++;
}

void __attribute__((weak)) ApplicationFaultHandler(char * LibName, char * LibMessage)
{
	faults++;
}