static void spi_ce_lo(void *);
static void spi_ce_hi(void *);
static void spi_cs_lo(void *);
static void spi_cs_hi(void *);
static void exchange_bytes(void *, uint8_t[], uint8_t[], uint8_t);
static void read_bytes(void *, uint8_t bytes_in_ptr[], uint8_t count);
static void write_bytes(void *, uint8_t bytes_out_ptr[], uint8_t count);
static void init_spi(SPI_HandleTypeDef * spi_ptr);
static void init_control_pins();
static void init_device(SPI_HandleTypeDef * spi_ptr, NrfSpiDevice_ptr device_ptr, NrfIoDescriptor_ptr descriptor_ptr);

static void flash_led_forever(uint32_t interval);