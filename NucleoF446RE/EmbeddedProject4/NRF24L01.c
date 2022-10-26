#include <stm32f4xx_hal.h>

#include <NRF24L01_types.h>
#include <NRF24L01_calls.h>

void spi_cs_lo(NrfSpi *);
void spi_cs_hi(NrfSpi *);

uint8_t ReadRegister(NrfSpi * SPI, uint8_t Register, uint8_t * Value, uint8_t * NrfStatus)
{
	HAL_StatusTypeDef spi_status;
	uint8_t command = 0x00 | Register;
	spi_cs_lo(SPI);
	spi_status = HAL_SPI_TransmitReceive(SPI->spi_ptr, &command, NrfStatus, 1, HAL_MAX_DELAY);
	spi_status = HAL_SPI_Receive(SPI->spi_ptr, Value, 1, HAL_MAX_DELAY);
	spi_cs_hi(SPI);
}

void spi_cs_lo(NrfSpi * SPI)
{
	HAL_GPIO_WritePin(SPI->gpio_ptr, SPI->cs_pin, GPIO_PIN_RESET);
}

void spi_cs_hi(NrfSpi * SPI)
{
	HAL_GPIO_WritePin(SPI->gpio_ptr, SPI->cs_pin, GPIO_PIN_SET);
}
