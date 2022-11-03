#define nrf24_hal_support_implementer

#include <stm32f4xx_hal.h>
#include <nrf24_package.library.h>
#include <nrf24_hal_support.library.h>

// Declare all static functions
static void spi_ce_lo(void *);
static void spi_ce_hi(void *);
static void spi_cs_lo(void *);
static void spi_cs_hi(void *);
static void exchange_bytes(void *, uint8_t[], uint8_t[], uint8_t);
static void read_bytes(void *, uint8_t bytes_in_ptr[], uint8_t count);
static void write_bytes(void *, uint8_t bytes_out_ptr[], uint8_t count);
static void init_spi(SPI_HandleTypeDef * spi_ptr);
static void init_control_pins();
static void init_device(SPI_HandleTypeDef * spi_ptr, NrfSpiDevice_ptr device_ptr, NrfIoDescriptor_ptr descriptor_ptr);
static void flash_led_forever(uint32_t interval);

// Declare the global library interface with same name as library
nrf24_hal_support_struct nrf24_hal_support =
{
	.init_spi = init_spi,
	.init_control_pins = init_control_pins,
	.spi_ce_lo = spi_ce_lo,
	.spi_ce_hi = spi_ce_hi,
	.spi_cs_lo = spi_cs_lo,
	.spi_cs_hi = spi_cs_hi,
	.exchange_bytes = exchange_bytes,
	.read_bytes = read_bytes,
	.write_bytes = write_bytes,
	.init_device = init_device,
	.flash_led_forever = flash_led_forever
};

// Implementation 
static void flash_led_forever(uint32_t interval)
{
	HAL_DeInit();
	HAL_Init();
	
	__GPIOA_CLK_ENABLE();

	GPIO_InitTypeDef  GPIO_InitStruct = { 0 };
	
	GPIO_InitStruct.Pin       = GPIO_PIN_5;
	GPIO_InitStruct.Mode      = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull      = GPIO_NOPULL;
	GPIO_InitStruct.Speed     = GPIO_SPEED_MEDIUM;
	
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	while (1)
	{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
		HAL_Delay(interval);	
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
		HAL_Delay(interval);	
	}
	

}
static void init_device(SPI_HandleTypeDef * spi_ptr, NrfSpiDevice_ptr device_ptr, NrfIoDescriptor_ptr descriptor_ptr)
{
	descriptor_ptr->spi_ptr = spi_ptr;
	descriptor_ptr->gpio_ptr = GPIOA;
	descriptor_ptr->ce_pin = NRF_CE;
	descriptor_ptr->cs_pin = SPI_CS;
	
	device_ptr->io_ptr = descriptor_ptr;
	device_ptr->SelectDevice = nrf24_hal_support.spi_cs_lo;
	device_ptr->DeselectDevice = nrf24_hal_support.spi_cs_hi;
	device_ptr->ExchangeBytes = nrf24_hal_support.exchange_bytes;
	device_ptr->ReadBytes = nrf24_hal_support.read_bytes;
	device_ptr->WriteBytes = nrf24_hal_support.write_bytes;

}
static void init_spi(SPI_HandleTypeDef * spi_ptr)
{
	GPIO_InitTypeDef  GPIO_InitStruct_spi = { 0 };

	__SPI1_CLK_ENABLE();
	
	spi_ptr->Instance = SPI1;
	spi_ptr->Init.Mode = SPI_MODE_MASTER; 
	spi_ptr->Init.Direction = SPI_DIRECTION_2LINES;
	spi_ptr->Init.DataSize = SPI_DATASIZE_8BIT;
	spi_ptr->Init.CLKPolarity = SPI_POLARITY_LOW;
	spi_ptr->Init.CLKPhase = SPI_PHASE_1EDGE;
	spi_ptr->Init.NSS = SPI_NSS_SOFT; // SPI_NSS_HARD_OUTPUT
	spi_ptr->Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256;
	spi_ptr->Init.FirstBit = SPI_FIRSTBIT_MSB;
	spi_ptr->Init.TIMode = SPI_TIMODE_DISABLED;
	spi_ptr->Init.CRCCalculation = SPI_CRCCALCULATION_DISABLED;
	spi_ptr->Init.CRCPolynomial = 10;
	
	HAL_SPI_Init(spi_ptr);
	
	__GPIOA_CLK_ENABLE();

	GPIO_InitStruct_spi.Pin       = GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7;
	GPIO_InitStruct_spi.Mode      = GPIO_MODE_AF_PP;
	GPIO_InitStruct_spi.Pull      = GPIO_PULLDOWN;
	GPIO_InitStruct_spi.Speed     = GPIO_SPEED_MEDIUM;
	GPIO_InitStruct_spi.Alternate = GPIO_AF5_SPI1;
 
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct_spi);
}

static void init_control_pins()
{
	GPIO_InitTypeDef  GPIO_InitStruct_ctrl = { 0 };
	
	GPIO_InitStruct_ctrl.Pin  = NRF_CE | SPI_CS;
	GPIO_InitStruct_ctrl.Mode = GPIO_MODE_OUTPUT_PP;

	GPIO_InitStruct_ctrl.Pull      = GPIO_PULLUP;
	GPIO_InitStruct_ctrl.Speed     = GPIO_SPEED_HIGH;

	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct_ctrl);

	HAL_GPIO_WritePin(GPIOA, SPI_CS, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, NRF_CE, GPIO_PIN_RESET);
}

static void spi_ce_lo(void * ptr)
{
	HAL_GPIO_WritePin(((NrfIoDescriptor_ptr)ptr)->gpio_ptr, ((NrfIoDescriptor_ptr)ptr)->ce_pin, GPIO_PIN_RESET);
}
static void spi_ce_hi(void * ptr)
{
	HAL_GPIO_WritePin(((NrfIoDescriptor_ptr)ptr)->gpio_ptr, ((NrfIoDescriptor_ptr)ptr)->ce_pin, GPIO_PIN_SET);
}
static void spi_cs_lo(void * ptr)
{
	HAL_GPIO_WritePin(((NrfIoDescriptor_ptr)ptr)->gpio_ptr, ((NrfIoDescriptor_ptr)ptr)->cs_pin, GPIO_PIN_RESET);
}
static void spi_cs_hi(void * ptr)
{
	HAL_GPIO_WritePin(((NrfIoDescriptor_ptr)ptr)->gpio_ptr, ((NrfIoDescriptor_ptr)ptr)->cs_pin, GPIO_PIN_SET);
}
static void exchange_bytes(void * ptr, uint8_t bytes_out_ptr[], uint8_t bytes_in_ptr[], uint8_t count)
{
	((NrfIoDescriptor_ptr)ptr)->status = HAL_SPI_TransmitReceive(((NrfIoDescriptor_ptr)ptr)->spi_ptr, bytes_out_ptr, bytes_in_ptr, count, HAL_MAX_DELAY);
}

static void read_bytes(void * ptr, uint8_t bytes_in_ptr[], uint8_t count)
{
	((NrfIoDescriptor_ptr)ptr)->status = HAL_SPI_Receive(((NrfIoDescriptor_ptr)ptr)->spi_ptr, bytes_in_ptr, count, HAL_MAX_DELAY);
}

static void write_bytes(void * ptr, uint8_t bytes_out_ptr[], uint8_t count)
{
	((NrfIoDescriptor_ptr)ptr)->status = HAL_SPI_Receive(((NrfIoDescriptor_ptr)ptr)->spi_ptr, bytes_out_ptr, count, HAL_MAX_DELAY);
}
