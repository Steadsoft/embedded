#include <stm32f4xx_hal.h>

#define forever for(;;)

#ifdef __cplusplus
extern "C"
#endif
void SysTick_Handler(void)
{
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}
 
#include <string.h>
#include <NRF24L01_types.h>
#include <NRF24L01_calls.h>
 
// This code works for the Nucleo F446RE board

#define SPI_CS GPIO_PIN_4
#define NRF_CE GPIO_PIN_1

void spi_cs_lo();
void spi_cs_hi();

// SEE: https://github.com/mokhwasomssi/stm32_hal_nrf24l01p

void GenerateTestSPISignal()
{
	
    __SPI1_CLK_ENABLE();
	static SPI_HandleTypeDef spi = { .Instance = SPI1 };
	spi.Init.Mode = SPI_MODE_MASTER; 
	spi.Init.Direction = SPI_DIRECTION_2LINES;
	spi.Init.DataSize = SPI_DATASIZE_8BIT;
	spi.Init.CLKPolarity = SPI_POLARITY_LOW;
	spi.Init.CLKPhase = SPI_PHASE_1EDGE;
	spi.Init.NSS = SPI_NSS_SOFT; // SPI_NSS_HARD_OUTPUT
	spi.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256;
	spi.Init.FirstBit = SPI_FIRSTBIT_MSB;
	spi.Init.TIMode = SPI_TIMODE_DISABLED;
	spi.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLED;
	spi.Init.CRCPolynomial = 10;
	
	if (HAL_SPI_Init(&spi) != HAL_OK)
	{
		asm("bkpt 255");
	}
	
	__GPIOA_CLK_ENABLE();
	GPIO_InitTypeDef  GPIO_InitStruct;
  
	GPIO_InitStruct.Pin       = GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7;
	GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull      = GPIO_PULLUP;
	GPIO_InitStruct.Speed     = GPIO_SPEED_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
 
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    
	GPIO_InitStruct.Pin  = NRF_CE | SPI_CS;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	HAL_GPIO_WritePin(GPIOA, SPI_CS, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, NRF_CE, GPIO_PIN_RESET);

	NrfSpi device = { .spi_ptr = &spi, .gpio_ptr = GPIOA, .cs_pin = SPI_CS, .ce_pin = NRF_CE };
	
	//uint8_t RX_ADDR[5] = { 0x00, 0x01, 0x02, 0x03, 0x04 };
	uint8_t BUFFER[5];
	
	uint8_t regval;
	uint8_t statval;
	uint8_t multisize;
	
	forever
	{
		ReadSingleByteRegister(&device, NrfRegister.RX_ADDR_P2, &regval, &statval);
		ReadSingleByteRegister(&device, NrfRegister.RX_ADDR_P3, &regval, &statval);
		ReadSingleByteRegister(&device, NrfRegister.RX_ADDR_P4, &regval, &statval);
		ReadSingleByteRegister(&device, NrfRegister.EN_AA, &regval, &statval);
		ReadSingleByteRegister(&device, NrfRegister.EN_RXADDR, &regval, &statval);
		ReadSingleByteRegister(&device, NrfRegister.SETUP_AW, &regval, &statval);
		ReadMultiBytesRegister(&device, NrfRegister.RX_ADDR_P0, BUFFER, &multisize, &statval);
	}
}

int main(void)
{
	HAL_Init();
	GenerateTestSPISignal();
}