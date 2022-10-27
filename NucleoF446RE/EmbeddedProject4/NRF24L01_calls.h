
void ReadSingleByteRegister(NrfSpi * SPI, uint8_t Register, void * Value, NrfSTATUS * NrfStatus);
void WriteSingleByteRegister(NrfSpi * SPI, uint8_t Register, void * Value, NrfSTATUS * NrfStatus);

void ReadMultiBytesRegister(NrfSpi * SPI, uint8_t Register, uint8_t Value[], uint8_t * BytesRead, NrfSTATUS * NrfStatus);
void WriteMultiBytesRegister(NrfSpi * SPI, uint8_t Register, uint8_t Value[], uint8_t * BytesWritten, NrfSTATUS * NrfStatus);

