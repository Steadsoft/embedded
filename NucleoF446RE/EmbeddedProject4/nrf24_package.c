#define nrf24_package_implementer


#include <stdint.h>
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
static void _ReadRpdRegister(NrfSpiDevice_ptr device_ptr, NrfReg_RPD_ptr Value, NrfReg_STATUS_ptr NrfStatus);
static void _WriteRpdRegister(NrfSpiDevice_ptr device_ptr, NrfReg_RPD Value, NrfReg_STATUS_ptr NrfStatus);
static void _ReadLongRxAddrRegister(NrfSpiDevice_ptr device_ptr, NrfReg_RX_ADDR_LONG_ptr Value, uint8_t Pipe, NrfReg_STATUS_ptr NrfStatus);
static void _WriteLongRxAddrRegister(NrfSpiDevice_ptr device_ptr, NrfReg_RX_ADDR_LONG Value, uint8_t Pipe, NrfReg_STATUS_ptr NrfStatus);
static void _ReadShortRxAddrRegister(NrfSpiDevice_ptr device_ptr, NrfReg_RX_ADDR_SHORT_ptr Value, uint8_t Pipe, NrfReg_STATUS_ptr NrfStatus);
static void _WriteShortRxAddrRegister(NrfSpiDevice_ptr device_ptr, NrfReg_RX_ADDR_SHORT Value, uint8_t Pipe, NrfReg_STATUS_ptr NrfStatus);
static void _ReadTxAddrRegister(NrfSpiDevice_ptr device_ptr, NrfReg_TX_ADDR_ptr Value, uint8_t Pipe, NrfReg_STATUS_ptr NrfStatus);
static void _WriteTxAddrRegister(NrfSpiDevice_ptr device_ptr, NrfReg_TX_ADDR Value, uint8_t Pipe, NrfReg_STATUS_ptr NrfStatus);
static void _ReadRxPwRegister(NrfSpiDevice_ptr device_ptr, NrfReg_RX_PW_ptr Value, uint8_t Pipe, NrfReg_STATUS_ptr NrfStatus);
static void _WriteRxPwRegister(NrfSpiDevice_ptr device_ptr, NrfReg_RX_PW Value, uint8_t Pipe, NrfReg_STATUS_ptr NrfStatus);
static void _ReadFifoStatusRegister(NrfSpiDevice_ptr device_ptr, NrfReg_FIFO_STATUS_ptr Value, NrfReg_STATUS_ptr NrfStatus);
static void _WriteFifoStatusRegister(NrfSpiDevice_ptr device_ptr, NrfReg_FIFO_STATUS Value, NrfReg_STATUS_ptr NrfStatus);
static void _ReadDynpdRegister(NrfSpiDevice_ptr device_ptr, NrfReg_DYNPD_ptr Value, NrfReg_STATUS_ptr NrfStatus);
static void _WriteDynpdRegister(NrfSpiDevice_ptr device_ptr, NrfReg_DYNPD Value, NrfReg_STATUS_ptr NrfStatus);
static void _ReadFeatureRegister(NrfSpiDevice_ptr device_ptr, NrfReg_FEATURE_ptr Value, NrfReg_STATUS_ptr NrfStatus);
static void _WriteFeatureRegister(NrfSpiDevice_ptr device_ptr, NrfReg_FEATURE Value, NrfReg_STATUS_ptr NrfStatus);
static void _ReadSingleByteRegister(NrfSpiDevice * SPI, uint8_t Register, uint8_t * Value, NrfReg_STATUS_ptr NrfStatus);
static void _WriteSingleByteRegister(NrfSpiDevice * SPI, uint8_t Register, uint8_t Value, NrfReg_STATUS_ptr NrfStatus);
static void _ReadMultiBytesRegister(NrfSpiDevice * SPI, uint8_t Register, uint8_t Value[], uint8_t * BytesRead, NrfReg_STATUS_ptr NrfStatus);
static void _WriteMultiBytesRegister(NrfSpiDevice * SPI, uint8_t Register, uint8_t Value[], uint8_t * BytesWritten, NrfReg_STATUS_ptr NrfStatus);

