// Should always be the very first line in the package implementation source file.
#define nrf24_package_implementer

// Include all required platform headers.
#include <stdbool.h>

#include <stdint.h>
#include <stdio.h>
#include <stm32f4xx_hal.h>

// Include all required library headers
#include <nrf24_hal_support.library.h>
#include <nrf24_package.library.h>

public const nrf24_register_names Nrf24Register = // We use this because we fan then qualify members for readability
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
public const nrf24_command_names NrfCommand = // We use this because we fan then qualify members for readability
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

// Declare all static (private) functions

private void ReadConfigRegister(NrfDevice_ptr device_ptr, NrfReg_CONFIG_ptr Value, NrfReg_STATUS_ptr NrfStatus);
private void WriteConfigRegister(NrfDevice_ptr device_ptr, NrfReg_CONFIG Value, NrfReg_STATUS_ptr NrfStatus);
private void UpdateConfigRegister(NrfDevice_ptr device_ptr, NrfReg_CONFIG Value, NrfReg_CONFIG Mask, NrfReg_STATUS_ptr NrfStatus);
private void ReadEnAaRegister(NrfDevice_ptr device_ptr, NrfReg_EN_AA_ptr Value, NrfReg_STATUS_ptr NrfStatus);
private void WriteEnAaRegister(NrfDevice_ptr device_ptr, NrfReg_EN_AA Value, NrfReg_STATUS_ptr NrfStatus);
private void UpdateEnAaRegister(NrfDevice_ptr device_ptr, NrfReg_EN_AA Value, NrfReg_EN_AA Mask, NrfReg_STATUS_ptr NrfStatus);
private void ReadEnRxAddrRegister(NrfDevice_ptr device_ptr, NrfReg_EN_RXADDR_ptr Value, NrfReg_STATUS_ptr NrfStatus);
private void WriteEnRxAddrRegister(NrfDevice_ptr device_ptr, NrfReg_EN_RXADDR Value, NrfReg_STATUS_ptr NrfStatus);
private void UpdateEnRxAddrRegister(NrfDevice_ptr device_ptr, NrfReg_EN_RXADDR Value, NrfReg_EN_RXADDR Mask, NrfReg_STATUS_ptr NrfStatus);
private void ReadSetupAwRegister(NrfDevice_ptr device_ptr, NrfReg_SETUP_AW_ptr Value, NrfReg_STATUS_ptr NrfStatus);
private void WriteSetupAwRegister(NrfDevice_ptr device_ptr, NrfReg_SETUP_AW Value, NrfReg_STATUS_ptr NrfStatus);
private void UpdateSetupAwRegister(NrfDevice_ptr device_ptr, NrfReg_SETUP_AW Value, NrfReg_SETUP_AW Mask, NrfReg_STATUS_ptr NrfStatus);
private void ReadSetupRetrRegister(NrfDevice_ptr device_ptr, NrfReg_SETUP_RETR_ptr Value, NrfReg_STATUS_ptr NrfStatus);
private void WriteSetupRetrRegister(NrfDevice_ptr device_ptr, NrfReg_SETUP_RETR Value, NrfReg_STATUS_ptr NrfStatus);
private void UpdateSetupRetrRegister(NrfDevice_ptr device_ptr, NrfReg_SETUP_RETR Value, NrfReg_SETUP_RETR Mask, NrfReg_STATUS_ptr NrfStatus);
private void ReadRfChannelRegister(NrfDevice_ptr device_ptr, NrfReg_RF_CH_ptr Value, NrfReg_STATUS_ptr NrfStatus);
private void WriteRfChannelRegister(NrfDevice_ptr device_ptr, NrfReg_RF_CH Value, NrfReg_STATUS_ptr NrfStatus);
private void UpdateRfChannelRegister(NrfDevice_ptr device_ptr, NrfReg_RF_CH Value, NrfReg_RF_CH Mask, NrfReg_STATUS_ptr NrfStatus);
private void ReadRfSetupRegister(NrfDevice_ptr device_ptr, NrfReg_RF_SETUP_ptr Value, NrfReg_STATUS_ptr NrfStatus);
private void WriteRfSetupRegister(NrfDevice_ptr device_ptr, NrfReg_RF_SETUP Value, NrfReg_STATUS_ptr NrfStatus);
private void UpdateRfSetupRegister(NrfDevice_ptr device_ptr, NrfReg_RF_SETUP Value, NrfReg_RF_SETUP Mask, NrfReg_STATUS_ptr NrfStatus);
private void ReadStatusRegister(NrfDevice_ptr device_ptr, NrfReg_STATUS_ptr Value);
private void WriteStatusRegister(NrfDevice_ptr device_ptr, NrfReg_STATUS Value, NrfReg_STATUS_ptr NrfStatus);
private void UpdateStatusRegister(NrfDevice_ptr device_ptr, NrfReg_STATUS Value, NrfReg_STATUS Mask);
private void ReadObserveTxRegister(NrfDevice_ptr device_ptr, NrfReg_OBSERVE_TX_ptr Value, NrfReg_STATUS_ptr NrfStatus);
private void WriteObserveTxRegister(NrfDevice_ptr device_ptr, NrfReg_OBSERVE_TX Value, NrfReg_STATUS_ptr NrfStatus);
private void UpdateObserveTxRegister(NrfDevice_ptr device_ptr, NrfReg_OBSERVE_TX Value, NrfReg_OBSERVE_TX Mask, NrfReg_STATUS_ptr NrfStatus);
private void ReadRpdRegister(NrfDevice_ptr device_ptr, NrfReg_RPD_ptr Value, NrfReg_STATUS_ptr NrfStatus);
private void WriteRpdRegister(NrfDevice_ptr device_ptr, NrfReg_RPD Value, NrfReg_STATUS_ptr NrfStatus);
private void UpdateRpdRegister(NrfDevice_ptr device_ptr, NrfReg_RPD Value, NrfReg_RPD Mask, NrfReg_STATUS_ptr NrfStatus);
private void ReadLongRxAddrRegister(NrfDevice_ptr device_ptr, NrfReg_RX_ADDR_LONG_ptr Value, uint8_t Pipe, NrfReg_STATUS_ptr NrfStatus);
private void WriteLongRxAddrRegister(NrfDevice_ptr device_ptr, NrfReg_RX_ADDR_LONG Value, uint8_t Pipe, NrfReg_STATUS_ptr NrfStatus);
private void ReadShortRxAddrRegister(NrfDevice_ptr device_ptr, NrfReg_RX_ADDR_SHORT_ptr Value, uint8_t Pipe, NrfReg_STATUS_ptr NrfStatus);
private void WriteShortRxAddrRegister(NrfDevice_ptr device_ptr, NrfReg_RX_ADDR_SHORT Value, uint8_t Pipe, NrfReg_STATUS_ptr NrfStatus);
private void ReadTxAddrRegister(NrfDevice_ptr device_ptr, NrfReg_TX_ADDR_LONG_ptr Value, NrfReg_STATUS_ptr NrfStatus);
private void WriteTxAddrRegister(NrfDevice_ptr device_ptr, NrfReg_TX_ADDR_LONG Value, NrfReg_STATUS_ptr NrfStatus);
private void ReadRxPwRegister(NrfDevice_ptr device_ptr, NrfReg_RX_PW_ptr Value, uint8_t Pipe, NrfReg_STATUS_ptr NrfStatus);
private void WriteRxPwRegister(NrfDevice_ptr device_ptr, NrfReg_RX_PW Value, uint8_t Pipe, NrfReg_STATUS_ptr NrfStatus);
private void ReadFifoStatusRegister(NrfDevice_ptr device_ptr, NrfReg_FIFO_STATUS_ptr Value, NrfReg_STATUS_ptr NrfStatus);
private void WriteFifoStatusRegister(NrfDevice_ptr device_ptr, NrfReg_FIFO_STATUS Value, NrfReg_STATUS_ptr NrfStatus);
private void UpdateFifoStatusRegister(NrfDevice_ptr device_ptr, NrfReg_FIFO_STATUS Value, NrfReg_FIFO_STATUS Mask, NrfReg_STATUS_ptr NrfStatus);
private void ReadDynpdRegister(NrfDevice_ptr device_ptr, NrfReg_DYNPD_ptr Value, NrfReg_STATUS_ptr NrfStatus);
private void WriteDynpdRegister(NrfDevice_ptr device_ptr, NrfReg_DYNPD Value, NrfReg_STATUS_ptr NrfStatus);
private void UpdateDynpdRegister(NrfDevice_ptr device_ptr, NrfReg_DYNPD Value, NrfReg_DYNPD Mask, NrfReg_STATUS_ptr NrfStatus);
private void ReadFeatureRegister(NrfDevice_ptr device_ptr, NrfReg_FEATURE_ptr Value, NrfReg_STATUS_ptr NrfStatus);
private void WriteFeatureRegister(NrfDevice_ptr device_ptr, NrfReg_FEATURE Value, NrfReg_STATUS_ptr NrfStatus);
private void UpdateFeatureRegister(NrfDevice_ptr device_ptr, NrfReg_FEATURE Value, NrfReg_FEATURE Mask, NrfReg_STATUS_ptr NrfStatus);
private void ReadSingleByteRegister(NrfDevice * device_ptr, uint8_t Register, uint8_t * Value, NrfReg_STATUS_ptr NrfStatus);
private void WriteSingleByteRegister(NrfDevice_ptr device_ptr, uint8_t Register, uint8_t Value, NrfReg_STATUS_ptr NrfStatus);
private void ReadMultiBytesRegister(NrfDevice_ptr device_ptr, uint8_t Register, uint8_t Value[], uint8_t * BytesRead, NrfReg_STATUS_ptr NrfStatu);
private void WriteMultiBytesRegister(NrfDevice_ptr device_ptr, uint8_t Register, uint8_t Value[], uint8_t * BytesWritten, NrfReg_STATUS_ptr NrfStatus);
private void ResetDevice(NrfDevice_ptr device_ptr);
private void PowerDown(NrfDevice_ptr device_ptr);
private void FLUSH_TX(NrfDevice_ptr device_ptr, NrfReg_STATUS_ptr NrfStatus);
private void FLUSH_RX(NrfDevice_ptr device_ptr, NrfReg_STATUS_ptr NrfStatus);
private void ReadAllRegisters(NrfDevice_ptr device_ptr, NrfReg_ALL_REGISTERS_ptr Value, NrfReg_STATUS_ptr NrfStatus);
private void W_TX_PAYLOAD(NrfDevice_ptr, uint8_t * data_ptr, uint8_t data_len, NrfReg_STATUS_ptr NrfStatus);
private void R_RX_PAYLOAD(NrfDevice_ptr, uint8_t * data_ptr, uint8_t data_len, NrfReg_STATUS_ptr NrfStatus);
private void ConfigureTransmitter(NrfDevice_ptr device_ptr, bool auto_ack);
private void ConfigureReceiver(NrfDevice_ptr device_ptr, uint8_t address[5], uint8_t pipe, bool auto_ack, uint8_t payload_size);
private void ConfigureRadio(NrfDevice_ptr device_ptr, uint8_t channel, uint8_t power, uint8_t rate, bool auto_ack);
private void PulseCE(NrfDevice_ptr device_ptr);
private void SendPayload(NrfDevice_ptr device_ptr, uint8_t * buffer, uint8_t size);
private void PowerUpDevice(NrfDevice_ptr device_ptr);
private void wait_for_interrupt(volatile NrfInterrupt_ptr state_ptr, int32_t max_spins);
private void confirm_interrupt(volatile NrfInterrupt_ptr state_ptr);

