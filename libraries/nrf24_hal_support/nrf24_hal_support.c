#define nrf24_hal_support_implementer

#include <stm32f4xx_hal.h>
#include <nrf24_hal_support.library.h>
#include <nrf24_package.library.h>

// Declare all static functions
static void spi_set_ce_lo(NrfSpiDevice_ptr);
static void spi_set_ce_hi(NrfSpiDevice_ptr);
static void spi_set_csn_lo(NrfSpiDevice_ptr);
static void spi_set_csn_hi(NrfSpiDevice_ptr);
static void exchange_bytes(NrfSpiDevice_ptr, uint8_t[], uint8_t[], uint8_t);
static void read_bytes(NrfSpiDevice_ptr, uint8_t bytes_in_ptr[], uint8_t count);
static void write_bytes(NrfSpiDevice_ptr, uint8_t bytes_out_ptr[], uint8_t count);
static void init_spi(SPI_HandleTypeDef * spi_ptr, unsigned long spi_base, int32_t int_pin, uint32_t ce_pin, uint32_t cs_pin, NrfSpiDevice_ptr device_ptr);
static void pulse_led_forever(uint32_t interval);

// Declare the global library interface with same name as library
nrf24_hal_support_struct nrf24_hal_support =
{
	.init_spi = init_spi,
	.spi_set_ce_lo = spi_set_ce_lo,
	.spi_set_ce_hi = spi_set_ce_hi,
	.spi_set_csn_lo = spi_set_csn_lo,
	.spi_set_csn_hi = spi_set_csn_hi,
	.exchange_bytes = exchange_bytes,
	.read_bytes = read_bytes,
	.write_bytes = write_bytes,
	.flash_led_forever = pulse_led_forever
};

// Implementation 
static void pulse_led_forever(uint32_t interval)
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

// Initiaize the SPI and associated GPIO pins based on the supplied SPI base address.
// The int pin, ce pin nd cs pin are assumed to be on the same IO port as the specified SPI.
static void Initialize(SPI_HandleTypeDef * spi_ptr, NrfSpiDevice_ptr device_ptr, unsigned long spi_base, int32_t int_pin, uint32_t ce_pin, uint32_t cs_pin)
{
	init_spi(spi_ptr, spi_base, int_pin, ce_pin, cs_pin, device_ptr);
}

