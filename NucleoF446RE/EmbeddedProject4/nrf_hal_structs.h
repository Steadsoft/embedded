#include <stm32f4xx_hal.h>


struct nrf_io_descriptor
{
	SPI_HandleTypeDef * spi_ptr;
	GPIO_TypeDef * gpio_ptr;
	HAL_StatusTypeDef status;
	uint8_t cs_pin;
	uint8_t ce_pin;
};
