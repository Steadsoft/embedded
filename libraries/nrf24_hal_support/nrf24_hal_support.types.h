struct nrf24_hal_support_interface
{
	/**
	 * @brief Configures the selected SPI instance and associated GPIO pins
	 * for SPI to function. The GPIO port is implied by the SPI base
	 * address, the interrupt, CE and CS pins are also configured and must be in the same GPIO port as
	 * the chosen SPI instance.
	 * @param spi_base The base address of the SPI instance to be configured.
	 * @param tim_base The base address of the timer instance to be used for CE pulse generation.
	 * @param int_pin The GPIO pin number for the interrupt line (negative value means no interrupt).
	 * @param ce_pin The GPIO pin number for the CE (Chip Enable) line.
	 * @param cs_pin The GPIO pin number for the CSN (Chip Select Not) line.
	 * @param device_ptr The returned configured device instance. 
	*/
	void(*ConfigureHardware)(NrfSpiSetup_ptr spi_setup, TIM_TypeDef * tim_base, uint64_t int_pin, uint32_t ext_int_id, uint64_t ce_pin, uint64_t cs_pin, NrfDevice_ptr device_ptr, nrf_fault_handler handler);
	/** 
	 Sets the NRF device's CE pin to low
	 */
	void(*Deactivate)(NrfDevice_ptr);
	/** 
	 Sets the NRF device's CE pin to high 
	 */
	void(*Activate)(NrfDevice_ptr);
	/**
	 Sets the NRF device's SPI CSN pin to low 
	 */
	void(*Select)(NrfDevice_ptr);
	/**
	 Sets the NRF device's SPI CSN pin to high 
	*/
	void(*Deselect)(NrfDevice_ptr);
	void(*ExchangeBytes)(NrfDevice_ptr, uint8_t[], uint8_t[], uint8_t);
	void(*ReadBytes)(NrfDevice_ptr, uint8_t bytes_in_ptr[], uint8_t count);
	void(*WriteBytes)(NrfDevice_ptr, uint8_t bytes_out_ptr[], uint8_t count);
	void(*flash_led_forever)(uint32_t interval);
};

struct nrf_interrupt
{
	volatile uint32_t complete;
	uint32_t spins;
	uint32_t max_so_far;
	uint32_t count;
};


struct nrf_device
{
	SPI_HandleTypeDef spi;
	TIM_HandleTypeDef pulse_timer;
	//GPIO_TypeDef * gpio_ptr;
	HAL_StatusTypeDef status;
	uint64_t cs_pin;
	uint64_t ce_pin;
	uint8_t int_pin;
	uint8_t configured;
	nrf_fault_handler FaultHandler;
	uint32_t tx_count;
	uint32_t rx_count;
	volatile NrfInterrupt tx_interrupt;
	volatile NrfInterrupt rx_interrupt;
};

struct nrf_spi_setup
{
	uint32_t pin_alt;
	uint64_t cs_pin;
	uint64_t mosi_pin;
	uint64_t miso_pin;
	uint64_t sck_pin;
	SPI_TypeDef  * spi;
};


enum nrf_error_code
{
	NULL_ARG_PTR,
	INVALID_INTERRUPT_PIN,
	INVALID_CE_PIN,
	INVALID_CS_PIN,
	INVALID_PIN_COMBINATION,
	INVALID_SPI_BASE,
	HAL_SPI_INIT_ERROR,
	HAL_TIM_INIT_ERROR,
    HAL_TIM_START_ERROR,
	DEVICE_MUST_BE_CONFIGURED,
	INVALID_PAYLOAD_SIZE

};


#if defined(nrf24_hal_support_implementer)
// Private types can go here, these will never been seen by consumer code when compiled.
#endif