// Declare the global library interface with same name as library


nrf24_package_struct nrf24_package =
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
		.RPD = _ReadRpdRegister,
		.RX_ADDR_LONG = _ReadLongRxAddrRegister,
		.RX_ADDR_SHORT = _ReadShortRxAddrRegister,
		.TX_ADDR = _ReadTxAddrRegister,
		.RX_PW = _ReadRxPwRegister,
		.FIFO_STATUS = _ReadFifoStatusRegister,
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
		.RPD = _WriteRpdRegister,
		.RX_ADDR_LONG = _WriteLongRxAddrRegister,
		.RX_ADDR_SHORT = _WriteShortRxAddrRegister,
		.TX_ADDR = _WriteTxAddrRegister,
		.RX_PW = _WriteRxPwRegister,
		.FIFO_STATUS = _WriteFifoStatusRegister,
		.DYNPD = _WriteDynpdRegister,
		.FEATURE = _WriteFeatureRegister,
		//		.SingleByteRegister = _WriteSingleByteRegister,
		//		.MultiBytesRegister = _WriteMultiBytesRegister,
	}
};

const nrf24_register_names Nrf24Register =
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
	.RPD = 0x09,
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

const nrf24_command_names NrfCommand =
{ 
	.R_REGISTER = 0x00,
	.W_REGISTER = 0x20,
	.R_RX_PAYLOAD = 0x61,
	.W_TX_PAYLOAD = 0xA0,
	.FLUSH_TX = 0xE1,
	.FLUSH_RX = 0xE2,
	.REUSE_TX_PL = 0xE3,
	.R_RX_PL_WID = 0x60,
	.W_ACK_PAYLOAD = 0xA8,
	.W_TX_PAYLOAD_NOACK = 0xB0,
	.NOP = 0xFF
};

// Implementation 


