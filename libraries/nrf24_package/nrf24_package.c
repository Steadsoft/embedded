#define nrf24_package_implementer

#include <stdint.h>
#include <stm32f4xx_hal.h>
#include <nrf24_package.library.h>
#include <nrf24_hal_support.library.h>

// Declare all static functions

static void _ReadConfigRegister(NrfSpiDevice_ptr device_ptr, NrfReg_CONFIG_ptr Value, NrfReg_STATUS_ptr NrfStatus);
static void _WriteConfigRegister(NrfSpiDevice_ptr device_ptr, NrfReg_CONFIG Value, NrfReg_STATUS_ptr NrfStatus);
static void _UpdateConfigRegister(NrfSpiDevice_ptr device_ptr, NrfReg_CONFIG Value, NrfReg_CONFIG Mask, NrfReg_STATUS_ptr NrfStatus);
static void _ReadEnAaRegister(NrfSpiDevice_ptr device_ptr, NrfReg_EN_AA_ptr Value, NrfReg_STATUS_ptr NrfStatus);
static void _WriteEnAaRegister(NrfSpiDevice_ptr device_ptr, NrfReg_EN_AA Value, NrfReg_STATUS_ptr NrfStatus);
static void _UpdateEnAaRegister(NrfSpiDevice_ptr device_ptr, NrfReg_EN_AA Value, NrfReg_EN_AA Mask, NrfReg_STATUS_ptr NrfStatus);
static void _ReadEnRxAddrRegister(NrfSpiDevice_ptr device_ptr, NrfReg_EN_RXADDR_ptr Value, NrfReg_STATUS_ptr NrfStatus);
static void _WriteEnRxAddrRegister(NrfSpiDevice_ptr device_ptr, NrfReg_EN_RXADDR Value, NrfReg_STATUS_ptr NrfStatus);
static void _UpdateEnRxAddrRegister(NrfSpiDevice_ptr device_ptr, NrfReg_EN_RXADDR Value, NrfReg_EN_RXADDR Mask, NrfReg_STATUS_ptr NrfStatus);
static void _ReadSetupAwRegister(NrfSpiDevice_ptr device_ptr, NrfReg_SETUP_AW_ptr Value, NrfReg_STATUS_ptr NrfStatus);
static void _WriteSetupAwRegister(NrfSpiDevice_ptr device_ptr, NrfReg_SETUP_AW Value, NrfReg_STATUS_ptr NrfStatus);
static void _UpdateSetupAwRegister(NrfSpiDevice_ptr device_ptr, NrfReg_SETUP_AW Value, NrfReg_SETUP_AW Mask, NrfReg_STATUS_ptr NrfStatus);
static void _ReadSetupRetrRegister(NrfSpiDevice_ptr device_ptr, NrfReg_SETUP_RETR_ptr Value, NrfReg_STATUS_ptr NrfStatus);
static void _WriteSetupRetrRegister(NrfSpiDevice_ptr device_ptr, NrfReg_SETUP_RETR Value, NrfReg_STATUS_ptr NrfStatus);
static void _UpdateSetupRetrRegister(NrfSpiDevice_ptr device_ptr, NrfReg_SETUP_RETR Value, NrfReg_SETUP_RETR Mask, NrfReg_STATUS_ptr NrfStatus);
static void _ReadRfChannelRegister(NrfSpiDevice_ptr device_ptr, NrfReg_RF_CH_ptr Value, NrfReg_STATUS_ptr NrfStatus);
static void _WriteRfChannelRegister(NrfSpiDevice_ptr device_ptr, NrfReg_RF_CH Value, NrfReg_STATUS_ptr NrfStatus);
static void _UpdateRfChannelRegister(NrfSpiDevice_ptr device_ptr, NrfReg_RF_CH Value, NrfReg_RF_CH Mask, NrfReg_STATUS_ptr NrfStatus);
static void _ReadRfSetupRegister(NrfSpiDevice_ptr device_ptr, NrfReg_RF_SETUP_ptr Value, NrfReg_STATUS_ptr NrfStatus);
static void _WriteRfSetupRegister(NrfSpiDevice_ptr device_ptr, NrfReg_RF_SETUP Value, NrfReg_STATUS_ptr NrfStatus);
static void _UpdateRfSetupRegister(NrfSpiDevice_ptr device_ptr, NrfReg_RF_SETUP Value, NrfReg_RF_SETUP Mask, NrfReg_STATUS_ptr NrfStatus);
static void _ReadStatusRegister(NrfSpiDevice_ptr device_ptr, NrfReg_STATUS_ptr Value);
static void _WriteStatusRegister(NrfSpiDevice_ptr device_ptr, NrfReg_STATUS Value, NrfReg_STATUS_ptr NrfStatus);
static void _UpdateStatusRegister(NrfSpiDevice_ptr device_ptr, NrfReg_STATUS Value, NrfReg_STATUS Mask);
static void _ReadObserveTxRegister(NrfSpiDevice_ptr device_ptr, NrfReg_OBSERVE_TX_ptr Value, NrfReg_STATUS_ptr NrfStatus);
static void _WriteObserveTxRegister(NrfSpiDevice_ptr device_ptr, NrfReg_OBSERVE_TX Value, NrfReg_STATUS_ptr NrfStatus);
static void _UpdateObserveTxRegister(NrfSpiDevice_ptr device_ptr, NrfReg_OBSERVE_TX Value, NrfReg_OBSERVE_TX Mask, NrfReg_STATUS_ptr NrfStatus);
static void _ReadRpdRegister(NrfSpiDevice_ptr device_ptr, NrfReg_RPD_ptr Value, NrfReg_STATUS_ptr NrfStatus);
static void _WriteRpdRegister(NrfSpiDevice_ptr device_ptr, NrfReg_RPD Value, NrfReg_STATUS_ptr NrfStatus);
static void _UpdateRpdRegister(NrfSpiDevice_ptr device_ptr, NrfReg_RPD Value, NrfReg_RPD Mask, NrfReg_STATUS_ptr NrfStatus);
static void _ReadLongRxAddrRegister(NrfSpiDevice_ptr device_ptr, NrfReg_RX_ADDR_LONG_ptr Value, uint8_t Pipe, NrfReg_STATUS_ptr NrfStatus);
static void _WriteLongRxAddrRegister(NrfSpiDevice_ptr device_ptr, NrfReg_RX_ADDR_LONG Value, uint8_t Pipe, NrfReg_STATUS_ptr NrfStatus);
static void _ReadShortRxAddrRegister(NrfSpiDevice_ptr device_ptr, NrfReg_RX_ADDR_SHORT_ptr Value, uint8_t Pipe, NrfReg_STATUS_ptr NrfStatus);
static void _WriteShortRxAddrRegister(NrfSpiDevice_ptr device_ptr, NrfReg_RX_ADDR_SHORT Value, uint8_t Pipe, NrfReg_STATUS_ptr NrfStatus);
static void _ReadTxAddrRegister(NrfSpiDevice_ptr device_ptr, NrfReg_TX_ADDR_LONG_ptr Value, NrfReg_STATUS_ptr NrfStatus);
static void _WriteTxAddrRegister(NrfSpiDevice_ptr device_ptr, NrfReg_TX_ADDR_LONG Value, NrfReg_STATUS_ptr NrfStatus);
static void _ReadRxPwRegister(NrfSpiDevice_ptr device_ptr, NrfReg_RX_PW_ptr Value, uint8_t Pipe, NrfReg_STATUS_ptr NrfStatus);
static void _WriteRxPwRegister(NrfSpiDevice_ptr device_ptr, NrfReg_RX_PW Value, uint8_t Pipe, NrfReg_STATUS_ptr NrfStatus);
static void _ReadFifoStatusRegister(NrfSpiDevice_ptr device_ptr, NrfReg_FIFO_STATUS_ptr Value, NrfReg_STATUS_ptr NrfStatus);
static void _WriteFifoStatusRegister(NrfSpiDevice_ptr device_ptr, NrfReg_FIFO_STATUS Value, NrfReg_STATUS_ptr NrfStatus);
static void _UpdateFifoStatusRegister(NrfSpiDevice_ptr device_ptr, NrfReg_FIFO_STATUS Value, NrfReg_FIFO_STATUS Mask, NrfReg_STATUS_ptr NrfStatus);
static void _ReadDynpdRegister(NrfSpiDevice_ptr device_ptr, NrfReg_DYNPD_ptr Value, NrfReg_STATUS_ptr NrfStatus);
static void _WriteDynpdRegister(NrfSpiDevice_ptr device_ptr, NrfReg_DYNPD Value, NrfReg_STATUS_ptr NrfStatus);
static void _UpdateDynpdRegister(NrfSpiDevice_ptr device_ptr, NrfReg_DYNPD Value, NrfReg_DYNPD Mask, NrfReg_STATUS_ptr NrfStatus);
static void _ReadFeatureRegister(NrfSpiDevice_ptr device_ptr, NrfReg_FEATURE_ptr Value, NrfReg_STATUS_ptr NrfStatus);
static void _WriteFeatureRegister(NrfSpiDevice_ptr device_ptr, NrfReg_FEATURE Value, NrfReg_STATUS_ptr NrfStatus);
static void _UpdateFeatureRegister(NrfSpiDevice_ptr device_ptr, NrfReg_FEATURE Value, NrfReg_FEATURE Mask, NrfReg_STATUS_ptr NrfStatus);
static void _ReadSingleByteRegister(NrfSpiDevice * SPI, uint8_t Register, uint8_t * Value, NrfReg_STATUS_ptr NrfStatus);
static void _WriteSingleByteRegister(NrfSpiDevice * SPI, uint8_t Register, uint8_t Value, NrfReg_STATUS_ptr NrfStatus);
static void _ReadMultiBytesRegister(NrfSpiDevice * SPI, uint8_t Register, uint8_t Value[], uint8_t * BytesRead, NrfReg_STATUS_ptr NrfStatus);
static void _WriteMultiBytesRegister(NrfSpiDevice * SPI, uint8_t Register, uint8_t Value[], uint8_t * BytesWritten, NrfReg_STATUS_ptr NrfStatus);
static void _SetToPowerOnResetState(NrfSpiDevice_ptr device_ptr);
static void _PowerUpTx(NrfSpiDevice_ptr device_ptr);

