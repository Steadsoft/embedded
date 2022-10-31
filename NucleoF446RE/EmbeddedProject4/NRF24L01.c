#include <stm32f4xx_hal.h>

#include <NRF24L01_macros.h>
#include <NRF24L01_typedefs.h>
#include <NRF24L01_structs.h>
#include <NRF24L01_calls.h>
#include <NRF24L01_statics.h>
#include <NRF24L01_globals.h>


// SEE: https://www.mouser.com/datasheet/2/297/nRF24L01_Product_Specification_v2_0-9199.pdf


static void _InitializeDevice(SPI_HandleTypeDef * SpiPtr, GPIO_TypeDef * GpioPtr, uint8_t CsPin, uint8_t CePin, NrfSpiDevice * Device)
{
	Device->spi_ptr = SpiPtr;
	Device->gpio_ptr = GpioPtr;
	Device->cs_pin = CsPin;
	Device->ce_pin = CePin;
}
static void _ReadSingleByteRegister(NrfSpiDevice * SPI, uint8_t Register, void * Value, NrfReg_STATUS_ptr NrfStatus)
{
	uint8_t command = R_REGISTER | Register;
	spi_cs_lo(SPI);
	SPI->status = HAL_SPI_TransmitReceive(SPI->spi_ptr, &command, (uint8_t*)NrfStatus, 1, HAL_MAX_DELAY);
	SPI->status = HAL_SPI_Receive(SPI->spi_ptr, Value, 1, HAL_MAX_DELAY);
	spi_cs_hi(SPI);
}
static void _WriteSingleByteRegister(NrfSpiDevice * SPI, uint8_t Register, void * Value, NrfReg_STATUS_ptr NrfStatus)
{
	uint8_t command = W_REGISTER | Register;
	spi_cs_lo(SPI);
	SPI->status = HAL_SPI_TransmitReceive(SPI->spi_ptr, &command, (uint8_t*)NrfStatus, 1, HAL_MAX_DELAY);
	SPI->status = HAL_SPI_Transmit(SPI->spi_ptr, Value, 1, HAL_MAX_DELAY);
	spi_cs_hi(SPI);
}
static void _ReadMultiBytesRegister(NrfSpiDevice * SPI, uint8_t Register, uint8_t Value[], uint8_t * BytesRead, NrfReg_STATUS_ptr NrfStatus)
{
	uint8_t command = R_REGISTER | Register;
	uint8_t width;
	uint8_t bytes;
	
	*BytesRead = 0;
	*NrfStatus = (NrfReg_STATUS){ 0 };
	
	SPI->callbacks_ptr->SendRecvSingle(SPI, Register, (uint8_t*)(Value), NrfStatus);

	//_ReadSingleByteRegister(SPI, NrfRegister.SETUP_AW, &width, NrfStatus);
	
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
static void _WriteMultiBytesRegister(NrfSpiDevice * SPI, uint8_t Register, uint8_t Value[], uint8_t * BytesWritten, NrfReg_STATUS_ptr NrfStatus)
{
	uint8_t command = W_REGISTER | Register;
	uint8_t width;
	uint8_t bytes;
	
	_ReadSingleByteRegister(SPI, NrfRegister.SETUP_AW, &width, NrfStatus);
	
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
static void spi_cs_lo(NrfSpiDevice * SPI)
{
	HAL_GPIO_WritePin(SPI->gpio_ptr, SPI->cs_pin, GPIO_PIN_RESET);
}
static void spi_cs_hi(NrfSpiDevice * SPI)
{
	HAL_GPIO_WritePin(SPI->gpio_ptr, SPI->cs_pin, GPIO_PIN_SET);
}
