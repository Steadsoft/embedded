#include <stm32f4xx_hal.h>

#include <NRF24L01_types.h>
#include <NRF24L01_calls.h>

void spi_cs_lo(NrfSpi *);
void spi_cs_hi(NrfSpi *);

void ReadSingleByteRegister(NrfSpi * SPI, uint8_t Register, uint8_t * Value, uint8_t * NrfStatus)
{
	uint8_t command = 0x00 | Register;
	spi_cs_lo(SPI);
	*NrfStatus = HAL_SPI_TransmitReceive(SPI->spi_ptr, &command, NrfStatus, 1, HAL_MAX_DELAY);
	*NrfStatus = HAL_SPI_Receive(SPI->spi_ptr, Value, 1, HAL_MAX_DELAY);
	spi_cs_hi(SPI);
}

void ReadMultiBytesRegister(NrfSpi * SPI, uint8_t Register, uint8_t * Value, uint8_t * BytesRead, uint8_t * NrfStatus)
{
	uint8_t command = 0x00 | Register;
	uint8_t width;
	uint8_t bytes;
	
	ReadSingleByteRegister(SPI, NrfRegister.SETUP_AW, &width, NrfStatus);
	
	switch (width)
	{
	case 1:
		bytes = 3;
		break;
	case 2: 
		bytes = 4;
		break;
	case 3:
		bytes = 5;
		break;
	}
	
	*BytesRead = bytes;
	
	spi_cs_lo(SPI);
	*NrfStatus = HAL_SPI_TransmitReceive(SPI->spi_ptr, &command, NrfStatus, 1, HAL_MAX_DELAY);
	*NrfStatus = HAL_SPI_Receive(SPI->spi_ptr, Value, bytes, HAL_MAX_DELAY);
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
