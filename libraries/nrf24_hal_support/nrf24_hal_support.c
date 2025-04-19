// Should always be the very first line in the implementation source file.
#define nrf24_hal_support_implementer

// Include all required platform headers.
#include <stm32f4xx_hal.h>

// Include all required library headers
#include <nrf24_hal_support.library.h>

#define elif else if

private NrfSpiDevice zeroized = { 0 };


// Declare all static functions
private void spi_set_ce_lo(NrfSpiDevice_ptr);
private void spi_set_ce_hi(NrfSpiDevice_ptr);
private void spi_set_csn_lo(NrfSpiDevice_ptr);
private void spi_set_csn_hi(NrfSpiDevice_ptr);
private void exchange_bytes(NrfSpiDevice_ptr ptr, uint8_t bytes_out_ptr[], uint8_t bytes_in_ptr[], uint8_t count);
private void configure(SPI_TypeDef * spi_base, TIM_TypeDef * tim_base, uint64_t int_pin, uint32_t ext_int_id, uint64_t ce_pin, uint64_t cs_pin, NrfSpiDevice_ptr device_ptr, nrf_fault_handler handler);
private void pulse_led_forever(uint32_t interval);
private void read_bytes(NrfSpiDevice_ptr ptr, uint8_t bytes_in_ptr[], uint8_t count);
private void write_bytes(NrfSpiDevice_ptr ptr, uint8_t bytes_out_ptr[], uint8_t count);

