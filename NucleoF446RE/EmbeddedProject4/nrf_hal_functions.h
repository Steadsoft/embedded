#include <nrf_hal_typedefs.h>
void spi_ce_lo(NrfIoDescriptor_ptr);
void spi_ce_hi(NrfIoDescriptor_ptr);
void spi_cs_lo(NrfIoDescriptor_ptr);
void spi_cs_hi(NrfIoDescriptor_ptr);
void exchange_bytes(NrfIoDescriptor_ptr, uint8_t[], uint8_t[], uint8_t);
void read_bytes(NrfIoDescriptor_ptr, uint8_t bytes_in_ptr[], uint8_t count);
void write_bytes(NrfIoDescriptor_ptr, uint8_t bytes_out_ptr[], uint8_t count);