static void init_spi(SPI_HandleTypeDef * spi_ptr, unsigned long spi_base, int32_t int_pin, uint32_t ce_pin, uint32_t cs_pin, NrfSpiDevice_ptr device_ptr)
{
	unsigned long gpio_base;
	HAL_StatusTypeDef status;
	GPIO_InitTypeDef  GPIO_InitStruct_ctrl = { 0 };
	GPIO_InitTypeDef  GPIO_InitStruct_spi = { 0 };
	GPIO_InitTypeDef  GPIO_InitStruct_irq = { 0 };

	if (spi_base == SPI1_BASE)
	{
		gpio_base = GPIOA_BASE;
		__SPI1_CLK_ENABLE();
		__GPIOA_CLK_ENABLE();
		GPIO_InitStruct_spi.Pin       = GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7;
		GPIO_InitStruct_spi.Alternate = GPIO_AF5_SPI1;
	}
	if (spi_base == SPI4_BASE)
	{
		gpio_base = GPIOB_BASE;
		__SPI4_CLK_ENABLE();
		__GPIOB_CLK_ENABLE();
		GPIO_InitStruct_spi.Pin       = GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5;
		GPIO_InitStruct_spi.Alternate = GPIO_AF5_SPI4;
	}
	
	spi_ptr->Instance = ((SPI_TypeDef *) spi_base);
	spi_ptr->Init.Mode = SPI_MODE_MASTER; 
	spi_ptr->Init.Direction = SPI_DIRECTION_2LINES;
	spi_ptr->Init.DataSize = SPI_DATASIZE_8BIT;
	spi_ptr->Init.CLKPolarity = SPI_POLARITY_LOW;
	spi_ptr->Init.CLKPhase = SPI_PHASE_1EDGE;
	spi_ptr->Init.NSS = SPI_NSS_SOFT; // SPI_NSS_HARD_OUTPUT
	spi_ptr->Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
	spi_ptr->Init.FirstBit = SPI_FIRSTBIT_MSB;
	spi_ptr->Init.TIMode = SPI_TIMODE_DISABLED;
	spi_ptr->Init.CRCCalculation = SPI_CRCCALCULATION_DISABLED;
	spi_ptr->Init.CRCPolynomial = 10;
	
	status = HAL_SPI_Init(spi_ptr);
	
	GPIO_InitStruct_spi.Mode      = GPIO_MODE_AF_PP;
	GPIO_InitStruct_spi.Pull      = GPIO_PULLDOWN;
	GPIO_InitStruct_spi.Speed     = GPIO_SPEED_HIGH;
 
	HAL_GPIO_Init((GPIO_TypeDef *)(gpio_base), &GPIO_InitStruct_spi);
	
	if (int_pin < 0)
	{
		GPIO_InitStruct_irq.Pin = int_pin;
		GPIO_InitStruct_irq.Mode = GPIO_MODE_IT_FALLING;
		GPIO_InitStruct_irq.Pull = GPIO_PULLUP;
		GPIO_InitStruct_spi.Speed = GPIO_SPEED_FAST;
		HAL_GPIO_Init((GPIO_TypeDef *)(gpio_base), &GPIO_InitStruct_irq);
		/* EXTI interrupt init*/
		HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
		HAL_NVIC_EnableIRQ(EXTI0_IRQn); 
	}
	
	// Init the control pins
	
	GPIO_InitStruct_ctrl.Pin   = ce_pin | cs_pin;
	GPIO_InitStruct_ctrl.Mode  = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct_ctrl.Pull  = GPIO_PULLUP;
	GPIO_InitStruct_ctrl.Speed = GPIO_SPEED_LOW;

	HAL_GPIO_Init((GPIO_TypeDef *)(gpio_base), &GPIO_InitStruct_ctrl);
	HAL_GPIO_WritePin((GPIO_TypeDef *)(gpio_base), cs_pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin((GPIO_TypeDef *)(gpio_base), ce_pin, GPIO_PIN_RESET);
	
	device_ptr->spi_ptr = spi_ptr;
	device_ptr->gpio_ptr = (GPIO_TypeDef *)(gpio_base);
	device_ptr->ce_pin = ce_pin;
	device_ptr->cs_pin = cs_pin;
	device_ptr->int_pin = int_pin;
}

static void spi_set_ce_lo(NrfSpiDevice_ptr ptr)
{
	HAL_GPIO_WritePin(ptr->gpio_ptr, ptr->ce_pin, GPIO_PIN_RESET);
}
static void spi_set_ce_hi(NrfSpiDevice_ptr ptr)
{
	HAL_GPIO_WritePin(ptr->gpio_ptr, ptr->ce_pin, GPIO_PIN_SET);
}
static void spi_set_csn_lo(NrfSpiDevice_ptr ptr)
{
	HAL_GPIO_WritePin(ptr->gpio_ptr, ptr->cs_pin, GPIO_PIN_RESET);
}
static void spi_set_csn_hi(NrfSpiDevice_ptr ptr)
{
	HAL_GPIO_WritePin(ptr->gpio_ptr, ptr->cs_pin, GPIO_PIN_SET);
}
static void exchange_bytes(NrfSpiDevice_ptr ptr, uint8_t bytes_out_ptr[], uint8_t bytes_in_ptr[], uint8_t count)
{
	ptr->status = HAL_SPI_TransmitReceive(ptr->spi_ptr, bytes_out_ptr, bytes_in_ptr, count, HAL_MAX_DELAY);
	
	if (ptr->status != HAL_OK)
		pulse_led_forever(100);
}

static void read_bytes(NrfSpiDevice_ptr ptr, uint8_t bytes_in_ptr[], uint8_t count)
{
	ptr->status = HAL_SPI_Receive(ptr->spi_ptr, bytes_in_ptr, count, HAL_MAX_DELAY);
	
	if (ptr->status != HAL_OK)
		pulse_led_forever(100);
}

static void write_bytes(NrfSpiDevice_ptr ptr, uint8_t bytes_out_ptr[], uint8_t count)
{
	ptr->status = HAL_SPI_Transmit(ptr->spi_ptr, bytes_out_ptr, count, HAL_MAX_DELAY);
	
	if (ptr->status != HAL_OK)
		pulse_led_forever(100);
}
