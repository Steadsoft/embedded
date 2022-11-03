// SEE: https://www.mouser.com/datasheet/2/297/nRF24L01_Product_Specification_v2_0-9199.pdf
// SEE: https://infocenter.nordicsemi.com/pdf/nan_24-08.pdf?cp=13_10

#include <stdint.h>

#define nrf24_package_implementer
#include <nrf24_package.library.h>

// Declare all static functions

static void _ReadConfigRegister(NrfSpiDevice_ptr device_ptr, NrfReg_CONFIG_ptr Value, NrfReg_STATUS_ptr NrfStatus);
static void _WriteConfigRegister(NrfSpiDevice_ptr device_ptr, NrfReg_CONFIG Value, NrfReg_STATUS_ptr NrfStatus);
static void _ReadEnAaRegister(NrfSpiDevice_ptr device_ptr, NrfReg_EN_AA_ptr Value, NrfReg_STATUS_ptr NrfStatus);
static void _WriteEnAaRegister(NrfSpiDevice_ptr device_ptr, NrfReg_EN_AA Value, NrfReg_STATUS_ptr NrfStatus);
static void _ReadEnRxAddrRegister(NrfSpiDevice_ptr device_ptr, NrfReg_EN_RXADDR_ptr Value, NrfReg_STATUS_ptr NrfStatus);
static void _WriteEnRxAddrRegister(NrfSpiDevice_ptr device_ptr, NrfReg_EN_RXADDR Value, NrfReg_STATUS_ptr NrfStatus);
static void _ReadSetupAwRegister(NrfSpiDevice_ptr device_ptr, NrfReg_SETUP_AW_ptr Value, NrfReg_STATUS_ptr NrfStatus);
static void _WriteSetupAwRegister(NrfSpiDevice_ptr device_ptr, NrfReg_SETUP_AW Value, NrfReg_STATUS_ptr NrfStatus);
static void _ReadSetupRetrRegister(NrfSpiDevice_ptr device_ptr, NrfReg_SETUP_RETR_ptr Value, NrfReg_STATUS_ptr NrfStatus);
static void _WriteSetupRetrRegister(NrfSpiDevice_ptr device_ptr, NrfReg_SETUP_RETR Value, NrfReg_STATUS_ptr NrfStatus);
static void _ReadRfChannelRegister(NrfSpiDevice_ptr device_ptr, NrfReg_RF_CH_ptr Value, NrfReg_STATUS_ptr NrfStatus);
static void _WriteRfChannelRegister(NrfSpiDevice_ptr device_ptr, NrfReg_RF_CH Value, NrfReg_STATUS_ptr NrfStatus);
static void _ReadRfSetupRegister(NrfSpiDevice_ptr device_ptr, NrfReg_RF_SETUP_ptr Value, NrfReg_STATUS_ptr NrfStatus);
static void _WriteRfSetupRegister(NrfSpiDevice_ptr device_ptr, NrfReg_RF_SETUP Value, NrfReg_STATUS_ptr NrfStatus);
static void _ReadStatusRegister(NrfSpiDevice_ptr device_ptr, NrfReg_STATUS_ptr Value, NrfReg_STATUS_ptr NrfStatus);
static void _WriteStatusRegister(NrfSpiDevice_ptr device_ptr, NrfReg_STATUS Value, NrfReg_STATUS_ptr NrfStatus);
static void _ReadObserveTxRegister(NrfSpiDevice_ptr device_ptr, NrfReg_OBSERVE_TX_ptr Value, NrfReg_STATUS_ptr NrfStatus);
static void _WriteObserveTxRegister(NrfSpiDevice_ptr device_ptr, NrfReg_OBSERVE_TX Value, NrfReg_STATUS_ptr NrfStatus);
static void _ReadCdRegister(NrfSpiDevice_ptr device_ptr, NrfReg_CD_ptr Value, NrfReg_STATUS_ptr NrfStatus);
static void _WriteCdRegister(NrfSpiDevice_ptr device_ptr, NrfReg_CD Value, NrfReg_STATUS_ptr NrfStatus);
static void _ReadRxAddrRegister(NrfSpiDevice_ptr device_ptr, NrfReg_RX_ADDR_ptr Value, uint8_t Pipe, NrfReg_STATUS_ptr NrfStatus);
static void _WriteRxAddrRegister(NrfSpiDevice_ptr device_ptr, NrfReg_RX_ADDR Value, uint8_t Pipe, NrfReg_STATUS_ptr NrfStatus);
static void _ReadRxPwRegister(NrfSpiDevice_ptr device_ptr, NrfReg_RX_PW_ptr Value, uint8_t Pipe, NrfReg_STATUS_ptr NrfStatus);
static void _WriteRxPwRegister(NrfSpiDevice_ptr device_ptr, NrfReg_RX_PW Value, uint8_t Pipe, NrfReg_STATUS_ptr NrfStatus);
static void _ReadDynpdRegister(NrfSpiDevice_ptr device_ptr, NrfReg_DYNPD_ptr Value, NrfReg_STATUS_ptr NrfStatus);
static void _WriteDynpdRegister(NrfSpiDevice_ptr device_ptr, NrfReg_DYNPD Value, NrfReg_STATUS_ptr NrfStatus);
static void _ReadFeatureRegister(NrfSpiDevice_ptr device_ptr, NrfReg_FEATURE_ptr Value, NrfReg_STATUS_ptr NrfStatus);
static void _WriteFeatureRegister(NrfSpiDevice_ptr device_ptr, NrfReg_FEATURE Value, NrfReg_STATUS_ptr NrfStatus);
static void _ReadSingleByteRegister(NrfSpiDevice * SPI, uint8_t Register, uint8_t * Value, NrfReg_STATUS_ptr NrfStatus);
static void _WriteSingleByteRegister(NrfSpiDevice * SPI, uint8_t Register, uint8_t Value, NrfReg_STATUS_ptr NrfStatus);
static void _ReadMultiBytesRegister(NrfSpiDevice * SPI, uint8_t Register, uint8_t Value[], uint8_t * BytesRead, NrfReg_STATUS_ptr NrfStatus);
static void _WriteMultiBytesRegister(NrfSpiDevice * SPI, uint8_t Register, uint8_t Value[], uint8_t * BytesWritten, NrfReg_STATUS_ptr NrfStatus);