static void _FlushTxFifo(NrfSpiDevice_ptr device_ptr, NrfReg_STATUS_ptr NrfStatus);
static void _FlushRxFifo(NrfSpiDevice_ptr device_ptr, NrfReg_STATUS_ptr NrfStatus);

static void _ReadAllRegisters(NrfSpiDevice_ptr device_ptr, NrfReg_ALL_REGISTERS_ptr Value, NrfReg_STATUS_ptr NrfStatus);
static void _Initialize(NrfSpiDevice_ptr device_ptr);

static void _WriteTxPayload(NrfSpiDevice_ptr, uint8_t * data_ptr, uint8_t data_len, NrfReg_STATUS_ptr NrfStatus);


// Declare the global library interface with same name as library

nrf24_package_struct nrf24_package =
{ 
	.GetRegister = 
	{     
		.CONFIG = _ReadConfigRegister,
		.EN_AA = _ReadEnAaRegister,
		.EN_RXADDR = _ReadEnRxAddrRegister,
		.SETUP_AW = _ReadSetupAwRegister,
		.SETUP_RETR = _ReadSetupRetrRegister,
		.RF_CH = _ReadRfChannelRegister,
		.RF_SETUP = _ReadRfSetupRegister,
		.STATUS = _ReadStatusRegister,
		.OBSERVE_TX = _ReadObserveTxRegister,
		.RPD = _ReadRpdRegister,
		.RX_ADDR_LONG = _ReadLongRxAddrRegister,
		.RX_ADDR_SHORT = _ReadShortRxAddrRegister,
		.TX_ADDR_LONG = _ReadTxAddrRegister,
		.RX_PW = _ReadRxPwRegister,
		.FIFO_STATUS = _ReadFifoStatusRegister,
		.DYNPD = _ReadDynpdRegister,
		.FEATURE = _ReadFeatureRegister,
		.ALL_REGISTERS = _ReadAllRegisters,
	},
	.SetRegister = 
	{ 
		.CONFIG = _WriteConfigRegister,
		.EN_AA = _WriteEnAaRegister,
		.EN_RXADDR = _WriteEnRxAddrRegister,
		.SETUP_AW = _WriteSetupAwRegister,
		.SETUP_RETR = _WriteSetupRetrRegister,
		.RF_CH = _WriteRfChannelRegister,
		.RF_SETUP = _WriteRfSetupRegister,
		.STATUS = _WriteStatusRegister,
		.OBSERVE_TX = _WriteObserveTxRegister,
		.RPD = _WriteRpdRegister,
		.RX_ADDR_LONG = _WriteLongRxAddrRegister,
		.RX_ADDR_SHORT = _WriteShortRxAddrRegister,
		.TX_ADDR_LONG = _WriteTxAddrRegister,
		.RX_PW = _WriteRxPwRegister,
		.FIFO_STATUS = _WriteFifoStatusRegister,
		.DYNPD = _WriteDynpdRegister,
		.FEATURE = _WriteFeatureRegister,
	},
	.UpdateRegister =
	{ 
		.CONFIG = _UpdateConfigRegister,
		.EN_AA = _UpdateEnAaRegister,
		.EN_RXADDR = _UpdateEnRxAddrRegister,
		.SETUP_AW = _UpdateSetupAwRegister,
		.SETUP_RETR = _UpdateSetupRetrRegister,
		.RF_CH = _UpdateRfChannelRegister,
		.RF_SETUP = _UpdateRfSetupRegister,
		.STATUS = _UpdateStatusRegister,
		.OBSERVE_TX = _UpdateObserveTxRegister,
		.RPD = _UpdateRpdRegister,
		.FIFO_STATUS = _UpdateFifoStatusRegister,
		.DYNPD = _UpdateDynpdRegister,
		.FEATURE = _UpdateFeatureRegister,
	},
	.DeviceControl =
	{ 
		.PowerOnReset = _SetToPowerOnResetState,
		.FlushTxFifo = _FlushTxFifo,
		.FlushRxFifo = _FlushRxFifo,
		.WriteTxPayload = _WriteTxPayload,
		.Initialize = _Initialize,
		.PowerUpTx = _PowerUpTx, // This is a misnomer, but we will use this to power up the device in RX mode.
	},
	.EmptyRegister =
	{ 
		.STATUS = (NrfReg_STATUS)  { 0 }
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
static void _UpdateConfigRegister(NrfSpiDevice_ptr device_ptr, NrfReg_CONFIG Value, NrfReg_CONFIG Mask, NrfReg_STATUS_ptr NrfStatus)
{
	uint8_t old_value;
	
	_ReadSingleByteRegister(device_ptr, Nrf24Register.CONFIG, &old_value, NrfStatus);
	_WriteSingleByteRegister(device_ptr, Nrf24Register.CONFIG, TWIDDLE(old_value, Value, Mask), NrfStatus);
}
static void _ReadEnAaRegister(NrfSpiDevice_ptr device_ptr, NrfReg_EN_AA_ptr Value, NrfReg_STATUS_ptr NrfStatus)
{
	_ReadSingleByteRegister(device_ptr, Nrf24Register.EN_AA, BYTE_ADDRESS(Value), NrfStatus);
}
static void _WriteEnAaRegister(NrfSpiDevice_ptr device_ptr, NrfReg_EN_AA Value, NrfReg_STATUS_ptr NrfStatus)
{
	_WriteSingleByteRegister(device_ptr, Nrf24Register.EN_AA, BYTE_VALUE(Value), NrfStatus);
}
static void _UpdateEnAaRegister(NrfSpiDevice_ptr device_ptr, NrfReg_EN_AA Value, NrfReg_EN_AA Mask, NrfReg_STATUS_ptr NrfStatus)
{
	uint8_t old_value;
	
	_ReadSingleByteRegister(device_ptr, Nrf24Register.EN_AA, &old_value, NrfStatus);
	_WriteSingleByteRegister(device_ptr, Nrf24Register.EN_AA, TWIDDLE(old_value, Value, Mask), NrfStatus);
}
static void _ReadEnRxAddrRegister(NrfSpiDevice_ptr device_ptr, NrfReg_EN_RXADDR_ptr Value, NrfReg_STATUS_ptr NrfStatus)
{
	_ReadSingleByteRegister(device_ptr, Nrf24Register.EN_RXADDR, BYTE_ADDRESS(Value), NrfStatus);
}
static void _WriteEnRxAddrRegister(NrfSpiDevice_ptr device_ptr, NrfReg_EN_RXADDR Value, NrfReg_STATUS_ptr NrfStatus)
{
	_WriteSingleByteRegister(device_ptr, Nrf24Register.EN_RXADDR, BYTE_VALUE(Value), NrfStatus);
}
static void _UpdateEnRxAddrRegister(NrfSpiDevice_ptr device_ptr, NrfReg_EN_RXADDR Value, NrfReg_EN_RXADDR Mask, NrfReg_STATUS_ptr NrfStatus)
{
	uint8_t old_value;
	
	_ReadSingleByteRegister(device_ptr, Nrf24Register.EN_RXADDR, &old_value, NrfStatus);
	_WriteSingleByteRegister(device_ptr, Nrf24Register.EN_RXADDR, TWIDDLE(old_value, Value, Mask), NrfStatus);
}
static void _ReadSetupAwRegister(NrfSpiDevice_ptr device_ptr, NrfReg_SETUP_AW_ptr Value, NrfReg_STATUS_ptr NrfStatus)
{
	_ReadSingleByteRegister(device_ptr, Nrf24Register.SETUP_AW, BYTE_ADDRESS(Value), NrfStatus);
}
static void _WriteSetupAwRegister(NrfSpiDevice_ptr device_ptr, NrfReg_SETUP_AW Value, NrfReg_STATUS_ptr NrfStatus)
{
	_WriteSingleByteRegister(device_ptr, Nrf24Register.SETUP_AW, BYTE_VALUE(Value), NrfStatus);
}
static void _UpdateSetupAwRegister(NrfSpiDevice_ptr device_ptr, NrfReg_SETUP_AW Value, NrfReg_SETUP_AW Mask, NrfReg_STATUS_ptr NrfStatus)
{
	uint8_t old_value;
	
	_ReadSingleByteRegister(device_ptr, Nrf24Register.SETUP_AW, &old_value, NrfStatus);
	_WriteSingleByteRegister(device_ptr, Nrf24Register.SETUP_AW, TWIDDLE(old_value, Value, Mask), NrfStatus);
}
static void _ReadSetupRetrRegister(NrfSpiDevice_ptr device_ptr, NrfReg_SETUP_RETR_ptr Value, NrfReg_STATUS_ptr NrfStatus)
{
	_ReadSingleByteRegister(device_ptr, Nrf24Register.SETUP_RETR, BYTE_ADDRESS(Value), NrfStatus);
}
static void _WriteSetupRetrRegister(NrfSpiDevice_ptr device_ptr, NrfReg_SETUP_RETR Value, NrfReg_STATUS_ptr NrfStatus)
{
	_WriteSingleByteRegister(device_ptr, Nrf24Register.SETUP_RETR, BYTE_VALUE(Value), NrfStatus);
}
static void _UpdateSetupRetrRegister(NrfSpiDevice_ptr device_ptr, NrfReg_SETUP_RETR Value, NrfReg_SETUP_RETR Mask, NrfReg_STATUS_ptr NrfStatus)
{
	uint8_t old_value;
	
	_ReadSingleByteRegister(device_ptr, Nrf24Register.SETUP_RETR, &old_value, NrfStatus);
	_WriteSingleByteRegister(device_ptr, Nrf24Register.SETUP_RETR, TWIDDLE(old_value, Value, Mask), NrfStatus);
}
static void _ReadRfChannelRegister(NrfSpiDevice_ptr device_ptr, NrfReg_RF_CH_ptr Value, NrfReg_STATUS_ptr NrfStatus)
{
	_ReadSingleByteRegister(device_ptr, Nrf24Register.RF_CH, BYTE_ADDRESS(Value), NrfStatus);
}
static void _WriteRfChannelRegister(NrfSpiDevice_ptr device_ptr, NrfReg_RF_CH Value, NrfReg_STATUS_ptr NrfStatus)
{
	_WriteSingleByteRegister(device_ptr, Nrf24Register.RF_CH, BYTE_VALUE(Value), NrfStatus);
}
static void _UpdateRfChannelRegister(NrfSpiDevice_ptr device_ptr, NrfReg_RF_CH Value, NrfReg_RF_CH Mask, NrfReg_STATUS_ptr NrfStatus)
{
	uint8_t old_value;
	
	_ReadSingleByteRegister(device_ptr, Nrf24Register.RF_CH, &old_value, NrfStatus);
	_WriteSingleByteRegister(device_ptr, Nrf24Register.RF_CH, TWIDDLE(old_value, Value, Mask), NrfStatus);
}
static void _ReadRfSetupRegister(NrfSpiDevice_ptr device_ptr, NrfReg_RF_SETUP_ptr Value, NrfReg_STATUS_ptr NrfStatus)
{
	_ReadSingleByteRegister(device_ptr, Nrf24Register.RF_SETUP, BYTE_ADDRESS(Value), NrfStatus);
}
static void _WriteRfSetupRegister(NrfSpiDevice_ptr device_ptr, NrfReg_RF_SETUP Value, NrfReg_STATUS_ptr NrfStatus)
{
	_WriteSingleByteRegister(device_ptr, Nrf24Register.RF_SETUP, BYTE_VALUE(Value), NrfStatus);
}
static void _UpdateRfSetupRegister(NrfSpiDevice_ptr device_ptr, NrfReg_RF_SETUP Value, NrfReg_RF_SETUP Mask, NrfReg_STATUS_ptr NrfStatus)
{
	uint8_t old_value;
	
	_ReadSingleByteRegister(device_ptr, Nrf24Register.RF_SETUP, &old_value, NrfStatus);
	_WriteSingleByteRegister(device_ptr, Nrf24Register.RF_SETUP, TWIDDLE(old_value, Value, Mask), NrfStatus);
}
static void _ReadStatusRegister(NrfSpiDevice_ptr device_ptr, NrfReg_STATUS_ptr Value)
{
	uint8_t command = NrfCommand.NOP | Nrf24Register.STATUS;
	device_ptr->SelectDevice(device_ptr->io_ptr);
	device_ptr->ExchangeBytes(device_ptr->io_ptr, &command, (uint8_t*)Value, 1);
	device_ptr->DeselectDevice(device_ptr->io_ptr);
}
static void _WriteStatusRegister(NrfSpiDevice_ptr device_ptr, NrfReg_STATUS Value, NrfReg_STATUS_ptr NrfStatus)
{
	_WriteSingleByteRegister(device_ptr, Nrf24Register.STATUS, BYTE_VALUE(Value), NrfStatus);
}
static void _UpdateStatusRegister(NrfSpiDevice_ptr device_ptr, NrfReg_STATUS Value, NrfReg_STATUS Mask)
{
	NrfReg_STATUS old_value;
	
	_ReadStatusRegister(device_ptr, &old_value);
	_WriteSingleByteRegister(device_ptr, Nrf24Register.STATUS, TWIDDLE(old_value, Value, Mask), &old_value);
}
static void _ReadObserveTxRegister(NrfSpiDevice_ptr device_ptr, NrfReg_OBSERVE_TX_ptr Value, NrfReg_STATUS_ptr NrfStatus)
{
	_ReadSingleByteRegister(device_ptr, Nrf24Register.OBSERVE_TX, BYTE_ADDRESS(Value), NrfStatus);
}
static void _WriteObserveTxRegister(NrfSpiDevice_ptr device_ptr, NrfReg_OBSERVE_TX Value, NrfReg_STATUS_ptr NrfStatus)
{
	_WriteSingleByteRegister(device_ptr, Nrf24Register.OBSERVE_TX, BYTE_VALUE(Value), NrfStatus);
}
static void _UpdateObserveTxRegister(NrfSpiDevice_ptr device_ptr, NrfReg_OBSERVE_TX Value, NrfReg_OBSERVE_TX Mask, NrfReg_STATUS_ptr NrfStatus)
{
	uint8_t old_value;
	
	_ReadSingleByteRegister(device_ptr, Nrf24Register.OBSERVE_TX, &old_value, NrfStatus);
	_WriteSingleByteRegister(device_ptr, Nrf24Register.OBSERVE_TX, TWIDDLE(old_value, Value, Mask), NrfStatus);
}
static void _ReadRpdRegister(NrfSpiDevice_ptr device_ptr, NrfReg_RPD_ptr Value, NrfReg_STATUS_ptr NrfStatus)
{
	_ReadSingleByteRegister(device_ptr, Nrf24Register.RPD, BYTE_ADDRESS(Value), NrfStatus);
}
static void _WriteRpdRegister(NrfSpiDevice_ptr device_ptr, NrfReg_RPD Value, NrfReg_STATUS_ptr NrfStatus)
{
	_WriteSingleByteRegister(device_ptr, Nrf24Register.RPD, BYTE_VALUE(Value), NrfStatus);
}
static void _UpdateRpdRegister(NrfSpiDevice_ptr device_ptr, NrfReg_RPD Value, NrfReg_RPD Mask, NrfReg_STATUS_ptr NrfStatus)
{
	uint8_t old_value;
	
	_ReadSingleByteRegister(device_ptr, Nrf24Register.RPD, &old_value, NrfStatus);
	_WriteSingleByteRegister(device_ptr, Nrf24Register.RPD, TWIDDLE(old_value, Value, Mask), NrfStatus);
}
static void _ReadLongRxAddrRegister(NrfSpiDevice_ptr device_ptr, NrfReg_RX_ADDR_LONG_ptr Value, uint8_t Pipe, NrfReg_STATUS_ptr NrfStatus)
{
	uint8_t bytes_read;
	_ReadMultiBytesRegister(device_ptr, Nrf24Register.RX_ADDR_P0 + Pipe, Value->value, &bytes_read, NrfStatus);
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

static void _ReadTxAddrRegister(NrfSpiDevice_ptr device_ptr, NrfReg_TX_ADDR_LONG_ptr Value, NrfReg_STATUS_ptr NrfStatus)
{
	uint8_t bytes_read;
	_ReadMultiBytesRegister(device_ptr, Nrf24Register.TX_ADDR, BYTE_ADDRESS(Value), &bytes_read, NrfStatus);
}
static void _WriteTxAddrRegister(NrfSpiDevice_ptr device_ptr, NrfReg_TX_ADDR_LONG Value, NrfReg_STATUS_ptr NrfStatus)
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

static void _UpdateFifoStatusRegister(NrfSpiDevice_ptr device_ptr, NrfReg_FIFO_STATUS Value, NrfReg_FIFO_STATUS Mask, NrfReg_STATUS_ptr NrfStatus)
{
	uint8_t old_value;
	
	_ReadSingleByteRegister(device_ptr, Nrf24Register.FIFO_STATUS, &old_value, NrfStatus);
	_WriteSingleByteRegister(device_ptr, Nrf24Register.FIFO_STATUS, TWIDDLE(old_value, Value, Mask), NrfStatus);
}
static void _ReadDynpdRegister(NrfSpiDevice_ptr device_ptr, NrfReg_DYNPD_ptr Value, NrfReg_STATUS_ptr NrfStatus)
{
	_ReadSingleByteRegister(device_ptr, Nrf24Register.DYNPD, BYTE_ADDRESS(Value), NrfStatus);
}
static void _WriteDynpdRegister(NrfSpiDevice_ptr device_ptr, NrfReg_DYNPD Value, NrfReg_STATUS_ptr NrfStatus)
{
	_WriteSingleByteRegister(device_ptr, Nrf24Register.DYNPD, BYTE_VALUE(Value), NrfStatus);
}
static void _UpdateDynpdRegister(NrfSpiDevice_ptr device_ptr, NrfReg_DYNPD Value, NrfReg_DYNPD Mask, NrfReg_STATUS_ptr NrfStatus)
{
	uint8_t old_value;
	
	_ReadSingleByteRegister(device_ptr, Nrf24Register.DYNPD, &old_value, NrfStatus);
	_WriteSingleByteRegister(device_ptr, Nrf24Register.DYNPD, TWIDDLE(old_value, Value, Mask), NrfStatus);
}
static void _ReadFeatureRegister(NrfSpiDevice_ptr device_ptr, NrfReg_FEATURE_ptr Value, NrfReg_STATUS_ptr NrfStatus)
{
	_ReadSingleByteRegister(device_ptr, Nrf24Register.FEATURE, BYTE_ADDRESS(Value), NrfStatus);
}
static void _WriteFeatureRegister(NrfSpiDevice_ptr device_ptr, NrfReg_FEATURE Value, NrfReg_STATUS_ptr NrfStatus)
{
	_WriteSingleByteRegister(device_ptr, Nrf24Register.FEATURE, BYTE_VALUE(Value), NrfStatus);
}
static void _UpdateFeatureRegister(NrfSpiDevice_ptr device_ptr, NrfReg_FEATURE Value, NrfReg_FEATURE Mask, NrfReg_STATUS_ptr NrfStatus)
{
	uint8_t old_value;
	
	_ReadSingleByteRegister(device_ptr, Nrf24Register.FEATURE, &old_value, NrfStatus);
	_WriteSingleByteRegister(device_ptr, Nrf24Register.FEATURE, TWIDDLE(old_value, Value, Mask), NrfStatus);
}
static void _ReadSingleByteRegister(NrfSpiDevice_ptr device_ptr, uint8_t Register, uint8_t * Value, NrfReg_STATUS_ptr NrfStatus)
{
	uint8_t command = NrfCommand.R_REGISTER | Register;
	
	device_ptr->SelectDevice(device_ptr->io_ptr);
	//device_ptr->ExchangeBytes(device_ptr->io_ptr, &command, (uint8_t*)NrfStatus, 1);
	device_ptr->WriteBytes(device_ptr->io_ptr, &command, 1);
	device_ptr->ReadBytes(device_ptr->io_ptr, Value, 1);
	device_ptr->DeselectDevice(device_ptr->io_ptr);
}
static void _WriteSingleByteRegister(NrfSpiDevice_ptr device_ptr, uint8_t Register, uint8_t Value, NrfReg_STATUS_ptr NrfStatus)
{
	uint8_t command[2] = { NrfCommand.W_REGISTER | Register, Value };
	
	device_ptr->SelectDevice(device_ptr->io_ptr);
	//device_ptr->ExchangeBytes(device_ptr->io_ptr, &command, (uint8_t*)NrfStatus, 1);
	device_ptr->WriteBytes(device_ptr->io_ptr, command, 2);
	device_ptr->DeselectDevice(device_ptr->io_ptr);
}
static void _ReadMultiBytesRegister(NrfSpiDevice_ptr device_ptr, uint8_t Register, uint8_t Value[], uint8_t * BytesRead, NrfReg_STATUS_ptr NrfStatus)
{
	uint8_t command = NrfCommand.R_REGISTER | Register;
	uint8_t width;
	uint8_t bytes;
	NrfReg_SETUP_AW aw;
	
	*BytesRead = 0;
	*NrfStatus = (NrfReg_STATUS){ 0 };
	
	_ReadSetupAwRegister(device_ptr, &aw, NrfStatus);

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

// Set all regsiters to the same values they get set to, when the device is powered off/on
// This function does not actually cycle the power, only simulate it in the sense that
// the device registers are in the same state as if it had been power cycled.
static void _SetToPowerOnResetState(NrfSpiDevice_ptr device_ptr)
{
	NrfReg_STATUS status;
	NrfReg_CONFIG configuration = { 0 };
	NrfReg_EN_AA en_aa = { 0 };
	NrfReg_EN_RXADDR en_rxaddr = { 0 };
	NrfReg_SETUP_AW setup_aw = { 0 };
	NrfReg_SETUP_RETR setup_retr = { 0 };
	NrfReg_RF_CH rf_ch = { 0 };
	NrfReg_RF_SETUP rf_setup = { 0 };
	NrfReg_OBSERVE_TX observe_tx = { 0 };
	NrfReg_RPD rpd = { 0 };
	NrfReg_RX_ADDR_LONG rx_addr_long_p0 = { .value[0] = E7, .value[1] = E7, .value[2] = E7, .value[3] = E7, .value[4] = E7 };
	NrfReg_RX_ADDR_LONG rx_addr_long_p1 = { .value[0] = C2, .value[1] = C2, .value[2] = C2, .value[3] = C2, .value[4] = C2 };
	NrfReg_TX_ADDR_LONG tx_addr_long = { .value[0] = E7, .value[1] = E7, .value[2] = E7, .value[3] = E7, .value[4] = E7 };
	NrfReg_RX_ADDR_SHORT rx_addr_short_p2 = { .value = C3 };
	NrfReg_RX_ADDR_SHORT rx_addr_short_p3 = { .value = C4 };
	NrfReg_RX_ADDR_SHORT rx_addr_short_p4 = { .value = C5 };
	NrfReg_RX_ADDR_SHORT rx_addr_short_p5 = { .value = C6 };
	NrfReg_RX_PW rx_pw = { 0 };
	NrfReg_DYNPD dynpd = { 0 };
	NrfReg_FEATURE feature = { 0 };
	
	configuration.EN_CRC = 1;
	
	en_aa.ENAA_P0 = 1;
	en_aa.ENAA_P1 = 1;
	en_aa.ENAA_P2 = 1;
	en_aa.ENAA_P3 = 1;
	en_aa.ENAA_P4 = 1;
	en_aa.ENAA_P5 = 1;

	en_rxaddr.ERX_P0 = 1;
	en_rxaddr.ERX_P1 = 1;
	
	setup_aw.AW = 3;
	
	setup_retr.ARC = 3;
	
	rf_ch.RF_CH = 2;
	
	rf_setup.RF_DR_HIGH = 1;
	rf_setup.RF_PWR = 3;
	
	rx_addr_short_p2.value = C3;
	rx_addr_short_p3.value = C4;
	rx_addr_short_p4.value = C5;
	rx_addr_short_p5.value = C6;
	
	nrf24_package.SetRegister.CONFIG(device_ptr, configuration, &status);
	nrf24_package.SetRegister.EN_AA(device_ptr, en_aa, &status);
	nrf24_package.SetRegister.EN_RXADDR(device_ptr, en_rxaddr, &status);
	nrf24_package.SetRegister.SETUP_AW(device_ptr, setup_aw, &status);
	nrf24_package.SetRegister.SETUP_RETR(device_ptr, setup_retr, &status);
	nrf24_package.SetRegister.RF_CH(device_ptr, rf_ch, &status);
	nrf24_package.SetRegister.OBSERVE_TX(device_ptr, observe_tx, &status);
	nrf24_package.SetRegister.RPD(device_ptr, rpd, &status);
	nrf24_package.SetRegister.RX_ADDR_LONG(device_ptr, rx_addr_long_p0, 0, &status);
	nrf24_package.SetRegister.RX_ADDR_LONG(device_ptr, rx_addr_long_p1, 1, &status);
	nrf24_package.SetRegister.RX_ADDR_SHORT(device_ptr, rx_addr_short_p2, 2, &status);
	nrf24_package.SetRegister.RX_ADDR_SHORT(device_ptr, rx_addr_short_p3, 3, &status);
	nrf24_package.SetRegister.RX_ADDR_SHORT(device_ptr, rx_addr_short_p4, 4, &status);
	nrf24_package.SetRegister.RX_ADDR_SHORT(device_ptr, rx_addr_short_p5, 5, &status);
	nrf24_package.SetRegister.TX_ADDR_LONG(device_ptr, tx_addr_long, &status);
	nrf24_package.SetRegister.RX_PW(device_ptr, rx_pw, 0, &status);
	nrf24_package.SetRegister.RX_PW(device_ptr, rx_pw, 1, &status);
	nrf24_package.SetRegister.RX_PW(device_ptr, rx_pw, 2, &status);
	nrf24_package.SetRegister.RX_PW(device_ptr, rx_pw, 3, &status);
	nrf24_package.SetRegister.RX_PW(device_ptr, rx_pw, 4, &status);
	nrf24_package.SetRegister.RX_PW(device_ptr, rx_pw, 5, &status);
	nrf24_package.SetRegister.DYNPD(device_ptr, dynpd, &status);
	nrf24_package.SetRegister.FEATURE(device_ptr, feature, &status);
}

static void _ReadAllRegisters(NrfSpiDevice_ptr device_ptr, NrfReg_ALL_REGISTERS_ptr Value, NrfReg_STATUS_ptr NrfStatus)
{
	_ReadConfigRegister(device_ptr, &(Value->Config), NrfStatus);
	_ReadEnAaRegister(device_ptr, &(Value->EnAa), NrfStatus);
	_ReadEnRxAddrRegister(device_ptr, &(Value->RxAddr), NrfStatus);
	_ReadSetupAwRegister(device_ptr, &(Value->SetupAw), NrfStatus);
	_ReadSetupRetrRegister(device_ptr, &(Value->SetupRetr), NrfStatus);
	_ReadRfChannelRegister(device_ptr, &(Value->RfCh), NrfStatus);
	_ReadRfSetupRegister(device_ptr, &(Value->RfSetup), NrfStatus);
	_ReadStatusRegister(device_ptr, &(Value->Status));
	_ReadObserveTxRegister(device_ptr, &(Value->ObserveTx), NrfStatus);
	_ReadRpdRegister(device_ptr, &(Value->Rpd), NrfStatus);
	_ReadLongRxAddrRegister(device_ptr, &(Value->RxAddrP0), 0, NrfStatus);
	_ReadLongRxAddrRegister(device_ptr, &(Value->RxAddrP1), 1, NrfStatus);
	_ReadShortRxAddrRegister(device_ptr, &(Value->RxAddrP2), 2, NrfStatus);
	_ReadShortRxAddrRegister(device_ptr, &(Value->RxAddrP3), 3, NrfStatus);
	_ReadShortRxAddrRegister(device_ptr, &(Value->RxAddrP4), 4, NrfStatus);
	_ReadShortRxAddrRegister(device_ptr, &(Value->RxAddrP5), 5, NrfStatus);
	_ReadTxAddrRegister(device_ptr, &(Value->TxAddr), NrfStatus);
	_ReadRxPwRegister(device_ptr, &(Value->RxPwP0), 0, NrfStatus);
	_ReadRxPwRegister(device_ptr, &(Value->RxPwP1), 0, NrfStatus);
	_ReadRxPwRegister(device_ptr, &(Value->RxPwP2), 0, NrfStatus);
	_ReadRxPwRegister(device_ptr, &(Value->RxPwP3), 0, NrfStatus);
	_ReadRxPwRegister(device_ptr, &(Value->RxPwP4), 0, NrfStatus);
	_ReadRxPwRegister(device_ptr, &(Value->RxPwP5), 0, NrfStatus);
	_ReadFifoStatusRegister(device_ptr, &(Value->FifoStatus), NrfStatus);
	_ReadDynpdRegister(device_ptr, &(Value->Dynpd), NrfStatus);
	_ReadFeatureRegister(device_ptr, &(Value->Feature), NrfStatus);
	

}

static void _Initialize(NrfSpiDevice_ptr device_ptr)
{
	NrfReg_STATUS status = { 0 };
	NrfReg_RX_PW rx_pw = { 0 };
	NrfReg_RF_SETUP rf_setup = { 0 };
	NrfReg_EN_AA en_aa = { 0 };
	NrfReg_EN_RXADDR en_rxaddr = { 0 };
	NrfReg_SETUP_RETR setup_retr = { 0 };
	NrfReg_DYNPD dynpd = { 0 };
	
	// Set channel
	
	/* Set pipeline to max possible 32 bytes */
	
	rx_pw.RX_PW_LEN = 32;
	
	nrf24_package.SetRegister.RX_PW(device_ptr, rx_pw, 0, &status);
	nrf24_package.SetRegister.RX_PW(device_ptr, rx_pw, 1, &status);
	nrf24_package.SetRegister.RX_PW(device_ptr, rx_pw, 2, &status);
	nrf24_package.SetRegister.RX_PW(device_ptr, rx_pw, 3, &status);
	nrf24_package.SetRegister.RX_PW(device_ptr, rx_pw, 4, &status);
	nrf24_package.SetRegister.RX_PW(device_ptr, rx_pw, 5, &status);

	/* Set RF settings (2mbps, output power) */
	
	// 0 and 1 here sets speed to 2 Mbps
	rf_setup.RF_DR_LOW = 0; 
	rf_setup.RF_DR_HIGH = 1; 
	
	// 3 = 0 dBm
	rf_setup.RF_PWR = 3; 
	
	nrf24_package.SetRegister.RF_SETUP(device_ptr, rf_setup, &status);
	
	/* Enable auto-acknowledgment for all pipes */
	
//	en_aa.ENAA_P0 = 1;
//	en_aa.ENAA_P1 = 1;
//	en_aa.ENAA_P2 = 1;
//	en_aa.ENAA_P3 = 1;
//	en_aa.ENAA_P4 = 1;
//	en_aa.ENAA_P5 = 1;
	
	nrf24_package.SetRegister.EN_AA(device_ptr, en_aa, &status);
	
	/* Enable RX addresses */
	
	en_rxaddr.ERX_P0 = 1;
	en_rxaddr.ERX_P0 = 1;
	en_rxaddr.ERX_P0 = 1;
	en_rxaddr.ERX_P0 = 1;
	en_rxaddr.ERX_P0 = 1;
	en_rxaddr.ERX_P0 = 1;

	nrf24_package.SetRegister.EN_RXADDR(device_ptr, en_rxaddr, &status);
	
	/* Auto retransmit delay: 1000 (4x250) us and Up to 15 retransmit trials */
	
	setup_retr.ARC = 15;
	setup_retr.ARD = 3;
	
	nrf24_package.SetRegister.SETUP_RETR(device_ptr, setup_retr, &status);
	
	/* Dynamic length configurations: No dynamic length */
	
	nrf24_package.SetRegister.DYNPD(device_ptr, dynpd, &status);
	
	// Clear FIFOs
	
	nrf24_package.DeviceControl.FlushRxFifo(device_ptr, &status);
	nrf24_package.DeviceControl.FlushTxFifo(device_ptr, &status);
	
	// Clear interrupts
	
	status.RX_DR = 1;
	status.TX_DS = 1;
	status.MAX_RT = 1;
	
	// Since the mask would be the same as the status itself, we can just pass 
	// it in for both args.

	nrf24_package.UpdateRegister.STATUS(device_ptr, status, status);
	
	_PowerUpTx(device_ptr);

}

static void _PowerUpTx(NrfSpiDevice_ptr device_ptr)
{
	NrfReg_STATUS status;
	NrfReg_CONFIG config = { 0 };
	NrfReg_CONFIG config_mask = { 0 };
	NrfReg_RF_CH rf_ch = { 0 };
	
	// Clear interrupts
	
	status.RX_DR = 1;
	status.TX_DS = 1;
	status.MAX_RT = 1;
	
	// Since the mask would be the same as the status itself, we can just pass 
	// it in for both args.
	
	nrf24_package.UpdateRegister.STATUS(device_ptr, status, status);
	
	// Set mode to TX

	config_mask.PWR_UP = 1;
	config_mask.PRIM_RX = 1;
	
	config.PWR_UP = 1;
	config.PRIM_RX = 0;
	
	nrf24_package.UpdateRegister.CONFIG(device_ptr, config, config_mask, &status);
	
	rf_ch.RF_CH = 4; // 2404 MHz
	
	nrf24_package.SetRegister.RF_CH(device_ptr, rf_ch, &status);

}

static void _FlushTxFifo(NrfSpiDevice_ptr device_ptr, NrfReg_STATUS_ptr NrfStatus)
{
	uint8_t command = NrfCommand.FLUSH_TX;
	
	device_ptr->SelectDevice(device_ptr->io_ptr);
	device_ptr->ExchangeBytes(device_ptr->io_ptr, &command, (uint8_t*)NrfStatus, 1);
	device_ptr->DeselectDevice(device_ptr->io_ptr);
}

static void _FlushRxFifo(NrfSpiDevice_ptr device_ptr, NrfReg_STATUS_ptr NrfStatus)
{
	uint8_t command = NrfCommand.FLUSH_RX;

	device_ptr->SelectDevice(device_ptr->io_ptr);
	device_ptr->ExchangeBytes(device_ptr->io_ptr, &command, (uint8_t*)NrfStatus, 1);
	device_ptr->DeselectDevice(device_ptr->io_ptr);
}

static void _WriteTxPayload(NrfSpiDevice_ptr device_ptr, uint8_t * data_ptr, uint8_t data_len, NrfReg_STATUS_ptr NrfStatus)
{
	uint8_t command = NrfCommand.W_TX_PAYLOAD;

	device_ptr->SelectDevice(device_ptr->io_ptr);
	device_ptr->ExchangeBytes(device_ptr->io_ptr, &command, (uint8_t*)NrfStatus, 1);
	device_ptr->WriteBytes(device_ptr->io_ptr, data_ptr, data_len);
	device_ptr->DeselectDevice(device_ptr->io_ptr);
}
