void _InitializeDevice(SPI_HandleTypeDef * SpiPtr, GPIO_TypeDef * GpioPtr, uint8_t CsPin, uint8_t CePin, NrfSpiDevice * Device);

void _ReadSingleByteRegister(NrfSpiDevice * SPI, uint8_t Register, void * Value, STATUS * NrfStatus);
void _WriteSingleByteRegister(NrfSpiDevice * SPI, uint8_t Register, void * Value, STATUS * NrfStatus);

void _ReadMultiBytesRegister(NrfSpiDevice * SPI, uint8_t Register, uint8_t Value[], uint8_t * BytesRead, STATUS * NrfStatus);
void _WriteMultiBytesRegister(NrfSpiDevice * SPI, uint8_t Register, uint8_t Value[], uint8_t * BytesWritten, STATUS * NrfStatus);

typedef struct
{
	void(* InitializeDevice)(SPI_HandleTypeDef * SpiPtr, GPIO_TypeDef * GpioPtr, uint8_t CsPin, uint8_t CePin, NrfSpiDevice * Device);
	void(* ReadSingleByteRegister)(NrfSpiDevice * SPI, uint8_t Register, void * Value, STATUS * NrfStatus);
	void(* WriteSingleByteRegister)(NrfSpiDevice * SPI, uint8_t Register, void * Value, STATUS * NrfStatus);
	void(* ReadMultiBytesRegister)(NrfSpiDevice * SPI, uint8_t Register, uint8_t Value[], uint8_t * BytesRead, STATUS * NrfStatus);
	void(* WriteMultiBytesRegister)(NrfSpiDevice * SPI, uint8_t Register, uint8_t Value[], uint8_t * BytesWritten, STATUS * NrfStatus);
} nrf24L01_library;

static nrf24L01_library NrfLibrary =
{ 
	.InitializeDevice = _InitializeDevice,
	.ReadSingleByteRegister = _ReadSingleByteRegister,
	.WriteSingleByteRegister = _WriteSingleByteRegister,
	.ReadMultiBytesRegister = _ReadMultiBytesRegister,
	.WriteMultiBytesRegister = _WriteMultiBytesRegister
};