// Declare the global library interface

NrfRegisters NrfRegister =
{ 
	.CONFIG = 0x00,
	.EN_AA = 0x01,
	.EN_RXADDR = 0x02,
	.SETUP_AW = 0x03,
	.SETUP_RETR = 0x04,
	.RF_CH = 0x05,
	.RF_SETUP = 0x06,
	.STATUS = 0x07,
	.OBSERVE_TX = 0x08,
	.CD = 0x09,
	.RX_ADDR_P0 = 0x0A,
	.RX_ADDR_P1 = 0x0B,
	.RX_ADDR_P2 = 0x0C,
	.RX_ADDR_P3 = 0x0D,
	.RX_ADDR_P4 = 0x0E,
	.RX_ADDR_P5 = 0x0F,
	.TX_ADDR = 0x10,
	.RX_PW_P0 = 0x11,
	.RX_PW_P1 = 0x12,
	.RX_PW_P2 = 0x13,
	.RX_PW_P3 = 0x14,
	.RX_PW_P4 = 0x15,
	.RX_PW_P5 = 0x16,
	.FIFO_STATUS = 0x17,
	.DYNPD = 0x1C,
	.FEATURE = 0x1D
};

nrf24_package Nrf24Package =
{ 
	.GetRegister = 
	{     
		.CONFIG = _ReadConfigRegister,
		.EN_AA = _ReadEnAaRegister,
		.EN_RX_ADDR = _ReadEnRxAddrRegister,
		.SETUP_AW = _ReadSetupAwRegister,
		.SETUP_RETR = _ReadSetupRetrRegister,
		.RF_CH = _ReadRfChannelRegister,
		.RF_SETUP = _ReadRfSetupRegister,
		.STATUS = _ReadStatusRegister,
		.OBSERVE_TX = _ReadObserveTxRegister,
		.CD = _ReadCdRegister,
		.RX_ADDR = _ReadRxAddrRegister,
		.RX_PW = _ReadRxPwRegister,
		.DYNPD = _ReadDynpdRegister,
		.FEATURE = _ReadFeatureRegister,
		//		.SingleByteRegister = _ReadSingleByteRegister,
		//		.MultiBytesRegister = _ReadMultiBytesRegister,
	},
	.SetRegister = 
	{ 
		.CONFIG = _WriteConfigRegister,
		.EN_AA = _WriteEnAaRegister,
		.EN_RX_ADDR = _WriteEnRxAddrRegister,
		.SETUP_AW = _WriteSetupAwRegister,
		.SETUP_RETR = _WriteSetupRetrRegister,
		.RF_CH = _WriteRfChannelRegister,
		.RF_SETUP = _WriteRfSetupRegister,
		.STATUS = _WriteStatusRegister,
		.OBSERVE_TX = _WriteObserveTxRegister,
		.CD = _WriteCdRegister,
		.RX_ADDR = _WriteRxAddrRegister,
		.RX_PW = _WriteRxPwRegister,
		.DYNPD = _WriteDynpdRegister,
		.FEATURE = _WriteFeatureRegister,
		//		.SingleByteRegister = _WriteSingleByteRegister,
		//		.MultiBytesRegister = _WriteMultiBytesRegister,
	}
};


