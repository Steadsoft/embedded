struct nrf24_hal_support_interface
{
	void(*init_spi)(SPI_HandleTypeDef * spi_ptr, unsigned long spi_base, int32_t int_pin, uint32_t ce_pin, uint32_t cs_pin, NrfSpiDevice_ptr device_ptr);
	void(*spi_set_ce_lo)(NrfSpiDevice_ptr);
	void(*spi_set_ce_hi)(NrfSpiDevice_ptr);
	void(*spi_set_csn_lo)(NrfSpiDevice_ptr);
	void(*spi_set_csn_hi)(NrfSpiDevice_ptr);
	void(*exchange_bytes)(NrfSpiDevice_ptr, uint8_t[], uint8_t[], uint8_t);
	void(*read_bytes)(NrfSpiDevice_ptr, uint8_t bytes_in_ptr[], uint8_t count);
	void(*write_bytes)(NrfSpiDevice_ptr, uint8_t bytes_out_ptr[], uint8_t count);
	void(*flash_led_forever)(uint32_t interval);
};


#if defined(nrf24_hal_support_implementer)
// Private types can go here, these will never been seen by consumer code when compiled.
#endif