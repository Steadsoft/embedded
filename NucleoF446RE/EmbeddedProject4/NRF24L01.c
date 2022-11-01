#include <stdint.h>

#include <NRF24L01_headers.h>

// SEE: https://www.mouser.com/datasheet/2/297/nRF24L01_Product_Specification_v2_0-9199.pdf
// SEE: https://infocenter.nordicsemi.com/pdf/nan_24-08.pdf?cp=13_10

static void _ReadRFChannelRegister(NrfSpiDevice_ptr device_ptr, NrfReg_RF_CH_ptr Value, NrfReg_STATUS_ptr NrfStatus)
{
	_ReadSingleByteRegister(device_ptr, NrfRegister.RF_CH, (uint8_t*)(Value), NrfStatus);
}

static void _ReadSingleByteRegister(NrfSpiDevice_ptr device_ptr, uint8_t Register, uint8_t * Value, NrfReg_STATUS_ptr NrfStatus)
{
	uint8_t command = R_REGISTER | Register;
	
	device_ptr->SelectDevice(device_ptr->io_ptr);
	device_ptr->ExchangeBytes(device_ptr->io_ptr, &command, (uint8_t*)NrfStatus, 1);
	device_ptr->ReadBytes(device_ptr->io_ptr, Value, 1);
	device_ptr->DeselectDevice(device_ptr->io_ptr);
}
static void _WriteSingleByteRegister(NrfSpiDevice_ptr device_ptr, uint8_t Register, uint8_t Value, NrfReg_STATUS_ptr NrfStatus)
{
	uint8_t command = W_REGISTER | Register;
	device_ptr->SelectDevice(device_ptr->io_ptr);
	device_ptr->ExchangeBytes(device_ptr->io_ptr, &command, (uint8_t*)NrfStatus, 1);
	device_ptr->WriteBytes(device_ptr->io_ptr, &Value, 1);
	device_ptr->DeselectDevice(device_ptr->io_ptr);
}
static void _ReadMultiBytesRegister(NrfSpiDevice_ptr device_ptr, uint8_t Register, uint8_t Value[], uint8_t * BytesRead, NrfReg_STATUS_ptr NrfStatus)
{
	uint8_t command = R_REGISTER | Register;
	uint8_t width;
	uint8_t bytes;
	
	*BytesRead = 0;
	*NrfStatus = (NrfReg_STATUS){ 0 };

	_ReadSingleByteRegister(device_ptr, NrfRegister.SETUP_AW, &width, NrfStatus);
	
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
	
	device_ptr->SelectDevice(device_ptr->io_ptr);
	device_ptr->ExchangeBytes(device_ptr->io_ptr, &command, (uint8_t*)NrfStatus,1);
	device_ptr->ReadBytes(device_ptr->io_ptr, Value, bytes);
	device_ptr->DeselectDevice(device_ptr->io_ptr);
}
static void _WriteMultiBytesRegister(NrfSpiDevice_ptr device_ptr, uint8_t Register, uint8_t Value[], uint8_t * BytesWritten, NrfReg_STATUS_ptr NrfStatus)
{
	uint8_t command = W_REGISTER | Register;
	uint8_t width;
	uint8_t bytes;
	
	*NrfStatus = (NrfReg_STATUS){ 0 };

	_ReadSingleByteRegister(device_ptr, NrfRegister.SETUP_AW, &width, NrfStatus);
	
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
	
	device_ptr->SelectDevice(device_ptr->io_ptr);
	device_ptr->ExchangeBytes(device_ptr->io_ptr, &command, (uint8_t*)NrfStatus, 1);
	device_ptr->WriteBytes(device_ptr->io_ptr, Value, bytes);
	device_ptr->DeselectDevice(device_ptr->io_ptr);
}
