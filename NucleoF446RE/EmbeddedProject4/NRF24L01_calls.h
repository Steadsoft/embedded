
void ReadSingleByteRegister(NrfSpi * SPI, uint8_t Register, void * Value, STATUS * NrfStatus);
void WriteSingleByteRegister(NrfSpi * SPI, uint8_t Register, void * Value, STATUS * NrfStatus);

void ReadMultiBytesRegister(NrfSpi * SPI, uint8_t Register, uint8_t Value[], uint8_t * BytesRead, STATUS * NrfStatus);
void WriteMultiBytesRegister(NrfSpi * SPI, uint8_t Register, uint8_t Value[], uint8_t * BytesWritten, STATUS * NrfStatus);

