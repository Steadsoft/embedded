#include <stdatomic.h>
#include <stdbool.h>
#include <malloc.h>
#include <stdio.h>
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

void pulse_led(uint32_t interval);
void board_led_init(void);

static void fault_handler(NrfDevice_ptr device_ptr, NrfErrorCode code);

void EXTI0_IRQPostHandler(NrfDevice_ptr device_ptr);


NrfDevice device = { 0 }; 

int arr[4][3] = { { 2, 3, 1 }, { 19, 12, 7 }, { 10, 9, 8 }, { 3, 11, 5 } };

int msgs_tx = 0;

int main(void)
{
	NrfSpiSetup spi_setttings = NRF_SPI_NUCLEO_F446RE;
	NrfAuxSetup aux_settings = NRF_AUX_NUCLEO_F446RE;
	NrfReg_STATUS status;
	NrfReg_RX_ADDR_LONG rx;
	uint8_t buffer[32] = { 0 };
	uint8_t * payload = "I AM A MESSAGE WITH LENGTH OF 32";
	NrfReg_ALL_REGISTERS all = { 0 };
	uint8_t radio_01[] = { 0x19, 0x51, 0x38, 0x31, 0xAA }; 
	uint8_t radio_02[] = { 0x0F, 0x50, 0x33, 0x46, 0xAA }; 
	uint8_t ack_address[5] = { 0x33, 0x33, 0x33, 0x33, 0x33 };

	uint32_t id;
	
	for (int X = 0; X < 32; X++) buffer[X] = 0xAA + X;
	
	HAL_Init();
	
	board_led_init();
		
	/// Perform all IO related initialization
	
	nrf24_hal_support.ConfigureHardware(&device, &spi_setttings, &aux_settings, fault_handler); 
	
	/// Force all registers into their hardware reset state.
	
	nrf24_package.Action.ResetDevice(&device);
	
	nrf24_package.Action.ConfigureRadio(&device, CHANNEL(9), HIGH_POWER, MAX_RATE, false);
	nrf24_package.Action.ClearInterruptFlags(&device, true, true, true); // clear all three flags
	nrf24_package.Action.MaskInterrupts(&device, 1, 0, 0);
	nrf24_package.Action.SetPipeState(&device, PIPE(0), true);
	nrf24_package.Action.SetPipeState(&device, PIPE(1), false);

	nrf24_package.Action.SetAutoAck(&device, PIPE(0), true);
	nrf24_package.Action.SetTransmitMode(&device);
	nrf24_package.Action.SetCRC(&device, 1, 1);
	
	nrf24_package.Action.PowerUpDevice(&device);
	
	while (1)
	{
		for (int C = 0; C < 100; C++)
		{
			/// Set these to be the same when expecting auto acks
			nrf24_package.Action.SetReceiveAddressLong(&device, radio_01, PIPE(0));
			nrf24_package.Action.SetTransmitAddress(&device, radio_01);
			
			nrf24_package.Action.DumpRegisters(&device);
//
			nrf24_package.Action.SendPayload(&device, payload, 8); // Literature indicates that reducing the size of the payload can improve range.
			nrf24_package.Action.SpinForTxInterrupt(&device,50000);
		
			pulse_led(1);
		
			HAL_Delay(50);
		
//			nrf24_package.Action.SetTransmitAddress(&device, radio_02);
//			nrf24_package.Action.SendPayload(&device, payload, 8); // Literature indicates that reducing the size of the payload can improve range.
//			nrf24_package.Action.SpinForTxInterrupt(&device, 50000);
//		
//			pulse_led(1);
//		
//			HAL_Delay(50);
		}
		
		HAL_Delay(5000);
	}

	return(0);
}


void EXTI0_IRQHandler(void)
{
	NrfReg_STATUS status_irq;
	uint32_t counter = 0;
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
	
	//nrf24_package.Action.DumpRegisters(&device);

	
	nrf24_package.Read.STATUS(&device, &status_irq); // sends a NOP to read status
	
	if ((status_irq.MAX_RT | status_irq.RX_DR | status_irq.TX_DS) == 0) // spurious interrupt unrelated to device itself.
	{
		return;
	}

	// If the interrupt for TX complete, clear just that bit
	
	if (status_irq.MAX_RT == 1)
	{
		nrf24_package.Command.FLUSH_TX(&device, &status_irq);
	}
	else
	{
		counter++;
	}
	
	if (status_irq.TX_DS || status_irq.MAX_RT)
	{
		status_irq.RX_DR = 0;
		nrf24_package.Update.STATUS(&device, status_irq, status_irq);
	}
	
	// If we've had successive MAX_RT failures we must flush the FIFO before any
	// further transmissions will work.
	
	nrf24_package.Action.ConfirmTxInterrupt(&device);
} 

static void fault_handler(NrfDevice_ptr device_ptr, NrfErrorCode code)
{
	faults++;
}

void __attribute__((weak)) ApplicationFaultHandler(char * LibName, char * LibMessage)
{
	faults++;
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

void pulse_led(uint32_t interval)
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
	HAL_Delay(interval);	
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
}
