struct nrf24_hal_support_interface
{
	/**
	 * @brief Configures the selected SPI instance and associated GPIO pins
	 * for SPI to function. The GPIO port is implied by the SPI base
	 * address, the interrupt, CE and CS pins are also configured and must be in the same GPIO port as
	 * the chosen SPI instance.
	 * @param spi_base The base address of the SPI instance to be configured.
	 * @param int_pin The GPIO pin number for the interrupt line (negative value means no interrupt).
	 * @param ce_pin The GPIO pin number for the CE (Chip Enable) line.
	 * @param cs_pin The GPIO pin number for the CSN (Chip Select Not) line.
	 * @param device_ptr The returned configured device instance. 
	*/
	void(*Configure)(uint32_t spi_base, int32_t int_pin, uint32_t ce_pin, uint32_t cs_pin, NrfSpiDevice_ptr device_ptr);
	/** 
	 Sets the NRF device's CE pin to low
	 */
	void(*Deactivate)(NrfSpiDevice_ptr);
	/** 
	 Sets the NRF device's CE pin to high 
	 */
	void(*Activate)(NrfSpiDevice_ptr);
	/**
	 Sets the NRF device's SPI CSN pin to low 
	 */
	void(*Select)(NrfSpiDevice_ptr);
	/// <summary>
	/// Sets the NRF device's SPI CSN pin to high 
	/// </summmary>
	void(*Deselect)(NrfSpiDevice_ptr);
	void(*ExchangeBytes)(NrfSpiDevice_ptr, uint8_t[], uint8_t[], uint8_t);
	void(*ReadBytes)(NrfSpiDevice_ptr, uint8_t bytes_in_ptr[], uint8_t count);
	void(*WriteBytes)(NrfSpiDevice_ptr, uint8_t bytes_out_ptr[], uint8_t count);
	void(*flash_led_forever)(uint32_t interval);
};

struct nrf_spi_device
{
	SPI_HandleTypeDef spi;
	GPIO_TypeDef * gpio_ptr;
	HAL_StatusTypeDef status;
	uint8_t cs_pin;
	uint8_t ce_pin;
	uint8_t int_pin;
};


#if defined(nrf24_hal_support_implementer)
// Private types can go here, these will never been seen by consumer code when compiled.
#endif