// Declare the global library interface with same name as library
public nrf24_hal_support_struct nrf24_hal_support =
{
	.Configure = configure,
	.Deactivate = spi_set_ce_lo,
	.Activate = spi_set_ce_hi,
	.Select = spi_set_csn_lo,
	.Deselect = spi_set_csn_hi,
	.ExchangeBytes = exchange_bytes,
	.ReadBytes = read_bytes,
	.WriteBytes = write_bytes,
	.flash_led_forever = pulse_led_forever
};
// Implementation 
private void pulse_led_forever(uint32_t interval)
{
	volatile uint8_t cease = 0;
	
	GPIO_InitTypeDef  GPIO_InitStruct = { 0 };
	
	GPIO_InitStruct.Pin       = GPIO_PIN_5;
	GPIO_InitStruct.Mode      = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull      = GPIO_NOPULL;
	GPIO_InitStruct.Speed     = GPIO_SPEED_MEDIUM;
	
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	while (cease == 0)
	{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
		HAL_Delay(interval);	
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
		HAL_Delay(interval);	
	}
}
// Configure the SPI and associated GPIO pins based on the supplied SPI base address.
// The int pin, ce pin and cs pin are assumed to be on the same IO port as the specified SPI.
private void configure(SPI_TypeDef * spi_base, TIM_TypeDef * tim_base, uint64_t int_pin, uint32_t ext_int_id, uint64_t ce_pin, uint64_t cs_pin, NrfSpiDevice_ptr device_ptr, nrf_fault_handler handler)
{
	HAL_StatusTypeDef status;
	GPIO_InitTypeDef  GPIO_InitStruct_ctrl = { 0 };
	GPIO_InitTypeDef  GPIO_InitStruct_spi = { 0 };
	GPIO_InitTypeDef  GPIO_InitStruct_irq = { 0 };
	
	(*device_ptr) = zeroized; // ensure the struct is in a clean state
	
	if (device_ptr == NULL)
	{
		handler(NULL, NULL_ARG_PTR);
		return;
	}
	
	device_ptr->FaultHandler = handler;
	
	if (int_pin == ce_pin || int_pin == cs_pin || ce_pin == cs_pin)
	{
		// Invalid pin combination
		device_ptr->FaultHandler(device_ptr, INVALID_PIN_COMBINATION);
		return;
	}

	if (spi_base == SPI1) // For now we use a fixed set of pins for the SPI based on the chosen SPI number.
	{
		__SPI1_CLK_ENABLE();
		__GPIOA_CLK_ENABLE();
		GPIO_InitStruct_spi.Pin       = GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7;  // SCK, MISO, MOSI
		GPIO_InitStruct_spi.Alternate = GPIO_AF5_SPI1;
		GPIO_InitStruct_spi.Mode      = GPIO_MODE_AF_PP;
		GPIO_InitStruct_spi.Pull      = GPIO_PULLDOWN;
		GPIO_InitStruct_spi.Speed     = GPIO_SPEED_HIGH;
 
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct_spi);

	}
	elif (spi_base == SPI2)
	{
		__SPI1_CLK_ENABLE();
		__GPIOB_CLK_ENABLE();
		GPIO_InitStruct_spi.Pin       = GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15; // SCK, MISO, MOSI
		GPIO_InitStruct_spi.Alternate = GPIO_AF5_SPI1;
		GPIO_InitStruct_spi.Mode      = GPIO_MODE_AF_PP;
		GPIO_InitStruct_spi.Pull      = GPIO_PULLDOWN;
		GPIO_InitStruct_spi.Speed     = GPIO_SPEED_HIGH;
 
		HAL_GPIO_Init(GPIOB, &GPIO_InitStruct_spi);
	}
	else
	{
		device_ptr->FaultHandler(device_ptr, INVALID_SPI_BASE);
		return;
	}
	
	device_ptr->spi.Instance = spi_base;
	device_ptr->spi.Init.Mode = SPI_MODE_MASTER; 
	device_ptr->spi.Init.Direction = SPI_DIRECTION_2LINES;
	device_ptr->spi.Init.DataSize = SPI_DATASIZE_8BIT;
	
	// These two settings set the SPI mode to 0
	device_ptr->spi.Init.CLKPolarity = SPI_POLARITY_LOW;
	device_ptr->spi.Init.CLKPhase = SPI_PHASE_1EDGE;
	
	device_ptr->spi.Init.NSS = SPI_NSS_SOFT; // SPI_NSS_HARD_OUTPUT
	device_ptr->spi.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
	device_ptr->spi.Init.FirstBit = SPI_FIRSTBIT_MSB;
	device_ptr->spi.Init.TIMode = SPI_TIMODE_DISABLED;
	device_ptr->spi.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLED;
	device_ptr->spi.Init.CRCPolynomial = 10;
	
	status = HAL_SPI_Init(&device_ptr->spi);
	
	if (status != HAL_OK)
	{
		device_ptr->FaultHandler(device_ptr, HAL_SPI_INIT_ERROR);
		return;
	}
	
	// The int, cs and ce pins can be assigned to any suitable pin and port the user desires.
	
	if (int_pin >= 0)
	{
		GPIO_InitStruct_irq.Pin = DECODE_PIN(int_pin);
		GPIO_InitStruct_irq.Mode = GPIO_MODE_IT_FALLING;
		GPIO_InitStruct_irq.Pull = GPIO_PULLUP;
		GPIO_InitStruct_spi.Speed = GPIO_SPEED_FAST;
		HAL_GPIO_Init(DECODE_BASE(int_pin), &GPIO_InitStruct_irq);
		/* EXTI interrupt init*/
		HAL_NVIC_SetPriority(ext_int_id, 0, 0);
		HAL_NVIC_EnableIRQ(ext_int_id); 
	}
	
	// Init the control pins
	
	GPIO_InitStruct_ctrl.Pin   = DECODE_PIN(ce_pin); 
	GPIO_InitStruct_ctrl.Mode  = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct_ctrl.Pull  = GPIO_PULLUP;
	GPIO_InitStruct_ctrl.Speed = GPIO_SPEED_LOW;

	HAL_GPIO_Init(DECODE_BASE(ce_pin), &GPIO_InitStruct_ctrl);
	HAL_GPIO_WritePin(DECODE_BASE(ce_pin), DECODE_PIN(ce_pin), GPIO_PIN_RESET);
	
	GPIO_InitStruct_ctrl.Pin   = DECODE_PIN(cs_pin); 
	GPIO_InitStruct_ctrl.Mode  = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct_ctrl.Pull  = GPIO_PULLUP;
	GPIO_InitStruct_ctrl.Speed = GPIO_SPEED_LOW;

	HAL_GPIO_Init(DECODE_BASE(cs_pin), &GPIO_InitStruct_ctrl);
	HAL_GPIO_WritePin(DECODE_BASE(cs_pin), DECODE_PIN(cs_pin), GPIO_PIN_SET);
	
	// Init the pulse timer for pulsing CE (a bit more than 10uS)
	
	__HAL_RCC_TIM1_CLK_ENABLE();
	
	uint32_t sysClockFreq = HAL_RCC_GetSysClockFreq() / 1000000; 	

	// Configure TIM1
	device_ptr->pulse_timer.Instance = tim_base;
	device_ptr->pulse_timer.Init.Prescaler = sysClockFreq - 1; // Set prescaler for 1 MHz timer clock (assuming 72 MHz system clock)
	device_ptr->pulse_timer.Init.CounterMode = TIM_COUNTERMODE_UP;
	device_ptr->pulse_timer.Init.Period = 0xFFFF; // Max count value
	device_ptr->pulse_timer.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	device_ptr->pulse_timer.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

	if (HAL_TIM_Base_Init(&(device_ptr->pulse_timer)) != HAL_OK)
	{
		// Initialization Error
		device_ptr->FaultHandler(device_ptr, HAL_TIM_INIT_ERROR);
	}

	// Start TIM1
	
	if (HAL_TIM_Base_Start(&(device_ptr->pulse_timer)) != HAL_OK)
	{
		// Initialization Error
		device_ptr->FaultHandler(device_ptr, HAL_TIM_START_ERROR);
	}
	
	// Attach the control pins details to the device struc
	
	//device_ptr->gpio_ptr = gpio_base;
	device_ptr->ce_pin = ce_pin;
	device_ptr->cs_pin = cs_pin;
	device_ptr->int_pin = DECODE_PIN(int_pin);
	device_ptr->configured = 1; // Mark as configured
}
private void spi_set_ce_lo(NrfSpiDevice_ptr ptr)
{
	HAL_GPIO_WritePin(DECODE_BASE(ptr->ce_pin), DECODE_PIN(ptr->ce_pin), GPIO_PIN_RESET);
}
private void spi_set_ce_hi(NrfSpiDevice_ptr ptr)
{
	HAL_GPIO_WritePin(DECODE_BASE(ptr->ce_pin), DECODE_PIN(ptr->ce_pin), GPIO_PIN_SET);
}
private void spi_set_csn_lo(NrfSpiDevice_ptr ptr)
{
	HAL_GPIO_WritePin(DECODE_BASE(ptr->cs_pin), DECODE_PIN(ptr->cs_pin), GPIO_PIN_RESET);
}
private void spi_set_csn_hi(NrfSpiDevice_ptr ptr)
{
	HAL_GPIO_WritePin(DECODE_BASE(ptr->cs_pin), DECODE_PIN(ptr->cs_pin), GPIO_PIN_SET);
}
private void exchange_bytes(NrfSpiDevice_ptr ptr, uint8_t bytes_out_ptr[], uint8_t bytes_in_ptr[], uint8_t count)
{
	ptr->status = HAL_SPI_TransmitReceive(&ptr->spi, bytes_out_ptr, bytes_in_ptr, count, HAL_MAX_DELAY);
	
	if (ptr->status != HAL_OK)
		pulse_led_forever(100);
}
private void read_bytes(NrfSpiDevice_ptr ptr, uint8_t bytes_in_ptr[], uint8_t count)
{
	ptr->status = HAL_SPI_Receive(&ptr->spi, bytes_in_ptr, count, HAL_MAX_DELAY);
	
	if (ptr->status != HAL_OK)
		pulse_led_forever(100);
}
private void write_bytes(NrfSpiDevice_ptr ptr, uint8_t bytes_out_ptr[], uint8_t count)
{
	ptr->status = HAL_SPI_Transmit(&ptr->spi, bytes_out_ptr, count, HAL_MAX_DELAY);
	
	if (ptr->status != HAL_OK)
		pulse_led_forever(100);
}