private void SpinForTxInterrupt(NrfDevice_ptr, int32_t);
private void ConfirmTxInterrupt(NrfDevice_ptr);
private void WaitForRxInterrupt(NrfDevice_ptr, int32_t);
private void ConfirmRxInterrupt(NrfDevice_ptr);

private void GetDefaultAddress(uint8_t address[5]);
private void DumpRegisters(NrfDevice_ptr device_ptr);
private void SetTransmitAddress(NrfDevice_ptr device_ptr, uint8_t address[5]);
private void SetReceiveAddressLong(NrfDevice_ptr device_ptr, uint8_t address[5], uint8_t pipe); // pipes 0 and 1
private void SetReceiveAddressShort(NrfDevice_ptr device_ptr, uint8_t address, uint8_t pipe); // pipes 2,3,4 and 5
private void SetAutoAck(NrfDevice_ptr device_ptr, uint8_t pipe, bool state);
private void SetPipeState(NrfDevice_ptr device_ptr, uint8_t pipe, bool state);
private void ClearInterruptFlags(NrfDevice_ptr device_ptr, bool RX_DR, bool TX_DS, bool MAX_RT);
private void SetReceiveMode(NrfDevice_ptr device_ptr);
private void SetTransmitMode(NrfDevice_ptr device_ptr);
private void MaskInterrupts(NrfDevice_ptr device_ptr, bool RX_DR, bool TX_DS, bool MAX_RT);
private void SetReceivePayloadSize(NrfDevice_ptr device_ptr, uint8_t payload_size, uint8_t pipe);
private void SetCRC(NrfDevice_ptr device_ptr, bool enable, bool size);
private void SetAutoAckRetries(NrfDevice_ptr device_ptr, uint8_t delay, uint8_t max);
private void SetAddressWidth(NrfDevice_ptr device_ptr, uint8_t width);


// Declare the global library interface with same name as library

public const nrf24_package_struct nrf24_package =
{ 
	.Read = 
	{     
		.CONFIG = ReadConfigRegister,
		.EN_AA = ReadEnAaRegister,
		.EN_RXADDR = ReadEnRxAddrRegister,
		.SETUP_AW = ReadSetupAwRegister,
		.SETUP_RETR = ReadSetupRetrRegister,
		.RF_CH = ReadRfChannelRegister,
		.RF_SETUP = ReadRfSetupRegister,
		.STATUS = ReadStatusRegister,
		.OBSERVE_TX = ReadObserveTxRegister,
		.RPD = ReadRpdRegister,
		.RX_ADDR_LONG = ReadLongRxAddrRegister,
		.RX_ADDR_SHORT = ReadShortRxAddrRegister,
		.TX_ADDR_LONG = ReadTxAddrRegister,
		.RX_PW = ReadRxPwRegister,
		.FIFO_STATUS = ReadFifoStatusRegister,
		.DYNPD = ReadDynpdRegister,
		.FEATURE = ReadFeatureRegister,
		.ALL_REGISTERS = ReadAllRegisters,
	},
	.Write = 
	{ 
		.CONFIG = WriteConfigRegister,
		.EN_AA = WriteEnAaRegister,
		.EN_RXADDR = WriteEnRxAddrRegister,
		.SETUP_AW = WriteSetupAwRegister,
		.SETUP_RETR = WriteSetupRetrRegister,
		.RF_CH = WriteRfChannelRegister,
		.RF_SETUP = WriteRfSetupRegister,
		.STATUS = WriteStatusRegister,
		.OBSERVE_TX = WriteObserveTxRegister,
		.RPD = WriteRpdRegister,
		.RX_ADDR_LONG = WriteLongRxAddrRegister,
		.RX_ADDR_SHORT = WriteShortRxAddrRegister,
		.TX_ADDR_LONG = WriteTxAddrRegister,
		.RX_PW = WriteRxPwRegister,
		.FIFO_STATUS = WriteFifoStatusRegister,
		.DYNPD = WriteDynpdRegister,
		.FEATURE = WriteFeatureRegister,
	},
	.Update =
	{ 
		.CONFIG = UpdateConfigRegister,
		.EN_AA = UpdateEnAaRegister,
		.EN_RXADDR = UpdateEnRxAddrRegister,
		.SETUP_AW = UpdateSetupAwRegister,
		.SETUP_RETR = UpdateSetupRetrRegister,
		.RF_CH = UpdateRfChannelRegister,
		.RF_SETUP = UpdateRfSetupRegister,
		.STATUS = UpdateStatusRegister,
		.OBSERVE_TX = UpdateObserveTxRegister,
		.RPD = UpdateRpdRegister,
		.FIFO_STATUS = UpdateFifoStatusRegister,
		.DYNPD = UpdateDynpdRegister,
		.FEATURE = UpdateFeatureRegister,
	},
	.Action =
	{ 
		// This is a misnomer, but we will use this to power up the device in RX mode.
		.PowerDown = PowerDown,
		.PowerUpDevice = PowerUpDevice,
		.ResetDevice = ResetDevice,
		.ConfigureTransmitter = ConfigureTransmitter,
		.ConfigureReceiver = ConfigureReceiver,
		.ConfigureRadio = ConfigureRadio,
		.PulseCE = PulseCE,
		.SendPayload = SendPayload,
		.SpinForTxInterrupt = SpinForTxInterrupt,
		.ConfirmTxInterrupt = ConfirmTxInterrupt,
		.WaitForRxInterrupt = WaitForRxInterrupt,
		.ConfirmRxInterrupt = ConfirmRxInterrupt,
		.GetDefaultAddress = GetDefaultAddress,
		.DumpRegisters = DumpRegisters,
		.SetTransmitAddress = SetTransmitAddress,
		.SetReceiveAddressLong = SetReceiveAddressLong,
		.SetReceiveAddressShort = SetReceiveAddressShort,
		.SetAutoAck = SetAutoAck,
		.SetPipeState = SetPipeState,
		.ClearInterruptFlags = ClearInterruptFlags,
		.SetReceiveMode = SetReceiveMode,
		.SetTransmitMode = SetTransmitMode,
		.MaskInterrupts = MaskInterrupts,
		.SetReceivePayloadSize = SetReceivePayloadSize,
		.SetCRC = SetCRC,
		.SetAutoAckRetries = SetAutoAckRetries,
		.SetAddressWidth = SetAddressWidth,

	},
	.Command =
	{ 
		.FLUSH_TX = FLUSH_TX,
		.FLUSH_RX = FLUSH_RX,
		 // TODO add support for REUSE_TX_PL as well.
		.W_TX_PAYLOAD = W_TX_PAYLOAD,
		.R_RX_PAYLOAD = R_RX_PAYLOAD
	},
	.EmptyRegister =
	{ 
		.STATUS = (NrfReg_STATUS)  { 0 }
	}
};

// Implementation 

