#include <nrf_hal_typedefs.h>
void spi_ce_lo(void *);
void spi_ce_hi(void *);
void spi_cs_lo(void *);
void spi_cs_hi(void *);
void exchange_bytes(void *, uint8_t[], uint8_t[], uint8_t);
void read_bytes(void *, uint8_t bytes_in_ptr[], uint8_t count);
void write_bytes(void *, uint8_t bytes_out_ptr[], uint8_t count);

