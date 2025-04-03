struct nrf24_hal_support_interface
{
	void(*Configure)(uint32_t spi_base, int32_t int_pin, uint32_t ce_pin, uint32_t cs_pin, NrfSpiDevice_ptr device_ptr);
	void(*Deactivate)(NrfSpiDevice_ptr);
	void(*Activate)(NrfSpiDevice_ptr);
	void(*Select)(NrfSpiDevice_ptr);
	void(*Deselect)(NrfSpiDevice_ptr);
	void(*ExchangeBytes)(NrfSpiDevice_ptr, uint8_t[], uint8_t[], uint8_t);
	void(*ReadBytes)(NrfSpiDevice_ptr, uint8_t bytes_in_ptr[], uint8_t count);
	void(*WriteBytes)(NrfSpiDevice_ptr, uint8_t bytes_out_ptr[], uint8_t count);
	void(*flash_led_forever)(uint32_t interval);
};


#if defined(nrf24_hal_support_implementer)
// Private types can go here, these will never been seen by consumer code when compiled.
#endif