private void SetReceiveAddressLong(NrfDevice_ptr device_ptr, uint8_t address[5], uint8_t pipe)
{
	NrfReg_STATUS status;
	NrfReg_RX_ADDR_LONG rx_addr = { 0 };
	
	rx_addr.value[0] = address[0];
	rx_addr.value[1] = address[1];
	rx_addr.value[2] = address[2];
	rx_addr.value[3] = address[3];
	rx_addr.value[4] = address[4];
	
	nrf24_package.Write.RX_ADDR_LONG(device_ptr, rx_addr, pipe, &status);
}
private void SetReceiveAddressShort(NrfDevice_ptr device_ptr, uint8_t address, uint8_t pipe)
{
	NrfReg_STATUS status;
	NrfReg_RX_ADDR_SHORT rx_addr = { 0 };
	
	rx_addr.value = address;
	nrf24_package.Write.RX_ADDR_SHORT(device_ptr, rx_addr, pipe, &status);
}
private void SetAutoAck(NrfDevice_ptr device_ptr, uint8_t pipe, bool state)
{
	NrfReg_STATUS status;
	NrfReg_EN_AA en_aa = { 0 };
	NrfReg_EN_AA mask = { 0 };
	
	switch (pipe)
	{
		
	case 0:
		en_aa.ENAA_P0 = state;	
		mask.ENAA_P0 = 1;
		break;
	case 1:
		en_aa.ENAA_P1 = state;	
		mask.ENAA_P1 = 1;
		break;
	case 2:
		en_aa.ENAA_P2 = state;	
		mask.ENAA_P2 = 1;
		break;
	case 3:
		en_aa.ENAA_P3 = state;	
		mask.ENAA_P3 = 1;
		break;
	case 4:
		en_aa.ENAA_P4 = state;	
		mask.ENAA_P4 = 1;
		break;
	case 5:
		en_aa.ENAA_P5 = state;	
		mask.ENAA_P5 = 1;
		break;
	}
	
	nrf24_package.Update.EN_AA(device_ptr, en_aa,mask, &status);
}
private void SetPipeState(NrfDevice_ptr device_ptr, uint8_t pipe, bool state)
{
	NrfReg_STATUS status;
	NrfReg_EN_RXADDR en_rxaddr = { 0 };
	NrfReg_EN_RXADDR mask = { 0 };
	
	switch (pipe)
	{
		
	case 0:
		en_rxaddr.ERX_P0 = state;	
		mask.ERX_P0 = 1;
		break;
	case 1:
		en_rxaddr.ERX_P1 = state;	
		mask.ERX_P1 = 1;
		break;
	case 2:
		en_rxaddr.ERX_P2 = state;	
		mask.ERX_P2 = 1;
		break;
	case 3:
		en_rxaddr.ERX_P3 = state;	
		mask.ERX_P3 = 1;
		break;
	case 4:
		en_rxaddr.ERX_P4 = state;	
		mask.ERX_P4 = 1;
		break;
	case 5:
		en_rxaddr.ERX_P5 = state;	
		mask.ERX_P5 = 1;
		break;
	}
	
	nrf24_package.Update.EN_RXADDR(device_ptr, en_rxaddr, mask, &status);
}
private void SetTransmitAddress(NrfDevice_ptr device_ptr, uint8_t address[5])
{
	NrfReg_STATUS status;
	NrfReg_TX_ADDR_LONG tx_addr = { 0 };
	
	tx_addr.value[0] = address[0];
	tx_addr.value[1] = address[1];
	tx_addr.value[2] = address[2];
	tx_addr.value[3] = address[3];
	tx_addr.value[4] = address[4];

	nrf24_package.Write.TX_ADDR_LONG(device_ptr, tx_addr, &status);

}
private void DumpRegisters(NrfDevice_ptr device_ptr)
{
	NrfReg_ALL_REGISTERS all = { 0 };
	NrfReg_STATUS status;

	nrf24_package.Read.ALL_REGISTERS(device_ptr, &all, &status);

	printf("NRF24L01+ REGISTER DUMP\n");
	printf(" CONFIG (%02X)\n",all.CONFIG);
	printf("  RESERVED    = %d\n", all.CONFIG.RESERVED);
	printf("  MASK_RX_DR  = %d\n", all.CONFIG.MASK_RX_DR);
	printf("  MASK_TX_DS  = %d\n", all.CONFIG.MASK_TX_DS);
	printf("  MASK_MAX_RT = %d\n", all.CONFIG.MASK_MAX_RT);
	printf("  EN_CRC      = %d\n", all.CONFIG.EN_CRC);
	printf("  CRCO        = %d\n", all.CONFIG.CRCO);
	printf("  PWR_UP      = %d\n", all.CONFIG.PWR_UP);
	printf("  PRIM_RX     = %d\n", all.CONFIG.PRIM_RX);
	printf("\n");
	
	printf(" EN_AA (%02X)\n",all.EN_AA);
	printf("  RESERVED    = %d\n", all.EN_AA.RESERVED);
	printf("  ENAA_P5     = %d\n", all.EN_AA.ENAA_P5);
	printf("  ENAA_P4     = %d\n", all.EN_AA.ENAA_P4);
	printf("  ENAA_P3     = %d\n", all.EN_AA.ENAA_P3);
	printf("  ENAA_P2     = %d\n", all.EN_AA.ENAA_P2);
	printf("  ENAA_P1     = %d\n", all.EN_AA.ENAA_P1);
	printf("  ENAA_P0     = %d\n", all.EN_AA.ENAA_P0);
	printf("\n");

	printf(" EN_RXADDR (%02X)\n",all.EN_RXADDR);
	printf("  RESERVED    = %d\n", all.EN_RXADDR.RESERVED);
	printf("  ERX_P5      = %d\n", all.EN_RXADDR.ERX_P5);
	printf("  ERX_P4      = %d\n", all.EN_RXADDR.ERX_P4);
	printf("  ERX_P3      = %d\n", all.EN_RXADDR.ERX_P3);
	printf("  ERX_P2      = %d\n", all.EN_RXADDR.ERX_P2);
	printf("  ERX_P1      = %d\n", all.EN_RXADDR.ERX_P1);
	printf("  ERX_P0      = %d\n", all.EN_RXADDR.ERX_P0);
	printf("\n");

	printf(" SETUP_AW (%02X)\n",all.SETUP_AW);
	printf("  RESERVED    = %d\n", all.SETUP_AW.RESERVED);
	printf("  AW          = %d\n", all.SETUP_AW.AW);
	printf("\n");

	printf(" SETUP_RETR (%02X)\n", all.SETUP_RETR);
	printf("  ARD         = %d\n", all.SETUP_RETR.ARD);
	printf("  ARC         = %d\n", all.SETUP_RETR.ARC);
	printf("\n");

	printf(" RF_CH (%02X)\n", all.RF_CH);
	printf("  RESERVED    = %d\n", all.RF_CH.RESERVED);
	printf("  RF_CH       = %d\n", all.RF_CH.RF_CH);
	printf("\n");

	printf(" RF_SETUP (%02X)\n",all.RF_SETUP);
	printf("  CONT_WAVE   = %d\n", all.RF_SETUP.CONT_WAVE);
	printf("  RESERVED    = %d\n", all.RF_SETUP.RESERVED);
	printf("  RF_DR_LOW   = %d\n", all.RF_SETUP.RF_DR_LOW);
	printf("  PLL_LOCK    = %d\n", all.RF_SETUP.PLL_LOCK);
	printf("  RF_DR_HIGH  = %d\n", all.RF_SETUP.RF_DR_HIGH);
	printf("  RF_PWR      = %d\n", all.RF_SETUP.RF_PWR);
	printf("  OBSOLETE    = %d\n", all.RF_SETUP.OBSOLETE);
	printf("\n");

	printf(" STATUS (%02X)\n",all.STATUS);
	printf("  RESERVED    = %d\n", all.STATUS.RESERVED);
	printf("  RX_DR       = %d\n", all.STATUS.RX_DR);
	printf("  TX_DS       = %d\n", all.STATUS.TX_DS);
	printf("  MAX_RT      = %d\n", all.STATUS.MAX_RT);
	printf("  RX_P_NO     = %d\n", all.STATUS.RX_P_NO);
	printf("  TX_FULL     = %d\n", all.STATUS.TX_FULL);
	printf("\n");

	printf(" OBSERVE_TX (%02X)\n",all.OBSERVE_TX);
	printf("  PLOS_CNT    = %d\n", all.OBSERVE_TX.PLOS_CNT);
	printf("  ARC_CNT     = %d\n", all.OBSERVE_TX.ARC_CNT);
	printf("\n");

	printf(" RPD (%02X)\n",all.RPD);
	printf("  RESERVED    = %d\n", all.RPD.RESERVED);
	printf("  RPD         = %d\n", all.RPD.RPD);
	printf("\n");

	printf(" RX_ADDR_P0   =  %02X  %02X  %02X  %02X  %02X\n", all.RX_ADDR_P0.value[0], all.RX_ADDR_P0.value[1], all.RX_ADDR_P0.value[2], all.RX_ADDR_P0.value[3], all.RX_ADDR_P0.value[4]);
	printf(" RX_ADDR_P1   =  %02X  %02X  %02X  %02X  %02X\n", all.RX_ADDR_P1.value[0], all.RX_ADDR_P1.value[1], all.RX_ADDR_P1.value[2], all.RX_ADDR_P1.value[3], all.RX_ADDR_P1.value[4]);
	printf(" RX_ADDR_P2   = [%02X  %02X  %02X  %02X] %02X\n", all.RX_ADDR_P1.value[0], all.RX_ADDR_P1.value[1], all.RX_ADDR_P1.value[2], all.RX_ADDR_P1.value[3], all.RX_ADDR_P2.value);
	printf(" RX_ADDR_P3   = [%02X  %02X  %02X  %02X] %02X\n", all.RX_ADDR_P1.value[0], all.RX_ADDR_P1.value[1], all.RX_ADDR_P1.value[2], all.RX_ADDR_P1.value[3], all.RX_ADDR_P3.value);
	printf(" RX_ADDR_P4   = [%02X  %02X  %02X  %02X] %02X\n", all.RX_ADDR_P1.value[0], all.RX_ADDR_P1.value[1], all.RX_ADDR_P1.value[2], all.RX_ADDR_P1.value[3], all.RX_ADDR_P4.value);
	printf(" RX_ADDR_P5   = [%02X  %02X  %02X  %02X] %02X\n", all.RX_ADDR_P1.value[0], all.RX_ADDR_P1.value[1], all.RX_ADDR_P1.value[2], all.RX_ADDR_P1.value[3], all.RX_ADDR_P5.value);
	printf("\n");

	printf(" TX_ADDR      =  %02X  %02X  %02X  %02X  %02X\n", all.TX_ADDR.value[0], all.TX_ADDR.value[1], all.TX_ADDR.value[2], all.TX_ADDR.value[3], all.TX_ADDR.value[4]);
	printf("\n");

	printf(" RX_PW_0 (%02X)\n",all.RX_PW_P0);
	printf("  RESERVED    = %d\n", all.RX_PW_P0.RESERVED);
	printf("  RX_PW_P0    = %d\n", all.RX_PW_P0.RX_PW_LEN);
	printf("\n");

	printf(" RX_PW_1 (%02X)\n", all.RX_PW_P1);
	printf("  RESERVED    = %d\n", all.RX_PW_P1.RESERVED);
	printf("  RX_PW_P1    = %d\n", all.RX_PW_P1.RX_PW_LEN);
	printf("\n");
	
	printf(" RX_PW_2 (%02X)\n", all.RX_PW_P2);
	printf("  RESERVED    = %d\n", all.RX_PW_P2.RESERVED);
	printf("  RX_PW_P2    = %d\n", all.RX_PW_P2.RX_PW_LEN);
	printf("\n");
	
	printf(" RX_PW_3 (%02X)\n", all.RX_PW_P3);
	printf("  RESERVED    = %d\n", all.RX_PW_P3.RESERVED);
	printf("  RX_PW_P3    = %d\n", all.RX_PW_P3.RX_PW_LEN);
	printf("\n");
	
	printf(" RX_PW_4 (%02X)\n", all.RX_PW_P4);
	printf("  RESERVED    = %d\n", all.RX_PW_P4.RESERVED);
	printf("  RX_PW_P4    = %d\n", all.RX_PW_P4.RX_PW_LEN);
	printf("\n");
	
	printf(" RX_PW_5 (%02X)\n", all.RX_PW_P5);
	printf("  RESERVED    = %d\n", all.RX_PW_P5.RESERVED);
	printf("  RX_PW_P5    = %d\n", all.RX_PW_P5.RX_PW_LEN);
	printf("\n");

	printf(" FIFO_STATUS (%02X)\n", all.FIFO_STATUS);
	printf("  RESERVED    = %d\n", all.FIFO_STATUS.RESERVED0);
	printf("  TX_REUSE    = %d\n", all.FIFO_STATUS.TX_REUSE);
	printf("  TX_FULL     = %d\n", all.FIFO_STATUS.TX_FULL);
	printf("  TX_EMPTY    = %d\n", all.FIFO_STATUS.TX_EMPTY);
	printf("  RESERVED    = %d\n", all.FIFO_STATUS.RESERVED1);
	printf("  RX_FULL     = %d\n", all.FIFO_STATUS.RX_FULL);
	printf("  RX_EMPTY    = %d\n", all.FIFO_STATUS.RX_EMPTY);
	printf("\n");
	
	printf(" DYNPD (%02X)\n", all.DYNPD);
	printf("  RESERVED    = %d\n", all.DYNPD.RESERVED);
	printf("  DPL_P5      = %d\n", all.DYNPD.DPL_P5);
	printf("  DPL_P4      = %d\n", all.DYNPD.DPL_P4);
	printf("  DPL_P3      = %d\n", all.DYNPD.DPL_P3);
	printf("  DPL_P2      = %d\n", all.DYNPD.DPL_P2);
	printf("  DPL_P1      = %d\n", all.DYNPD.DPL_P1);
	printf("  DPL_P0      = %d\n", all.DYNPD.DPL_P0);
	printf("\n");

	printf(" FEATURE (%02X)\n", all.FEATURE);
	printf("  RESERVED    = %d\n", all.FEATURE.RESERVED);
	printf("  EN_DPL      = %d\n", all.FEATURE.EN_DPL);
	printf("  EN_ACK_PAY  = %d\n", all.FEATURE.EN_ACK_PAY);
	printf("  EN_DYN_ACK  = %d\n", all.FEATURE.EN_DYN_ACK);
	printf("\n");

}
private void GetDefaultAddress(uint8_t address[5])
{
	uint32_t id1 = *(uint32_t*)0x1FFF7A10; // First 32 bits
	uint32_t id2 = *(uint32_t*)0x1FFF7A14; // Second 32 bits
	uint32_t id3 = *(uint32_t*)0x1FFF7A18; // Last 32 bits

	address[4] = 0xAA;
	address[3] = (id2 & 0xFF000000) >> 24;
	address[2] = (id2 & 0x00FF0000) >> 16;
	address[1] = (id2 & 0x0000FF00) >> 8;
	address[0] = (id2 & 0x000000FF) >> 0;
}
private void ConfirmTxInterrupt(NrfDevice_ptr device_ptr)
{
	confirm_interrupt(&(device_ptr->tx_interrupt));
}
private void ConfirmRxInterrupt(NrfDevice_ptr device_ptr)
{
	confirm_interrupt(&(device_ptr->rx_interrupt));
}
private void WaitForRxInterrupt(NrfDevice_ptr device_ptr, int32_t max_spins)
{
	wait_for_interrupt(&(device_ptr->rx_interrupt), max_spins);
}
private void SpinForTxInterrupt(NrfDevice_ptr device_ptr, int32_t max_spins)
{
	wait_for_interrupt(&(device_ptr->tx_interrupt), max_spins);
}
private void SendPayload(NrfDevice_ptr device_ptr, uint8_t * buffer, uint8_t size)
{
	NrfReg_STATUS status;

	if (size == 0 || size > 32)
	{
		device_ptr->FaultHandler(device_ptr, INVALID_PAYLOAD_SIZE);
		return;
	}
	

	nrf24_package.Command.W_TX_PAYLOAD(device_ptr, buffer, size, &status);
	
	// We must now pulse CE high for > 10 uS for RF transmision to begin. See Page 23 of chip manual.
	
	nrf24_package.Action.PulseCE(device_ptr);
	
	device_ptr->tx_count++;

}
private void PulseCE(NrfDevice_ptr device_ptr)
{
	nrf24_hal_support.Activate(device_ptr);
	
	// Given the brevity of the pulse at just over 10 uS, it is
	// fine to "poll" here it only spins a few times so isn't that big a cost.
		
	__HAL_TIM_SET_COUNTER(&(device_ptr->pulse_timer), 0); // Reset the timer
	while (__HAL_TIM_GET_COUNTER(&(device_ptr->pulse_timer)) < 12) 
	{
		;
	}
		
	nrf24_hal_support.Deactivate(device_ptr);
}
private void ReadConfigRegister(NrfDevice_ptr device_ptr, NrfReg_CONFIG_ptr Value, NrfReg_STATUS_ptr NrfStatus)
{
	ReadSingleByteRegister(device_ptr, Nrf24Register.CONFIG, BYTE_ADDRESS(Value), NrfStatus);
}
private void WriteConfigRegister(NrfDevice_ptr device_ptr, NrfReg_CONFIG Value, NrfReg_STATUS_ptr NrfStatus)
{
	WriteSingleByteRegister(device_ptr, Nrf24Register.CONFIG, BYTE_VALUE(Value), NrfStatus);
}
private void UpdateConfigRegister(NrfDevice_ptr device_ptr, NrfReg_CONFIG Value, NrfReg_CONFIG Mask, NrfReg_STATUS_ptr NrfStatus)
{
	uint8_t old_value;
	
	ReadSingleByteRegister(device_ptr, Nrf24Register.CONFIG, &old_value, NrfStatus);
	WriteSingleByteRegister(device_ptr, Nrf24Register.CONFIG, TWIDDLE(old_value, Value, Mask), NrfStatus);
}
private void ReadEnAaRegister(NrfDevice_ptr device_ptr, NrfReg_EN_AA_ptr Value, NrfReg_STATUS_ptr NrfStatus)
{
	ReadSingleByteRegister(device_ptr, Nrf24Register.EN_AA, BYTE_ADDRESS(Value), NrfStatus);
}
private void WriteEnAaRegister(NrfDevice_ptr device_ptr, NrfReg_EN_AA Value, NrfReg_STATUS_ptr NrfStatus)
{
	WriteSingleByteRegister(device_ptr, Nrf24Register.EN_AA, BYTE_VALUE(Value), NrfStatus);
}
private void UpdateEnAaRegister(NrfDevice_ptr device_ptr, NrfReg_EN_AA Value, NrfReg_EN_AA Mask, NrfReg_STATUS_ptr NrfStatus)
{
	uint8_t old_value;
	
	ReadSingleByteRegister(device_ptr, Nrf24Register.EN_AA, &old_value, NrfStatus);
	WriteSingleByteRegister(device_ptr, Nrf24Register.EN_AA, TWIDDLE(old_value, Value, Mask), NrfStatus);
}
private void ReadEnRxAddrRegister(NrfDevice_ptr device_ptr, NrfReg_EN_RXADDR_ptr Value, NrfReg_STATUS_ptr NrfStatus)
{
	ReadSingleByteRegister(device_ptr, Nrf24Register.EN_RXADDR, BYTE_ADDRESS(Value), NrfStatus);
}
private void WriteEnRxAddrRegister(NrfDevice_ptr device_ptr, NrfReg_EN_RXADDR Value, NrfReg_STATUS_ptr NrfStatus)
{
	WriteSingleByteRegister(device_ptr, Nrf24Register.EN_RXADDR, BYTE_VALUE(Value), NrfStatus);
}
private void UpdateEnRxAddrRegister(NrfDevice_ptr device_ptr, NrfReg_EN_RXADDR Value, NrfReg_EN_RXADDR Mask, NrfReg_STATUS_ptr NrfStatus)
{
	uint8_t old_value;
	
	ReadSingleByteRegister(device_ptr, Nrf24Register.EN_RXADDR, &old_value, NrfStatus);
	WriteSingleByteRegister(device_ptr, Nrf24Register.EN_RXADDR, TWIDDLE(old_value, Value, Mask), NrfStatus);
}
private void ReadSetupAwRegister(NrfDevice_ptr device_ptr, NrfReg_SETUP_AW_ptr Value, NrfReg_STATUS_ptr NrfStatus)
{
	ReadSingleByteRegister(device_ptr, Nrf24Register.SETUP_AW, BYTE_ADDRESS(Value), NrfStatus);
}
private void WriteSetupAwRegister(NrfDevice_ptr device_ptr, NrfReg_SETUP_AW Value, NrfReg_STATUS_ptr NrfStatus)
{
	WriteSingleByteRegister(device_ptr, Nrf24Register.SETUP_AW, BYTE_VALUE(Value), NrfStatus);
}
private void UpdateSetupAwRegister(NrfDevice_ptr device_ptr, NrfReg_SETUP_AW Value, NrfReg_SETUP_AW Mask, NrfReg_STATUS_ptr NrfStatus)
{
	uint8_t old_value;
	
	ReadSingleByteRegister(device_ptr, Nrf24Register.SETUP_AW, &old_value, NrfStatus);
	WriteSingleByteRegister(device_ptr, Nrf24Register.SETUP_AW, TWIDDLE(old_value, Value, Mask), NrfStatus);
}
private void ReadSetupRetrRegister(NrfDevice_ptr device_ptr, NrfReg_SETUP_RETR_ptr Value, NrfReg_STATUS_ptr NrfStatus)
{
	ReadSingleByteRegister(device_ptr, Nrf24Register.SETUP_RETR, BYTE_ADDRESS(Value), NrfStatus);
}
private void WriteSetupRetrRegister(NrfDevice_ptr device_ptr, NrfReg_SETUP_RETR Value, NrfReg_STATUS_ptr NrfStatus)
{
	WriteSingleByteRegister(device_ptr, Nrf24Register.SETUP_RETR, BYTE_VALUE(Value), NrfStatus);
}
private void UpdateSetupRetrRegister(NrfDevice_ptr device_ptr, NrfReg_SETUP_RETR Value, NrfReg_SETUP_RETR Mask, NrfReg_STATUS_ptr NrfStatus)
{
	uint8_t old_value;
	
	ReadSingleByteRegister(device_ptr, Nrf24Register.SETUP_RETR, &old_value, NrfStatus);
	WriteSingleByteRegister(device_ptr, Nrf24Register.SETUP_RETR, TWIDDLE(old_value, Value, Mask), NrfStatus);
}
private void ReadRfChannelRegister(NrfDevice_ptr device_ptr, NrfReg_RF_CH_ptr Value, NrfReg_STATUS_ptr NrfStatus)
{
	ReadSingleByteRegister(device_ptr, Nrf24Register.RF_CH, BYTE_ADDRESS(Value), NrfStatus);
}
private void WriteRfChannelRegister(NrfDevice_ptr device_ptr, NrfReg_RF_CH Value, NrfReg_STATUS_ptr NrfStatus)
{
	WriteSingleByteRegister(device_ptr, Nrf24Register.RF_CH, BYTE_VALUE(Value), NrfStatus);
}
private void UpdateRfChannelRegister(NrfDevice_ptr device_ptr, NrfReg_RF_CH Value, NrfReg_RF_CH Mask, NrfReg_STATUS_ptr NrfStatus)
{
	uint8_t old_value;
	
	ReadSingleByteRegister(device_ptr, Nrf24Register.RF_CH, &old_value, NrfStatus);
	WriteSingleByteRegister(device_ptr, Nrf24Register.RF_CH, TWIDDLE(old_value, Value, Mask), NrfStatus);
}
private void ReadRfSetupRegister(NrfDevice_ptr device_ptr, NrfReg_RF_SETUP_ptr Value, NrfReg_STATUS_ptr NrfStatus)
{
	ReadSingleByteRegister(device_ptr, Nrf24Register.RF_SETUP, BYTE_ADDRESS(Value), NrfStatus);
}
private void WriteRfSetupRegister(NrfDevice_ptr device_ptr, NrfReg_RF_SETUP Value, NrfReg_STATUS_ptr NrfStatus)
{
	WriteSingleByteRegister(device_ptr, Nrf24Register.RF_SETUP, BYTE_VALUE(Value), NrfStatus);
}
private void UpdateRfSetupRegister(NrfDevice_ptr device_ptr, NrfReg_RF_SETUP Value, NrfReg_RF_SETUP Mask, NrfReg_STATUS_ptr NrfStatus)
{
	uint8_t old_value;
	
	ReadSingleByteRegister(device_ptr, Nrf24Register.RF_SETUP, &old_value, NrfStatus);
	WriteSingleByteRegister(device_ptr, Nrf24Register.RF_SETUP, TWIDDLE(old_value, Value, Mask), NrfStatus);
}
private void ReadStatusRegister(NrfDevice_ptr device_ptr, NrfReg_STATUS_ptr Value)
{
	uint8_t command = NrfCommand.NOP | Nrf24Register.STATUS;
	
	nrf24_hal_support.Select(device_ptr);
	nrf24_hal_support.ExchangeBytes(device_ptr, &command, (uint8_t*)Value, 1);
	nrf24_hal_support.Deselect(device_ptr);

}
private void WriteStatusRegister(NrfDevice_ptr device_ptr, NrfReg_STATUS Value, NrfReg_STATUS_ptr NrfStatus)
{
	WriteSingleByteRegister(device_ptr, Nrf24Register.STATUS, BYTE_VALUE(Value), NrfStatus);
}
private void UpdateStatusRegister(NrfDevice_ptr device_ptr, NrfReg_STATUS Value, NrfReg_STATUS Mask)
{
	NrfReg_STATUS old_value;
	
	ReadStatusRegister(device_ptr, &old_value);
	WriteSingleByteRegister(device_ptr, Nrf24Register.STATUS, TWIDDLE(old_value, Value, Mask), &old_value);
}
private void ReadObserveTxRegister(NrfDevice_ptr device_ptr, NrfReg_OBSERVE_TX_ptr Value, NrfReg_STATUS_ptr NrfStatus)
{
	ReadSingleByteRegister(device_ptr, Nrf24Register.OBSERVE_TX, BYTE_ADDRESS(Value), NrfStatus);
}
private void WriteObserveTxRegister(NrfDevice_ptr device_ptr, NrfReg_OBSERVE_TX Value, NrfReg_STATUS_ptr NrfStatus)
{
	WriteSingleByteRegister(device_ptr, Nrf24Register.OBSERVE_TX, BYTE_VALUE(Value), NrfStatus);
}
private void UpdateObserveTxRegister(NrfDevice_ptr device_ptr, NrfReg_OBSERVE_TX Value, NrfReg_OBSERVE_TX Mask, NrfReg_STATUS_ptr NrfStatus)
{
	uint8_t old_value;
	
	ReadSingleByteRegister(device_ptr, Nrf24Register.OBSERVE_TX, &old_value, NrfStatus);
	WriteSingleByteRegister(device_ptr, Nrf24Register.OBSERVE_TX, TWIDDLE(old_value, Value, Mask), NrfStatus);
}
private void ReadRpdRegister(NrfDevice_ptr device_ptr, NrfReg_RPD_ptr Value, NrfReg_STATUS_ptr NrfStatus)
{
	ReadSingleByteRegister(device_ptr, Nrf24Register.RPD, BYTE_ADDRESS(Value), NrfStatus);
}
private void WriteRpdRegister(NrfDevice_ptr device_ptr, NrfReg_RPD Value, NrfReg_STATUS_ptr NrfStatus)
{
	WriteSingleByteRegister(device_ptr, Nrf24Register.RPD, BYTE_VALUE(Value), NrfStatus);
}
private void UpdateRpdRegister(NrfDevice_ptr device_ptr, NrfReg_RPD Value, NrfReg_RPD Mask, NrfReg_STATUS_ptr NrfStatus)
{
	uint8_t old_value;
	
	ReadSingleByteRegister(device_ptr, Nrf24Register.RPD, &old_value, NrfStatus);
	WriteSingleByteRegister(device_ptr, Nrf24Register.RPD, TWIDDLE(old_value, Value, Mask), NrfStatus);
}
private void ReadLongRxAddrRegister(NrfDevice_ptr device_ptr, NrfReg_RX_ADDR_LONG_ptr Value, uint8_t Pipe, NrfReg_STATUS_ptr NrfStatus)
{
	uint8_t bytes_read;
	ReadMultiBytesRegister(device_ptr, Nrf24Register.RX_ADDR_P0 + Pipe, Value->value, &bytes_read, NrfStatus);
}
private void WriteLongRxAddrRegister(NrfDevice_ptr device_ptr, NrfReg_RX_ADDR_LONG Value, uint8_t Pipe, NrfReg_STATUS_ptr NrfStatus)
{
	uint8_t bytes_written;
	WriteMultiBytesRegister(device_ptr, Nrf24Register.RX_ADDR_P0 + Pipe, Value.value, &bytes_written, NrfStatus);
}
private void ReadShortRxAddrRegister(NrfDevice_ptr device_ptr, NrfReg_RX_ADDR_SHORT_ptr Value, uint8_t Pipe, NrfReg_STATUS_ptr NrfStatus)
{
	ReadSingleByteRegister(device_ptr, Nrf24Register.RX_ADDR_P0 + Pipe, BYTE_ADDRESS(Value), NrfStatus);
}
private void WriteShortRxAddrRegister(NrfDevice_ptr device_ptr, NrfReg_RX_ADDR_SHORT Value, uint8_t Pipe, NrfReg_STATUS_ptr NrfStatus)
{
	WriteSingleByteRegister(device_ptr, Nrf24Register.RX_ADDR_P0 + Pipe, BYTE_VALUE(Value), NrfStatus);
}
private void ReadTxAddrRegister(NrfDevice_ptr device_ptr, NrfReg_TX_ADDR_LONG_ptr Value, NrfReg_STATUS_ptr NrfStatus)
{
	uint8_t bytes_read;
	ReadMultiBytesRegister(device_ptr, Nrf24Register.TX_ADDR, BYTE_ADDRESS(Value), &bytes_read, NrfStatus);
}
private void WriteTxAddrRegister(NrfDevice_ptr device_ptr, NrfReg_TX_ADDR_LONG Value, NrfReg_STATUS_ptr NrfStatus)
{
	uint8_t bytes_written;
	WriteMultiBytesRegister(device_ptr, Nrf24Register.TX_ADDR, Value.value, &bytes_written, NrfStatus);
}
private void ReadRxPwRegister(NrfDevice_ptr device_ptr, NrfReg_RX_PW_ptr Value, uint8_t Pipe, NrfReg_STATUS_ptr NrfStatus)
{
	ReadSingleByteRegister(device_ptr, Nrf24Register.RX_PW_P0 + Pipe, BYTE_ADDRESS(Value), NrfStatus);
}
private void WriteRxPwRegister(NrfDevice_ptr device_ptr, NrfReg_RX_PW Value, uint8_t Pipe,NrfReg_STATUS_ptr NrfStatus)
{
	WriteSingleByteRegister(device_ptr, Nrf24Register.RX_PW_P0 + Pipe, BYTE_VALUE(Value), NrfStatus);
}
private void ReadFifoStatusRegister(NrfDevice_ptr device_ptr, NrfReg_FIFO_STATUS_ptr Value, NrfReg_STATUS_ptr NrfStatus)
{
	ReadSingleByteRegister(device_ptr, Nrf24Register.FIFO_STATUS, BYTE_ADDRESS(Value), NrfStatus);
}
private void WriteFifoStatusRegister(NrfDevice_ptr device_ptr, NrfReg_FIFO_STATUS Value, NrfReg_STATUS_ptr NrfStatus)
{
	WriteSingleByteRegister(device_ptr, Nrf24Register.FIFO_STATUS, BYTE_VALUE(Value), NrfStatus);
}
private void UpdateFifoStatusRegister(NrfDevice_ptr device_ptr, NrfReg_FIFO_STATUS Value, NrfReg_FIFO_STATUS Mask, NrfReg_STATUS_ptr NrfStatus)
{
	uint8_t old_value;
	
	ReadSingleByteRegister(device_ptr, Nrf24Register.FIFO_STATUS, &old_value, NrfStatus);
	WriteSingleByteRegister(device_ptr, Nrf24Register.FIFO_STATUS, TWIDDLE(old_value, Value, Mask), NrfStatus);
}
private void ReadDynpdRegister(NrfDevice_ptr device_ptr, NrfReg_DYNPD_ptr Value, NrfReg_STATUS_ptr NrfStatus)
{
	ReadSingleByteRegister(device_ptr, Nrf24Register.DYNPD, BYTE_ADDRESS(Value), NrfStatus);
}
private void WriteDynpdRegister(NrfDevice_ptr device_ptr, NrfReg_DYNPD Value, NrfReg_STATUS_ptr NrfStatus)
{
	WriteSingleByteRegister(device_ptr, Nrf24Register.DYNPD, BYTE_VALUE(Value), NrfStatus);
}
private void UpdateDynpdRegister(NrfDevice_ptr device_ptr, NrfReg_DYNPD Value, NrfReg_DYNPD Mask, NrfReg_STATUS_ptr NrfStatus)
{
	uint8_t old_value;
	
	ReadSingleByteRegister(device_ptr, Nrf24Register.DYNPD, &old_value, NrfStatus);
	WriteSingleByteRegister(device_ptr, Nrf24Register.DYNPD, TWIDDLE(old_value, Value, Mask), NrfStatus);
}
private void ReadFeatureRegister(NrfDevice_ptr device_ptr, NrfReg_FEATURE_ptr Value, NrfReg_STATUS_ptr NrfStatus)
{
	ReadSingleByteRegister(device_ptr, Nrf24Register.FEATURE, BYTE_ADDRESS(Value), NrfStatus);
}
private void WriteFeatureRegister(NrfDevice_ptr device_ptr, NrfReg_FEATURE Value, NrfReg_STATUS_ptr NrfStatus)
{
	WriteSingleByteRegister(device_ptr, Nrf24Register.FEATURE, BYTE_VALUE(Value), NrfStatus);
}
private void UpdateFeatureRegister(NrfDevice_ptr device_ptr, NrfReg_FEATURE Value, NrfReg_FEATURE Mask, NrfReg_STATUS_ptr NrfStatus)
{
	uint8_t old_value;
	
	ReadSingleByteRegister(device_ptr, Nrf24Register.FEATURE, &old_value, NrfStatus);
	WriteSingleByteRegister(device_ptr, Nrf24Register.FEATURE, TWIDDLE(old_value, Value, Mask), NrfStatus);
}
private void ReadSingleByteRegister(NrfDevice * device_ptr, uint8_t Register, uint8_t * Value, NrfReg_STATUS_ptr NrfStatus)
{
	uint8_t command = NrfCommand.R_REGISTER | Register;
	
	nrf24_hal_support.Select(device_ptr);
	nrf24_hal_support.WriteBytes(device_ptr, &command, 1);
	nrf24_hal_support.ReadBytes(device_ptr, Value, 1);
	nrf24_hal_support.Deselect(device_ptr);
}
private void WriteSingleByteRegister(NrfDevice_ptr device_ptr, uint8_t Register, uint8_t Value, NrfReg_STATUS_ptr NrfStatus)
{
	uint8_t command[2] = { NrfCommand.W_REGISTER | Register, Value };
	
	nrf24_hal_support.Select(device_ptr);
	nrf24_hal_support.WriteBytes(device_ptr, command, 2);
	nrf24_hal_support.Deselect(device_ptr);
}
private void ReadMultiBytesRegister(NrfDevice_ptr device_ptr, uint8_t Register, uint8_t Value[], uint8_t * BytesRead, NrfReg_STATUS_ptr NrfStatus)
{
	uint8_t command = NrfCommand.R_REGISTER | Register;
	uint8_t width;
	uint8_t bytes;
	NrfReg_SETUP_AW aw;
	
	*BytesRead = 0;
	*NrfStatus = (NrfReg_STATUS){ 0 };
	
	ReadSetupAwRegister(device_ptr, &aw, NrfStatus);

	ReadSingleByteRegister(device_ptr, Nrf24Register.SETUP_AW, &width, NrfStatus);
	
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
	
	nrf24_hal_support.Select(device_ptr);
	nrf24_hal_support.ExchangeBytes(device_ptr, &command, (uint8_t*)NrfStatus,1);
	nrf24_hal_support.ReadBytes(device_ptr, Value, bytes);
	nrf24_hal_support.Deselect(device_ptr);
}
private void WriteMultiBytesRegister(NrfDevice_ptr device_ptr, uint8_t Register, uint8_t Value[], uint8_t * BytesWritten, NrfReg_STATUS_ptr NrfStatus)
{
	uint8_t command = NrfCommand.W_REGISTER | Register;
	uint8_t width;
	uint8_t bytes;
	
	*NrfStatus = (NrfReg_STATUS){ 0 };

	ReadSingleByteRegister(device_ptr, Nrf24Register.SETUP_AW, &width, NrfStatus);
	
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
	
	nrf24_hal_support.Select(device_ptr);
	nrf24_hal_support.ExchangeBytes(device_ptr, &command, (uint8_t*)NrfStatus, 1);
	nrf24_hal_support.WriteBytes(device_ptr, Value, bytes);
	nrf24_hal_support.Deselect(device_ptr);
}