static void _ReadConfigRegister(NrfSpiDevice_ptr device_ptr, NrfReg_CONFIG_ptr Value, NrfReg_STATUS_ptr NrfStatus)
{
	_ReadSingleByteRegister(device_ptr, Nrf24Register.CONFIG, BYTE_ADDRESS(Value), NrfStatus);
}
static void _WriteConfigRegister(NrfSpiDevice_ptr device_ptr, NrfReg_CONFIG Value, NrfReg_STATUS_ptr NrfStatus)
{
	_WriteSingleByteRegister(device_ptr, Nrf24Register.CONFIG, BYTE_VALUE(Value), NrfStatus);
}
static void _ReadEnAaRegister(NrfSpiDevice_ptr device_ptr, NrfReg_EN_AA_ptr Value, NrfReg_STATUS_ptr NrfStatus)
{
	_ReadSingleByteRegister(device_ptr, Nrf24Register.EN_AA, BYTE_ADDRESS(Value), NrfStatus);
}
static void _WriteEnAaRegister(NrfSpiDevice_ptr device_ptr, NrfReg_EN_AA Value, NrfReg_STATUS_ptr NrfStatus)
{
	_WriteSingleByteRegister(device_ptr, Nrf24Register.EN_AA, BYTE_VALUE(Value), NrfStatus);
}
static void _ReadEnRxAddrRegister(NrfSpiDevice_ptr device_ptr, NrfReg_EN_RXADDR_ptr Value, NrfReg_STATUS_ptr NrfStatus)
{
	_ReadSingleByteRegister(device_ptr, Nrf24Register.EN_RXADDR, BYTE_ADDRESS(Value), NrfStatus);
}
static void _WriteEnRxAddrRegister(NrfSpiDevice_ptr device_ptr, NrfReg_EN_RXADDR Value, NrfReg_STATUS_ptr NrfStatus)
{
	_WriteSingleByteRegister(device_ptr, Nrf24Register.EN_RXADDR, BYTE_VALUE(Value), NrfStatus);
}
static void _ReadSetupAwRegister(NrfSpiDevice_ptr device_ptr, NrfReg_SETUP_AW_ptr Value, NrfReg_STATUS_ptr NrfStatus)
{
	_ReadSingleByteRegister(device_ptr, Nrf24Register.SETUP_AW, BYTE_ADDRESS(Value), NrfStatus);
}
static void _WriteSetupAwRegister(NrfSpiDevice_ptr device_ptr, NrfReg_SETUP_AW Value, NrfReg_STATUS_ptr NrfStatus)
{
	_WriteSingleByteRegister(device_ptr, Nrf24Register.SETUP_AW, BYTE_VALUE(Value), NrfStatus);
}
static void _ReadSetupRetrRegister(NrfSpiDevice_ptr device_ptr, NrfReg_SETUP_RETR_ptr Value, NrfReg_STATUS_ptr NrfStatus)
{
	_ReadSingleByteRegister(device_ptr, Nrf24Register.SETUP_RETR, BYTE_ADDRESS(Value), NrfStatus);
}
static void _WriteSetupRetrRegister(NrfSpiDevice_ptr device_ptr, NrfReg_SETUP_RETR Value, NrfReg_STATUS_ptr NrfStatus)
{
	_WriteSingleByteRegister(device_ptr, Nrf24Register.SETUP_RETR, BYTE_VALUE(Value), NrfStatus);
}
static void _ReadRfChannelRegister(NrfSpiDevice_ptr device_ptr, NrfReg_RF_CH_ptr Value, NrfReg_STATUS_ptr NrfStatus)
{
	_ReadSingleByteRegister(device_ptr, Nrf24Register.RF_CH, BYTE_ADDRESS(Value), NrfStatus);
}
static void _WriteRfChannelRegister(NrfSpiDevice_ptr device_ptr, NrfReg_RF_CH Value, NrfReg_STATUS_ptr NrfStatus)
{
	_WriteSingleByteRegister(device_ptr, Nrf24Register.RF_CH, BYTE_VALUE(Value), NrfStatus);
}
static void _ReadRfSetupRegister(NrfSpiDevice_ptr device_ptr, NrfReg_RF_SETUP_ptr Value, NrfReg_STATUS_ptr NrfStatus)
{
	_ReadSingleByteRegister(device_ptr, Nrf24Register.RF_SETUP, BYTE_ADDRESS(Value), NrfStatus);
}
static void _WriteRfSetupRegister(NrfSpiDevice_ptr device_ptr, NrfReg_RF_SETUP Value, NrfReg_STATUS_ptr NrfStatus)
{
	_WriteSingleByteRegister(device_ptr, Nrf24Register.RF_SETUP, BYTE_VALUE(Value), NrfStatus);
}
static void _ReadStatusRegister(NrfSpiDevice_ptr device_ptr, NrfReg_STATUS_ptr Value, NrfReg_STATUS_ptr NrfStatus)
{
	_ReadSingleByteRegister(device_ptr, Nrf24Register.STATUS, BYTE_ADDRESS(Value), NrfStatus);
}
static void _WriteStatusRegister(NrfSpiDevice_ptr device_ptr, NrfReg_STATUS Value, NrfReg_STATUS_ptr NrfStatus)
{
	_WriteSingleByteRegister(device_ptr, Nrf24Register.STATUS, BYTE_VALUE(Value), NrfStatus);
}
static void _ReadObserveTxRegister(NrfSpiDevice_ptr device_ptr, NrfReg_OBSERVE_TX_ptr Value, NrfReg_STATUS_ptr NrfStatus)
{
	_ReadSingleByteRegister(device_ptr, Nrf24Register.OBSERVE_TX, BYTE_ADDRESS(Value), NrfStatus);
}
static void _WriteObserveTxRegister(NrfSpiDevice_ptr device_ptr, NrfReg_OBSERVE_TX Value, NrfReg_STATUS_ptr NrfStatus)
{
	_WriteSingleByteRegister(device_ptr, Nrf24Register.OBSERVE_TX, BYTE_VALUE(Value), NrfStatus);
}
static void _ReadRpdRegister(NrfSpiDevice_ptr device_ptr, NrfReg_RPD_ptr Value, NrfReg_STATUS_ptr NrfStatus)
{
	_ReadSingleByteRegister(device_ptr, Nrf24Register.RPD, BYTE_ADDRESS(Value), NrfStatus);
}
static void _WriteRpdRegister(NrfSpiDevice_ptr device_ptr, NrfReg_RPD Value, NrfReg_STATUS_ptr NrfStatus)
{
	_WriteSingleByteRegister(device_ptr, Nrf24Register.RPD, BYTE_VALUE(Value), NrfStatus);
}
static void _ReadLongRxAddrRegister(NrfSpiDevice_ptr device_ptr, NrfReg_RX_ADDR_LONG_ptr Value, uint8_t Pipe, NrfReg_STATUS_ptr NrfStatus)
{
	_ReadSingleByteRegister(device_ptr, Nrf24Register.RX_ADDR_P0 + Pipe, BYTE_ADDRESS(Value), NrfStatus);
}
static void _WriteLongRxAddrRegister(NrfSpiDevice_ptr device_ptr, NrfReg_RX_ADDR_LONG Value, uint8_t Pipe, NrfReg_STATUS_ptr NrfStatus)
{
	_WriteSingleByteRegister(device_ptr, Nrf24Register.RX_ADDR_P0 + Pipe, BYTE_VALUE(Value), NrfStatus);
}
static void _ReadShortRxAddrRegister(NrfSpiDevice_ptr device_ptr, NrfReg_RX_ADDR_SHORT_ptr Value, uint8_t Pipe, NrfReg_STATUS_ptr NrfStatus)
{
	_ReadSingleByteRegister(device_ptr, Nrf24Register.RX_ADDR_P0 + Pipe, BYTE_ADDRESS(Value), NrfStatus);
}
static void _WriteShortRxAddrRegister(NrfSpiDevice_ptr device_ptr, NrfReg_RX_ADDR_SHORT Value, uint8_t Pipe, NrfReg_STATUS_ptr NrfStatus)
{
	_WriteSingleByteRegister(device_ptr, Nrf24Register.RX_ADDR_P0 + Pipe, BYTE_VALUE(Value), NrfStatus);
}

