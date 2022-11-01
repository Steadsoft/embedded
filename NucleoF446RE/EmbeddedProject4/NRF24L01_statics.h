static void _ReadRfSetupRegister(NrfSpiDevice_ptr device_ptr, NrfReg_RF_SETUP_ptr Value, NrfReg_STATUS_ptr NrfStatus);
static void _WriteRfSetupRegister(NrfSpiDevice_ptr device_ptr, NrfReg_RF_SETUP Value, NrfReg_STATUS_ptr NrfStatus);

static void _ReadEnRxAddrRegister(NrfSpiDevice_ptr device_ptr, NrfReg_EN_RXADDR_ptr Value, NrfReg_STATUS_ptr NrfStatus);
static void _WriteEnRxAddrRegister(NrfSpiDevice_ptr device_ptr, NrfReg_EN_RXADDR Value, NrfReg_STATUS_ptr NrfStatus);
static void _ReadConfigRegister(NrfSpiDevice_ptr device_ptr, NrfReg_CONFIG_ptr Value, NrfReg_STATUS_ptr NrfStatus);
static void _WriteConfigRegister(NrfSpiDevice_ptr device_ptr, NrfReg_CONFIG Value, NrfReg_STATUS_ptr NrfStatus);
static void _ReadRFChannelRegister(NrfSpiDevice_ptr device_ptr,  NrfReg_RF_CH_ptr Value, NrfReg_STATUS_ptr NrfStatus);
static void _WriteRFChannelRegister(NrfSpiDevice_ptr device_ptr, NrfReg_RF_CH Value, NrfReg_STATUS_ptr NrfStatus);
static void _ReadSingleByteRegister(NrfSpiDevice * SPI, uint8_t Register, uint8_t * Value, NrfReg_STATUS_ptr NrfStatus);
static void _WriteSingleByteRegister(NrfSpiDevice * SPI, uint8_t Register, uint8_t Value, NrfReg_STATUS_ptr NrfStatus);
static void _ReadMultiBytesRegister(NrfSpiDevice * SPI, uint8_t Register, uint8_t Value[], uint8_t * BytesRead, NrfReg_STATUS_ptr NrfStatus);
static void _WriteMultiBytesRegister(NrfSpiDevice * SPI, uint8_t Register, uint8_t Value[], uint8_t * BytesWritten, NrfReg_STATUS_ptr NrfStatus);
