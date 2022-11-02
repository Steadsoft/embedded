
#include <stm32f4xx_hal.h>

#define nrf_hal_support
#include <nrf_hal_support.headers.h>

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