// Set all regsiters to the same values they get set to, when the device is powered off/on
// This function does not actually cycle the power, only simulate it in the sense that
// the device registers are in the same state as if it had been power cycled.
private void ResetDevice(NrfDevice_ptr device_ptr)
{
	NrfReg_STATUS status;
	NrfReg_STATUS status_mask = { 0 };
	NrfReg_CONFIG config = { 0 };
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
	NrfReg_FIFO_STATUS fifo_status = { 0 };
	NrfReg_DYNPD dynpd = { 0 };
	NrfReg_FEATURE feature = { 0 };
	
	// Set CONFIG reg defaults
	config.EN_CRC = 1;
	
	// Set EN_AA reg defaults
	en_aa.ENAA_P5 = 1;
	en_aa.ENAA_P4 = 1;
	en_aa.ENAA_P3 = 1;
	en_aa.ENAA_P2 = 1;
	en_aa.ENAA_P1 = 1;
	en_aa.ENAA_P0 = 1;
	
	// Set EN_RXADDR reg defaults

	en_rxaddr.ERX_P0 = 1;
	en_rxaddr.ERX_P1 = 1;
	
	// Set SETUP_AW reg defaults
	setup_aw.AW = 3;
	
	// Set SETUP_RETR reg defaults
	setup_retr.ARD = 0x00;
	setup_retr.ARC = 0x03;
	
	// Set RF_CH reg defaults
	rf_ch.RF_CH = 2;
	
	// Set RF_SETUP reg defaults
	rf_setup.RF_DR_HIGH = 1;
	rf_setup.RF_PWR = 3;
	
	// Set STATUS defaults
	
	status.RX_DR = 0;
	status.TX_DS = 0;
	status.MAX_RT = 0;
	
	// Registers OBSERVE_TX and RPD are read only on every bit.
	
	// Set RX_ADDR_P0 - RX_ADDR_P1 reg defaults
	rx_addr_long_p0.value[0] = E7;
	rx_addr_long_p0.value[1] = E7;
	rx_addr_long_p0.value[2] = E7;
	rx_addr_long_p0.value[3] = E7;
	rx_addr_long_p0.value[4] = E7;
	
	rx_addr_long_p1.value[0] = C2;
	rx_addr_long_p1.value[1] = C2;
	rx_addr_long_p1.value[2] = C2;
	rx_addr_long_p1.value[3] = C2;
	rx_addr_long_p1.value[4] = C2;

	// Set RX_ADDR_P2 - RX_ADDR_P5 reg defaults
	rx_addr_short_p2.value = C3;
	rx_addr_short_p3.value = C4;
	rx_addr_short_p4.value = C5;
	rx_addr_short_p5.value = C6;
	
	// Set TX_ADDR reg defaults
	tx_addr_long.value[0] = E7;
	tx_addr_long.value[1] = E7;
	tx_addr_long.value[2] = E7;
	tx_addr_long.value[3] = E7;
	tx_addr_long.value[4] = E7;
	
	// FIFO_STATUS has no user settable bits
	
	nrf24_package.Action.PowerDown(device_ptr);
	nrf24_package.Write.CONFIG(device_ptr, config, &status);
	nrf24_package.Write.EN_AA(device_ptr, en_aa, &status);
	nrf24_package.Write.EN_RXADDR(device_ptr, en_rxaddr, &status);
	nrf24_package.Write.SETUP_AW(device_ptr, setup_aw, &status);
	nrf24_package.Write.SETUP_RETR(device_ptr, setup_retr, &status);
	nrf24_package.Write.RF_CH(device_ptr, rf_ch, &status);
	nrf24_package.Write.RF_SETUP(device_ptr, rf_setup, &status);
	nrf24_package.Write.STATUS(device_ptr, status, &status);

	nrf24_package.Write.RX_ADDR_LONG(device_ptr, rx_addr_long_p0, 0, &status);
	nrf24_package.Write.RX_ADDR_LONG(device_ptr, rx_addr_long_p1, 1, &status);
	nrf24_package.Write.RX_ADDR_SHORT(device_ptr, rx_addr_short_p2, 2, &status);
	nrf24_package.Write.RX_ADDR_SHORT(device_ptr, rx_addr_short_p3, 3, &status);
	nrf24_package.Write.RX_ADDR_SHORT(device_ptr, rx_addr_short_p4, 4, &status);
	nrf24_package.Write.RX_ADDR_SHORT(device_ptr, rx_addr_short_p5, 5, &status);
	
	nrf24_package.Write.TX_ADDR_LONG(device_ptr, tx_addr_long, &status);
	
	nrf24_package.Write.RX_PW(device_ptr, rx_pw, 0, &status);
	nrf24_package.Write.RX_PW(device_ptr, rx_pw, 1, &status);
	nrf24_package.Write.RX_PW(device_ptr, rx_pw, 2, &status);
	nrf24_package.Write.RX_PW(device_ptr, rx_pw, 3, &status);
	nrf24_package.Write.RX_PW(device_ptr, rx_pw, 4, &status);
	nrf24_package.Write.RX_PW(device_ptr, rx_pw, 5, &status);
	
	nrf24_package.Command.FLUSH_TX(device_ptr, &status);
	nrf24_package.Command.FLUSH_RX(device_ptr, &status);
	nrf24_package.Write.DYNPD(device_ptr, dynpd, &status);
	nrf24_package.Write.FEATURE(device_ptr, feature, &status);
	
}
private void ReadAllRegisters(NrfDevice_ptr device_ptr, NrfReg_ALL_REGISTERS_ptr Value, NrfReg_STATUS_ptr NrfStatus)
{
	ReadConfigRegister(device_ptr, &(Value->CONFIG), NrfStatus);
	ReadEnAaRegister(device_ptr, &(Value->EN_AA), NrfStatus);
	ReadEnRxAddrRegister(device_ptr, &(Value->EN_RXADDR), NrfStatus);
	ReadSetupAwRegister(device_ptr, &(Value->SETUP_AW), NrfStatus);
	ReadSetupRetrRegister(device_ptr, &(Value->SETUP_RETR), NrfStatus);
	ReadRfChannelRegister(device_ptr, &(Value->RF_CH), NrfStatus);
	ReadRfSetupRegister(device_ptr, &(Value->RF_SETUP), NrfStatus);
	ReadStatusRegister(device_ptr, &(Value->STATUS));
	ReadObserveTxRegister(device_ptr, &(Value->OBSERVE_TX), NrfStatus);
	ReadRpdRegister(device_ptr, &(Value->RPD), NrfStatus);
	ReadLongRxAddrRegister(device_ptr, &(Value->RX_ADDR_P0), 0, NrfStatus);
	ReadLongRxAddrRegister(device_ptr, &(Value->RX_ADDR_P1), 1, NrfStatus);
	ReadShortRxAddrRegister(device_ptr, &(Value->RX_ADDR_P2), 2, NrfStatus);
	ReadShortRxAddrRegister(device_ptr, &(Value->RX_ADDR_P3), 3, NrfStatus);
	ReadShortRxAddrRegister(device_ptr, &(Value->RX_ADDR_P4), 4, NrfStatus);
	ReadShortRxAddrRegister(device_ptr, &(Value->RX_ADDR_P5), 5, NrfStatus);
	ReadTxAddrRegister(device_ptr, &(Value->TX_ADDR), NrfStatus);
	ReadRxPwRegister(device_ptr, &(Value->RX_PW_P0), 0, NrfStatus);
	ReadRxPwRegister(device_ptr, &(Value->RX_PW_P1), 1, NrfStatus);
	ReadRxPwRegister(device_ptr, &(Value->RX_PW_P2), 2, NrfStatus);
	ReadRxPwRegister(device_ptr, &(Value->RX_PW_P3), 3, NrfStatus);
	ReadRxPwRegister(device_ptr, &(Value->RX_PW_P4), 4, NrfStatus);
	ReadRxPwRegister(device_ptr, &(Value->RX_PW_P5), 5, NrfStatus);
	ReadFifoStatusRegister(device_ptr, &(Value->FIFO_STATUS), NrfStatus);
	ReadDynpdRegister(device_ptr, &(Value->DYNPD), NrfStatus);
	ReadFeatureRegister(device_ptr, &(Value->FEATURE), NrfStatus);
}