static void _ReadTxAddrRegister(NrfSpiDevice_ptr device_ptr, NrfReg_TX_ADDR_ptr Value, uint8_t Pipe, NrfReg_STATUS_ptr NrfStatus)
{
	_ReadSingleByteRegister(device_ptr, Nrf24Register.TX_ADDR, BYTE_ADDRESS(Value), NrfStatus);
}
static void _WriteTxAddrRegister(NrfSpiDevice_ptr device_ptr, NrfReg_TX_ADDR Value, uint8_t Pipe, NrfReg_STATUS_ptr NrfStatus)
{
	_WriteSingleByteRegister(device_ptr, Nrf24Register.TX_ADDR, BYTE_VALUE(Value), NrfStatus);
}

static void _ReadRxPwRegister(NrfSpiDevice_ptr device_ptr, NrfReg_RX_PW_ptr Value, uint8_t Pipe, NrfReg_STATUS_ptr NrfStatus)
{
	_ReadSingleByteRegister(device_ptr, Nrf24Register.RX_PW_P0 + Pipe, BYTE_ADDRESS(Value), NrfStatus);
}
static void _WriteRxPwRegister(NrfSpiDevice_ptr device_ptr, NrfReg_RX_PW Value, uint8_t Pipe,NrfReg_STATUS_ptr NrfStatus)
{
	_WriteSingleByteRegister(device_ptr, Nrf24Register.RX_PW_P0 + Pipe, BYTE_VALUE(Value), NrfStatus);
}

