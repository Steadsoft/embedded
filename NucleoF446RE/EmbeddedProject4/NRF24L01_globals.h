/* This file is for consumption only by library code. */
/* Global singletons exposed by the NRF library.      */

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

NrfLibraryCalls NrfLibrary =
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
		.SingleByteRegister = _ReadSingleByteRegister,
		.MultiBytesRegister = _ReadMultiBytesRegister,

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
		.SingleByteRegister = _WriteSingleByteRegister,
		.MultiBytesRegister = _WriteMultiBytesRegister,
	}
};
