#include <stm32f4xx_hal.h>

#include <NRF24L01_macros.h>
#include <NRF24L01_typedefs.h>
#include <NRF24L01_structs.h>
#include <NRF24L01_externs.h>
#include <NRF24L01_functions.h>

#include <nrf_hal_typedefs.h>
#include <nrf_hal_structs.h>
#include <nrf_hal_functions.h>

void spi_ce_lo(void * ptr)
{
	HAL_GPIO_WritePin(((NrfIoDescriptor_ptr)ptr)->gpio_ptr, ((NrfIoDescriptor_ptr)ptr)->ce_pin, GPIO_PIN_RESET);
}
void spi_ce_hi(void * ptr)
{
	HAL_GPIO_WritePin(((NrfIoDescriptor_ptr)ptr)->gpio_ptr, ((NrfIoDescriptor_ptr)ptr)->ce_pin, GPIO_PIN_SET);
}
void spi_cs_lo(void * ptr)
{
	HAL_GPIO_WritePin(((NrfIoDescriptor_ptr)ptr)->gpio_ptr, ((NrfIoDescriptor_ptr)ptr)->cs_pin, GPIO_PIN_RESET);
}
void spi_cs_hi(void * ptr)
{
	HAL_GPIO_WritePin(((NrfIoDescriptor_ptr)ptr)->gpio_ptr, ((NrfIoDescriptor_ptr)ptr)->cs_pin, GPIO_PIN_SET);
}
void exchange_bytes(void * ptr, uint8_t bytes_out_ptr[], uint8_t bytes_in_ptr[], uint8_t count)
{
	((NrfIoDescriptor_ptr)ptr)->status = HAL_SPI_TransmitReceive(((NrfIoDescriptor_ptr)ptr)->spi_ptr, bytes_out_ptr, bytes_in_ptr, count, HAL_MAX_DELAY);
}

void read_bytes(void * ptr, uint8_t bytes_in_ptr[], uint8_t count)
{
	((NrfIoDescriptor_ptr)ptr)->status = HAL_SPI_Receive(((NrfIoDescriptor_ptr)ptr)->spi_ptr, bytes_in_ptr, count, HAL_MAX_DELAY);
}

void write_bytes(void * ptr, uint8_t bytes_out_ptr[], uint8_t count)
{
	((NrfIoDescriptor_ptr)ptr)->status = HAL_SPI_Receive(((NrfIoDescriptor_ptr)ptr)->spi_ptr, bytes_out_ptr, count, HAL_MAX_DELAY);
}