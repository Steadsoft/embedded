static void spi_cs_lo(NrfSpiDevice *);
static void spi_cs_hi(NrfSpiDevice *);
static void _InitializeDevice(SPI_HandleTypeDef * SpiPtr, GPIO_TypeDef * GpioPtr, uint8_t CsPin, uint8_t CePin, NrfSpiDevice * Device);
static void _ReadSingleByteRegister(NrfSpiDevice * SPI, uint8_t Register, void * Value, NrfReg_STATUS_ptr NrfStatus);
static void _WriteSingleByteRegister(NrfSpiDevice * SPI, uint8_t Register, void * Value, NrfReg_STATUS_ptr NrfStatus);
static void _ReadMultiBytesRegister(NrfSpiDevice * SPI, uint8_t Register, uint8_t Value[], uint8_t * BytesRead, NrfReg_STATUS_ptr NrfStatus);
static void _WriteMultiBytesRegister(NrfSpiDevice * SPI, uint8_t Register, uint8_t Value[], uint8_t * BytesWritten, NrfReg_STATUS_ptr NrfStatus);