// Implementation 


static void _ReadConfigRegister(NrfSpiDevice_ptr device_ptr, NrfReg_CONFIG_ptr Value, NrfReg_STATUS_ptr NrfStatus)
{
	_ReadSingleByteRegister(device_ptr, NrfRegister.CONFIG, BYTE_ADDRESS(Value), NrfStatus);
}
static void _WriteConfigRegister(NrfSpiDevice_ptr device_ptr, NrfReg_CONFIG Value, NrfReg_STATUS_ptr NrfStatus)
{
	_WriteSingleByteRegister(device_ptr, NrfRegister.CONFIG, BYTE_VALUE(Value), NrfStatus);
}
static void _ReadEnAaRegister(NrfSpiDevice_ptr device_ptr, NrfReg_EN_AA_ptr Value, NrfReg_STATUS_ptr NrfStatus)
{
	_ReadSingleByteRegister(device_ptr, NrfRegister.EN_AA, BYTE_ADDRESS(Value), NrfStatus);
}
static void _WriteEnAaRegister(NrfSpiDevice_ptr device_ptr, NrfReg_EN_AA Value, NrfReg_STATUS_ptr NrfStatus)
{
	_WriteSingleByteRegister(device_ptr, NrfRegister.EN_AA, BYTE_VALUE(Value), NrfStatus);
}
static void _ReadEnRxAddrRegister(NrfSpiDevice_ptr device_ptr, NrfReg_EN_RXADDR_ptr Value, NrfReg_STATUS_ptr NrfStatus)
{
	_ReadSingleByteRegister(device_ptr, NrfRegister.EN_RXADDR, BYTE_ADDRESS(Value), NrfStatus);
}
static void _WriteEnRxAddrRegister(NrfSpiDevice_ptr device_ptr, NrfReg_EN_RXADDR Value, NrfReg_STATUS_ptr NrfStatus)
{
	_WriteSingleByteRegister(device_ptr, NrfRegister.EN_RXADDR, BYTE_VALUE(Value), NrfStatus);
}
static void _ReadSetupAwRegister(NrfSpiDevice_ptr device_ptr, NrfReg_SETUP_AW_ptr Value, NrfReg_STATUS_ptr NrfStatus)
{
	_ReadSingleByteRegister(device_ptr, NrfRegister.SETUP_AW, BYTE_ADDRESS(Value), NrfStatus);
}
static void _WriteSetupAwRegister(NrfSpiDevice_ptr device_ptr, NrfReg_SETUP_AW Value, NrfReg_STATUS_ptr NrfStatus)
{
	_WriteSingleByteRegister(device_ptr, NrfRegister.SETUP_AW, BYTE_VALUE(Value), NrfStatus);
}
static void _ReadSetupRetrRegister(NrfSpiDevice_ptr device_ptr, NrfReg_SETUP_RETR_ptr Value, NrfReg_STATUS_ptr NrfStatus)
{
	_ReadSingleByteRegister(device_ptr, NrfRegister.SETUP_RETR, BYTE_ADDRESS(Value), NrfStatus);
}
static void _WriteSetupRetrRegister(NrfSpiDevice_ptr device_ptr, NrfReg_SETUP_RETR Value, NrfReg_STATUS_ptr NrfStatus)
{
	_WriteSingleByteRegister(device_ptr, NrfRegister.SETUP_RETR, BYTE_VALUE(Value), NrfStatus);
}
static void _ReadRfChannelRegister(NrfSpiDevice_ptr device_ptr, NrfReg_RF_CH_ptr Value, NrfReg_STATUS_ptr NrfStatus)
{
	_ReadSingleByteRegister(device_ptr, NrfRegister.RF_CH, BYTE_ADDRESS(Value), NrfStatus);
}
static void _WriteRfChannelRegister(NrfSpiDevice_ptr device_ptr, NrfReg_RF_CH Value, NrfReg_STATUS_ptr NrfStatus)
{
	_WriteSingleByteRegister(device_ptr, NrfRegister.RF_CH, BYTE_VALUE(Value), NrfStatus);
}
static void _ReadRfSetupRegister(NrfSpiDevice_ptr device_ptr, NrfReg_RF_SETUP_ptr Value, NrfReg_STATUS_ptr NrfStatus)
{
	_ReadSingleByteRegister(device_ptr, NrfRegister.RF_SETUP, BYTE_ADDRESS(Value), NrfStatus);
}
static void _WriteRfSetupRegister(NrfSpiDevice_ptr device_ptr, NrfReg_RF_SETUP Value, NrfReg_STATUS_ptr NrfStatus)
{
	_WriteSingleByteRegister(device_ptr, NrfRegister.RF_SETUP, BYTE_VALUE(Value), NrfStatus);
}
static void _ReadStatusRegister(NrfSpiDevice_ptr device_ptr, NrfReg_STATUS_ptr Value, NrfReg_STATUS_ptr NrfStatus)
{
	_ReadSingleByteRegister(device_ptr, NrfRegister.STATUS, BYTE_ADDRESS(Value), NrfStatus);
}
static void _WriteStatusRegister(NrfSpiDevice_ptr device_ptr, NrfReg_STATUS Value, NrfReg_STATUS_ptr NrfStatus)
{
	_WriteSingleByteRegister(device_ptr, NrfRegister.STATUS, BYTE_VALUE(Value), NrfStatus);
}
static void _ReadObserveTxRegister(NrfSpiDevice_ptr device_ptr, NrfReg_OBSERVE_TX_ptr Value, NrfReg_STATUS_ptr NrfStatus)
{
	_ReadSingleByteRegister(device_ptr, NrfRegister.OBSERVE_TX, BYTE_ADDRESS(Value), NrfStatus);
}
static void _WriteObserveTxRegister(NrfSpiDevice_ptr device_ptr, NrfReg_OBSERVE_TX Value, NrfReg_STATUS_ptr NrfStatus)
{
	_WriteSingleByteRegister(device_ptr, NrfRegister.OBSERVE_TX, BYTE_VALUE(Value), NrfStatus);
}
static void _ReadCdRegister(NrfSpiDevice_ptr device_ptr, NrfReg_CD_ptr Value, NrfReg_STATUS_ptr NrfStatus)
{
	_ReadSingleByteRegister(device_ptr, NrfRegister.CD, BYTE_ADDRESS(Value), NrfStatus);
}
static void _WriteCdRegister(NrfSpiDevice_ptr device_ptr, NrfReg_CD Value, NrfReg_STATUS_ptr NrfStatus)
{
	_WriteSingleByteRegister(device_ptr, NrfRegister.CD, BYTE_VALUE(Value), NrfStatus);
}
static void _ReadRxAddrRegister(NrfSpiDevice_ptr device_ptr, NrfReg_RX_ADDR_ptr Value, uint8_t Pipe, NrfReg_STATUS_ptr NrfStatus)
{
	_ReadSingleByteRegister(device_ptr, NrfRegister.RX_ADDR_P0 + Pipe, BYTE_ADDRESS(Value), NrfStatus);
}
static void _WriteRxAddrRegister(NrfSpiDevice_ptr device_ptr, NrfReg_RX_ADDR Value, uint8_t Pipe, NrfReg_STATUS_ptr NrfStatus)
{
	_WriteSingleByteRegister(device_ptr, NrfRegister.RX_ADDR_P0 + Pipe, BYTE_VALUE(Value), NrfStatus);
}
static void _ReadRxAddrP0Register(NrfSpiDevice_ptr device_ptr, NrfReg_RX_ADDR_ptr Value, NrfReg_STATUS_ptr NrfStatus)
{
	_ReadSingleByteRegister(device_ptr, NrfRegister.RX_ADDR_P0, BYTE_ADDRESS(Value), NrfStatus);
}
static void _WriteRxAddrP0Register(NrfSpiDevice_ptr device_ptr, NrfReg_RX_ADDR Value, NrfReg_STATUS_ptr NrfStatus)
{
	_WriteSingleByteRegister(device_ptr, NrfRegister.RX_ADDR_P0, BYTE_VALUE(Value), NrfStatus);
}
static void _ReadRxPwRegister(NrfSpiDevice_ptr device_ptr, NrfReg_RX_PW_ptr Value, uint8_t Pipe, NrfReg_STATUS_ptr NrfStatus)
{
	_ReadSingleByteRegister(device_ptr, NrfRegister.RX_PW_P0 + Pipe, BYTE_ADDRESS(Value), NrfStatus);
}
static void _WriteRxPwRegister(NrfSpiDevice_ptr device_ptr, NrfReg_RX_PW Value, uint8_t Pipe,NrfReg_STATUS_ptr NrfStatus)
{
	_WriteSingleByteRegister(device_ptr, NrfRegister.RX_PW_P0 + Pipe, BYTE_VALUE(Value), NrfStatus);
}
static void _ReadDynpdRegister(NrfSpiDevice_ptr device_ptr, NrfReg_DYNPD_ptr Value, NrfReg_STATUS_ptr NrfStatus)
{
	_ReadSingleByteRegister(device_ptr, NrfRegister.FEATURE, BYTE_ADDRESS(Value), NrfStatus);
}
static void _WriteDynpdRegister(NrfSpiDevice_ptr device_ptr, NrfReg_DYNPD Value, NrfReg_STATUS_ptr NrfStatus)
{
	_WriteSingleByteRegister(device_ptr, NrfRegister.FEATURE, BYTE_VALUE(Value), NrfStatus);
}
static void _ReadFeatureRegister(NrfSpiDevice_ptr device_ptr, NrfReg_FEATURE_ptr Value, NrfReg_STATUS_ptr NrfStatus)
{
	_ReadSingleByteRegister(device_ptr, NrfRegister.FEATURE, BYTE_ADDRESS(Value), NrfStatus);
}
static void _WriteFeatureRegister(NrfSpiDevice_ptr device_ptr, NrfReg_FEATURE Value, NrfReg_STATUS_ptr NrfStatus)
{
	_WriteSingleByteRegister(device_ptr, NrfRegister.FEATURE, BYTE_VALUE(Value), NrfStatus);
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
