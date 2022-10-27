#include <stm32f4xx_hal.h>

#include <NRF24L01_defs.h>
#include <NRF24L01_types.h>
#include <NRF24L01_calls.h>

void spi_cs_lo(NrfSpi *);
void spi_cs_hi(NrfSpi *);

// SEE: https://www.mouser.com/datasheet/2/297/nRF24L01_Product_Specification_v2_0-9199.pdf

void ReadSingleByteRegister(NrfSpi * SPI, uint8_t Register, void * Value, STATUS * NrfStatus)
{
	uint8_t command = R_REGISTER | Register;
	spi_cs_lo(SPI);
	SPI->status = HAL_SPI_TransmitReceive(SPI->spi_ptr, &command, (uint8_t*)NrfStatus, 1, HAL_MAX_DELAY);
	SPI->status = HAL_SPI_Receive(SPI->spi_ptr, Value, 1, HAL_MAX_DELAY);
	spi_cs_hi(SPI);
}

void WriteSingleByteRegister(NrfSpi * SPI, uint8_t Register, void * Value, STATUS * NrfStatus)
{
	uint8_t command = W_REGISTER | Register;
	spi_cs_lo(SPI);
	SPI->status = HAL_SPI_TransmitReceive(SPI->spi_ptr, &command, (uint8_t*)NrfStatus, 1, HAL_MAX_DELAY);
	SPI->status = HAL_SPI_Transmit(SPI->spi_ptr, Value, 1, HAL_MAX_DELAY);
	spi_cs_hi(SPI);
}

void ReadMultiBytesRegister(NrfSpi * SPI, uint8_t Register, uint8_t Value[], uint8_t * BytesRead, STATUS * NrfStatus)
{
	uint8_t command = R_REGISTER | Register;
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
	SPI->status = HAL_SPI_TransmitReceive(SPI->spi_ptr, &command, (uint8_t*)NrfStatus, 1, HAL_MAX_DELAY);
	SPI->status = HAL_SPI_Receive(SPI->spi_ptr, Value, bytes, HAL_MAX_DELAY);
	spi_cs_hi(SPI);
}

void WriteMultiBytesRegister(NrfSpi * SPI, uint8_t Register, uint8_t Value[], uint8_t * BytesWritten, STATUS * NrfStatus)
{
	uint8_t command = W_REGISTER | Register;
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
	
	*BytesWritten = bytes;
	
	spi_cs_lo(SPI);
	SPI->status = HAL_SPI_TransmitReceive(SPI->spi_ptr, &command, (uint8_t*)NrfStatus, 1, HAL_MAX_DELAY);
	SPI->status = HAL_SPI_Transmit(SPI->spi_ptr, Value, bytes, HAL_MAX_DELAY);
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