static void _ReadFifoStatusRegister(NrfSpiDevice_ptr device_ptr, NrfReg_FIFO_STATUS_ptr Value, NrfReg_STATUS_ptr NrfStatus)
{
	_ReadSingleByteRegister(device_ptr, Nrf24Register.FIFO_STATUS, BYTE_ADDRESS(Value), NrfStatus);
}
static void _WriteFifoStatusRegister(NrfSpiDevice_ptr device_ptr, NrfReg_FIFO_STATUS Value, NrfReg_STATUS_ptr NrfStatus)
{
	_WriteSingleByteRegister(device_ptr, Nrf24Register.FIFO_STATUS, BYTE_VALUE(Value), NrfStatus);
}

static void _ReadDynpdRegister(NrfSpiDevice_ptr device_ptr, NrfReg_DYNPD_ptr Value, NrfReg_STATUS_ptr NrfStatus)
{
	_ReadSingleByteRegister(device_ptr, Nrf24Register.DYNPD, BYTE_ADDRESS(Value), NrfStatus);
}
static void _WriteDynpdRegister(NrfSpiDevice_ptr device_ptr, NrfReg_DYNPD Value, NrfReg_STATUS_ptr NrfStatus)
{
	_WriteSingleByteRegister(device_ptr, Nrf24Register.DYNPD, BYTE_VALUE(Value), NrfStatus);
}
static void _ReadFeatureRegister(NrfSpiDevice_ptr device_ptr, NrfReg_FEATURE_ptr Value, NrfReg_STATUS_ptr NrfStatus)
{
	_ReadSingleByteRegister(device_ptr, Nrf24Register.FEATURE, BYTE_ADDRESS(Value), NrfStatus);
}
static void _WriteFeatureRegister(NrfSpiDevice_ptr device_ptr, NrfReg_FEATURE Value, NrfReg_STATUS_ptr NrfStatus)
{
	_WriteSingleByteRegister(device_ptr, Nrf24Register.FEATURE, BYTE_VALUE(Value), NrfStatus);
}
static void _ReadSingleByteRegister(NrfSpiDevice_ptr device_ptr, uint8_t Register, uint8_t * Value, NrfReg_STATUS_ptr NrfStatus)
{
	uint8_t command = NrfCommand.R_REGISTER | Register;
	
	device_ptr->SelectDevice(device_ptr->io_ptr);
	device_ptr->ExchangeBytes(device_ptr->io_ptr, &command, (uint8_t*)NrfStatus, 1);
	device_ptr->ReadBytes(device_ptr->io_ptr, Value, 1);
	device_ptr->DeselectDevice(device_ptr->io_ptr);
}
static void _WriteSingleByteRegister(NrfSpiDevice_ptr device_ptr, uint8_t Register, uint8_t Value, NrfReg_STATUS_ptr NrfStatus)
{
	uint8_t command = NrfCommand.W_REGISTER | Register;
	device_ptr->SelectDevice(device_ptr->io_ptr);
	device_ptr->ExchangeBytes(device_ptr->io_ptr, &command, (uint8_t*)NrfStatus, 1);
	device_ptr->WriteBytes(device_ptr->io_ptr, &Value, 1);
	device_ptr->DeselectDevice(device_ptr->io_ptr);
}
static void _ReadMultiBytesRegister(NrfSpiDevice_ptr device_ptr, uint8_t Register, uint8_t Value[], uint8_t * BytesRead, NrfReg_STATUS_ptr NrfStatus)
{
	uint8_t command = NrfCommand.R_REGISTER | Register;
	uint8_t width;
	uint8_t bytes;
	
	*BytesRead = 0;
	*NrfStatus = (NrfReg_STATUS){ 0 };

	_ReadSingleByteRegister(device_ptr, Nrf24Register.SETUP_AW, &width, NrfStatus);
	
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
	uint8_t command = NrfCommand.W_REGISTER | Register;
	uint8_t width;
	uint8_t bytes;
	
	*NrfStatus = (NrfReg_STATUS){ 0 };

	_ReadSingleByteRegister(device_ptr, Nrf24Register.SETUP_AW, &width, NrfStatus);
	
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