private void SetAddressWidth(NrfDevice_ptr device_ptr, uint8_t width)
{
	NrfReg_STATUS status = { 0 };
	NrfReg_SETUP_AW setup_aw = { 0 };
	
	setup_aw.AW = width;
	
	nrf24_package.Write.SETUP_AW(device_ptr, setup_aw, &status);
}

private void SetAutoAckRetries(NrfDevice_ptr device_ptr, uint8_t delay, uint8_t max)
{
	NrfReg_STATUS status = { 0 };
	NrfReg_SETUP_RETR setup_retr = { 0 };
	
	setup_retr.ARD = delay;
	setup_retr.ARC = max;
	nrf24_package.Write.SETUP_RETR(device_ptr, setup_retr, &status);
}
private void SetCRC(NrfDevice_ptr device_ptr, bool enable, bool size)
{
	NrfReg_STATUS status = { 0 };
	NrfReg_CONFIG config = { 0 };
	NrfReg_CONFIG mask = { 0 };
	
	config.CRCO = size;
	config.EN_CRC = enable;
	
	mask.CRCO = 1;
	mask.EN_CRC = 1;
	
	nrf24_package.Update.CONFIG(device_ptr, config, mask, &status); // Zeroize the config register

}
private void PowerDown(NrfDevice_ptr device_ptr)
{
	NrfReg_CONFIG config = { 0 };
	NrfReg_STATUS status;
	
	nrf24_hal_support.Deactivate(device_ptr);

	nrf24_package.Read.CONFIG(device_ptr, &config, &status);
	
	config.PWR_UP = 0;
	
	nrf24_package.Write.CONFIG(device_ptr, config, &status);
}
private void ClearInterruptFlags(NrfDevice_ptr device_ptr, bool RX_DR, bool TX_DS, bool MAX_RT)
{
	NrfReg_STATUS status = { 0 };
	
	// These are write 1 to clear so the register value also serves as its own mask here.
	
	status.RX_DR = RX_DR;
	status.TX_DS = TX_DS;
	status.MAX_RT = MAX_RT;
	
	nrf24_package.Update.STATUS(device_ptr, status, status);
	
}
private void SetReceiveMode(NrfDevice_ptr device_ptr)
{
	NrfReg_CONFIG config = { 0 };
	NrfReg_CONFIG mask = { 0 };
	NrfReg_STATUS status;
	
	mask.PRIM_RX = 1; 
	config.PRIM_RX = 1;
	
	nrf24_package.Update.CONFIG(device_ptr, config, mask, &status);
	nrf24_hal_support.Activate(device_ptr);
}
private void SetTransmitMode(NrfDevice_ptr device_ptr)
{
	NrfReg_CONFIG config = { 0 };
	NrfReg_CONFIG mask = { 0 };
	NrfReg_STATUS status;
	
	mask.PRIM_RX = 1; 
	config.PRIM_RX = 0;
	
	nrf24_package.Update.CONFIG(device_ptr, config, mask, &status);
}
private void ConfigureTransmitter(NrfDevice_ptr device_ptr, bool auto_ack)
{
	NrfReg_STATUS status;
	NrfReg_CONFIG config = { 0 };
	NrfReg_CONFIG bits_to_change = { 0 };
	NrfReg_TX_ADDR_LONG tx_addr = { 0 };
	NrfReg_RF_SETUP rf_setup = { 0 };
	NrfReg_EN_AA enaa = { 0 }, enaa_mask = { 0 };
	NrfReg_SETUP_RETR retr = { 0 };
	NrfReg_EN_RXADDR rxaddr = { 0 };
	
	if (auto_ack) // SEE: https://devzone.nordicsemi.com/f/nordic-q-a/7177/nrf24l01-not-receiving-ack
	{
		rxaddr.ERX_P0 = 1;
		nrf24_package.Write.EN_RXADDR(device_ptr, rxaddr, &status);
	}

	// Clear interrupts
	
	status.RX_DR = 1;
	status.TX_DS = 1;
	status.MAX_RT = 1;
	
	// Since the mask would be the same as the status itself, we can just pass 
	// it in for both args.
	
	nrf24_package.Update.STATUS(device_ptr, status, status);
	
	// Set rate
	
	
	// Set mode to TX

	bits_to_change.PRIM_RX = 1; 
	
	config.PRIM_RX = 0;
	
	
	nrf24_package.Update.CONFIG(device_ptr, config, bits_to_change, &status);
	

}
private void PowerUpDevice(NrfDevice_ptr device_ptr)
{
	NrfReg_STATUS status;
	NrfReg_CONFIG config = { 0 };
	NrfReg_CONFIG bits_to_change = { 0 };

	bits_to_change.PWR_UP = 1;
	config.PWR_UP = 1;
	
	nrf24_package.Update.CONFIG(device_ptr, config, bits_to_change, &status);
	
	HAL_Delay(2); // 1.5 mS min delay after powerup.
	
}
private void ConfigureRadio(NrfDevice_ptr device_ptr, uint8_t channel, uint8_t power, uint8_t rate, bool auto_ack)
{
	NrfReg_STATUS status;
	NrfReg_RF_CH rf_ch = { 0 };
	NrfReg_RF_SETUP rf_setup = { 0 }, rf_setup_mask = { 0 };
	
	rf_setup_mask.RF_DR_HIGH = 1;
	rf_setup_mask.RF_DR_LOW = 1;
	rf_setup_mask.RF_PWR = 3;
	
	rf_ch.RF_CH = channel; 

	switch (rate)
	{
	case MIN_RATE:
		rf_setup.RF_DR_LOW = 1; 
		rf_setup.RF_DR_HIGH = 0;
		break;
	case MAX_RATE: 
		rf_setup.RF_DR_LOW = 0; 
		rf_setup.RF_DR_HIGH = 1;
		break;
	case MED_RATE:
		rf_setup.RF_DR_LOW = 0; 
		rf_setup.RF_DR_HIGH = 0;
		break;
	}
	
	rf_setup.RF_PWR = power;
	
	nrf24_package.Write.RF_CH(device_ptr, rf_ch, &status);
	nrf24_package.Update.RF_SETUP(device_ptr, rf_setup, rf_setup_mask, &status); // Set RF settings

}
private void MaskInterrupts(NrfDevice_ptr device_ptr, bool RX_DR, bool TX_DS, bool MAX_RT)
{
	NrfReg_STATUS status;
	NrfReg_CONFIG config = { 0 };
	NrfReg_CONFIG bits_to_change = { 0 };
	
	bits_to_change.MASK_MAX_RT = 1;
	bits_to_change.MASK_TX_DS = 1;
	bits_to_change.MASK_RX_DR = 1;
	
	config.MASK_MAX_RT = MAX_RT;
	config.MASK_TX_DS = TX_DS;
	config.MASK_RX_DR = RX_DR;
	
	nrf24_package.Update.CONFIG(device_ptr, config, bits_to_change, &status);
	
}
private void SetReceivePayloadSize(NrfDevice_ptr device_ptr, uint8_t payload_size, uint8_t pipe)
{
	NrfReg_RX_PW rx_pw = { 0 };
	NrfReg_STATUS status;

	rx_pw.RX_PW_LEN = payload_size;
	nrf24_package.Write.RX_PW(device_ptr, rx_pw, pipe, &status);
	
}
private void ConfigureReceiver(NrfDevice_ptr device_ptr, uint8_t address[5], uint8_t pipe, bool auto_ack, uint8_t payload_size)
{
	NrfReg_STATUS status;
	NrfReg_RX_ADDR_LONG rx_addr = { 0 };
	NrfReg_CONFIG bits_to_change = { 0 };
	NrfReg_CONFIG config = { 0 };
	NrfReg_EN_RXADDR en_rx_addr = { 0 };
	NrfReg_RX_PW rx_pw = { 0 };
	NrfReg_EN_AA enaa = { 0 }, enaa_mask = { 0 };
	NrfReg_ALL_REGISTERS bef = { 0 }, aft = { 0 };
	
	rx_addr.value[0] = address[0];
	rx_addr.value[1] = address[1];
	rx_addr.value[2] = address[2];
	rx_addr.value[3] = address[3];
	rx_addr.value[4] = address[4];

	nrf24_package.Write.RX_ADDR_LONG(device_ptr, rx_addr, pipe, &status);
	
	// Clear interrupts
	
	status.RX_DR = 1;
	status.TX_DS = 1;
	status.MAX_RT = 1;
	
	// Since the mask would be the same as the status itself, we can just pass 
	// it in for both args.
	
	nrf24_package.Update.STATUS(device_ptr, status, status);
	
	// enable the pipe;
	
	switch(pipe)
		{
		case 0:
			en_rx_addr.ERX_P0 = 1;
			break;
		case 1: 
			en_rx_addr.ERX_P1 = 1;
			break;
		case 2: 
			en_rx_addr.ERX_P2 = 1;
			break;
		case 3: 
			en_rx_addr.ERX_P3 = 1;
			break;
		case 4: 
			en_rx_addr.ERX_P3 = 1;
			break;
		case 5: 
			en_rx_addr.ERX_P3 = 1;
			break;
		}
	
	nrf24_package.Write.EN_RXADDR(device_ptr, en_rx_addr, &status);
	
	rx_pw.RX_PW_LEN = payload_size; // Set the RX payload width to 32 bytes.
	
	nrf24_package.Write.RX_PW(device_ptr, rx_pw, pipe, &status);
	
	// Set mode to RX

	bits_to_change.PRIM_RX = 1; 
	bits_to_change.MASK_MAX_RT = 1;
	bits_to_change.MASK_TX_DS = 1;
	bits_to_change.MASK_RX_DR = 1;
	
	// Enable on the RX interrupt.
	
	config.PRIM_RX = 1;
	config.MASK_MAX_RT = 1;
	config.MASK_TX_DS = 1;
	config.MASK_RX_DR = 0;
	
	if (auto_ack)
	{
		bits_to_change.EN_CRC = 1;
		bits_to_change.CRCO = 1;
		
		config.CRCO = 1;
		config.EN_CRC = 1;
	}
	
	nrf24_package.Update.CONFIG(device_ptr, config, bits_to_change, &status);
	
	// Set rate
	
	
//	enaa_mask.ENAA_P0 = 1;
//	enaa_mask.ENAA_P1 = 0;
//	enaa_mask.ENAA_P2 = 0;
//	enaa_mask.ENAA_P3 = 0;
//	enaa_mask.ENAA_P4 = 0;
//	enaa_mask.ENAA_P5 = 0;
//	
//	if (auto_ack)
//	{
//		
//		enaa.ENAA_P0 = 1;
//		enaa.ENAA_P1 = 1;
//		enaa.ENAA_P2 = 1;
//		enaa.ENAA_P3 = 1;
//		enaa.ENAA_P4 = 1;
//		enaa.ENAA_P5 = 1;
//		
//		nrf24_package.Read.ALL_REGISTERS(device_ptr, &bef, &status);
//		nrf24_package.Update.EN_AA(device_ptr, enaa, enaa_mask, &status); // we canjust use enaa as the mask here.
//		nrf24_package.Read.ALL_REGISTERS(device_ptr, &bef, &status);
//	}
//	else
//	{
//		enaa.ENAA_P0 = 0;
//		enaa.ENAA_P1 = 0;
//		enaa.ENAA_P2 = 0;
//		enaa.ENAA_P3 = 0;
//		enaa.ENAA_P4 = 0;
//		enaa.ENAA_P5 = 0;
//		
//		nrf24_package.Update.EN_AA(device_ptr, enaa, enaa_mask, &status);
//	}
	
	nrf24_hal_support.Activate(device_ptr);

	
}
private void FLUSH_TX(NrfDevice_ptr device_ptr, NrfReg_STATUS_ptr NrfStatus)
{
	uint8_t command = NrfCommand.FLUSH_TX;
	
	nrf24_hal_support.Select(device_ptr);
	nrf24_hal_support.ExchangeBytes(device_ptr, &command, (uint8_t*)NrfStatus, 1);
	nrf24_hal_support.Deselect(device_ptr);
}
private void FLUSH_RX(NrfDevice_ptr device_ptr, NrfReg_STATUS_ptr NrfStatus)
{
	uint8_t command = NrfCommand.FLUSH_RX;

	nrf24_hal_support.Select(device_ptr);
	nrf24_hal_support.ExchangeBytes(device_ptr, &command, (uint8_t*)NrfStatus, 1);
	nrf24_hal_support.Deselect(device_ptr);
}
private void W_TX_PAYLOAD(NrfDevice_ptr device_ptr, uint8_t * data_ptr, uint8_t data_len, NrfReg_STATUS_ptr NrfStatus)
{
	uint8_t buffer[33];
	
	buffer[0] = NrfCommand.W_TX_PAYLOAD;
	
	for (int X = 0; X < 32; X++)
	{
		if (X < data_len)
			buffer[X + 1] = data_ptr[X];
	}

	nrf24_hal_support.Select(device_ptr);
	nrf24_hal_support.WriteBytes(device_ptr, buffer, data_len + 1);
	nrf24_hal_support.Deselect(device_ptr);
}
private void R_RX_PAYLOAD(NrfDevice_ptr device_ptr, uint8_t * data_ptr, uint8_t data_len, NrfReg_STATUS_ptr NrfStatus)
{

	nrf24_hal_support.Select(device_ptr);
	nrf24_hal_support.WriteBytes(device_ptr, &(NrfCommand.R_RX_PAYLOAD), 1);
	nrf24_hal_support.ReadBytes(device_ptr, data_ptr, data_len);
	nrf24_hal_support.Deselect(device_ptr);
	
}
private void wait_for_interrupt(volatile NrfInterrupt_ptr state_ptr, int32_t max_spins)
{
	state_ptr->spins = 0;
	
	while (state_ptr->complete == 0)
	{
		state_ptr->spins++;
		
		if (state_ptr->spins >= 0)
			if (state_ptr->spins >= max_spins)
				ApplicationFaultHandler(LIBNAME, "missing interrupt");
	}
	
	if (state_ptr->spins > state_ptr->max_so_far)
		state_ptr->max_so_far = state_ptr->spins;
	
	state_ptr->count++;
	state_ptr->complete = 0;
}
private void confirm_interrupt(volatile NrfInterrupt_ptr state_ptr)
{
	state_ptr->complete = 1;
}