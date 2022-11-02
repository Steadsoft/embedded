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
	.Read =
	{     
		.ConfigRegister = _ReadConfigRegister,
		.EnAaRegister = _ReadEnAaRegister,
		.EnRxAddrRegister = _ReadEnRxAddrRegister,
		.SetupAwRegister = _ReadSetupAwRegister,
		.SetupRetrRegister = _ReadSetupRetrRegister,
		.RfChannelRegister = _ReadRfChannelRegister,
		.RfSetupRegister = _ReadRfSetupRegister,
		.StatusRegister = _ReadStatusRegister,
		.ObserveTxRegister = _ReadObserveTxRegister,
		.CdRegister = _ReadCdRegister,
		.RxAddrRegister = _ReadRxAddrRegister,
		.RxPwRegister = _ReadRxPwRegister,
		.DynpdRegister = _ReadDynpdRegister,
		.FeatureRegister = _ReadFeatureRegister,
		.SingleByteRegister = _ReadSingleByteRegister,
		.MultiBytesRegister = _ReadMultiBytesRegister,

	},
	.Write = 
	{ 
		.ConfigRegister = _WriteConfigRegister,
		.EnAaRegister = _WriteEnAaRegister,
		.EnRxAddrRegister = _WriteEnRxAddrRegister,
		.SetupAwRegister = _WriteSetupAwRegister,
		.SetupRetrRegister = _WriteSetupRetrRegister,
		.RfChannelRegister = _WriteRfChannelRegister,
		.RfSetupRegister = _WriteRfSetupRegister,
		.StatusRegister = _WriteStatusRegister,
		.ObserveTxRegister = _WriteObserveTxRegister,
		.CdRegister = _WriteCdRegister,
		.RxAddrRegister = _WriteRxAddrRegister,
		.RxPwRegister = _WriteRxPwRegister,
		.DynpdRegister = _WriteDynpdRegister,
		.FeatureRegister = _WriteFeatureRegister,
		.SingleByteRegister = _WriteSingleByteRegister,
		.MultiBytesRegister = _WriteMultiBytesRegister,
	}
};
