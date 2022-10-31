#include <stm32f4xx_hal.h>

#include <NRF24L01_macros.h>
#include <NRF24L01_typedefs.h>
#include <NRF24L01_structs.h>
#include <NRF24L01_externs.h>
#include <NRF24L01_functions.h>

#include <nrf_hal_typedefs.h>
#include <nrf_hal_structs.h>
#include <nrf_hal_functions.h>

void spi_cs_lo(NrfIoDescriptor_ptr ptr)
{
	HAL_GPIO_WritePin(ptr->gpio_ptr, ptr->cs_pin, GPIO_PIN_RESET);
}
void spi_cs_hi(NrfIoDescriptor_ptr ptr)
{
	HAL_GPIO_WritePin(ptr->gpio_ptr, ptr->cs_pin, GPIO_PIN_SET);
}
void exchange_bytes(NrfIoDescriptor_ptr ptr, uint8_t bytes_out_ptr[], uint8_t bytes_in_ptr[], uint8_t count)
{
	ptr->status = HAL_SPI_TransmitReceive(ptr->spi_ptr, bytes_out_ptr, bytes_in_ptr, count, HAL_MAX_DELAY);
}

void read_bytes(NrfIoDescriptor_ptr ptr, uint8_t bytes_in_ptr[], uint8_t count)
{
	ptr->status = HAL_SPI_Receive(ptr->spi_ptr, bytes_in_ptr, count, HAL_MAX_DELAY);
}

void write_bytes(NrfIoDescriptor_ptr ptr, uint8_t bytes_out_ptr[], uint8_t count)
{
	ptr->status = HAL_SPI_Receive(ptr->spi_ptr, bytes_out_ptr, count, HAL_MAX_DELAY);
}