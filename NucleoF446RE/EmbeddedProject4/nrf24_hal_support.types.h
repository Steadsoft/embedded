struct nrf24_io_descriptor
{
	SPI_HandleTypeDef * spi_ptr;
	GPIO_TypeDef * gpio_ptr;
	
	HAL_StatusTypeDef status;
	uint8_t cs_pin;
	uint8_t ce_pin;
};

struct nrf24_hal_support_interface
{
	void (*init_spi)(SPI_HandleTypeDef * spi_ptr);
	void (*init_control_pins)();
	void (*spi_ce_lo)(void *);
	void (*spi_ce_hi)(void *);
	void (*spi_cs_lo)(void *);
	void (*spi_cs_hi)(void *);
	void (*exchange_bytes)(void *, uint8_t[], uint8_t[], uint8_t);
	void (*read_bytes)(void *, uint8_t bytes_in_ptr[], uint8_t count);
	void (*write_bytes)(void *, uint8_t bytes_out_ptr[], uint8_t count);
	void(*init_device)(SPI_HandleTypeDef * spi_ptr, NrfSpiDevice_ptr device_ptr, NrfIoDescriptor_ptr descriptor_ptr);
	void(*flash_led_forever)(uint32_t interval);
};


#if defined(nrf24_hal_support_implementer)
// Private types can go here, these will never been seen by consumer code when compiled.
#endif