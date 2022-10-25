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
 
// This code works for the Nucleo F446RE board

#define SPI_CS GPIO_PIN_4
#define NRF_CE GPIO_PIN_1

void GenerateTestSPISignal()
{
	
    __SPI1_CLK_ENABLE();
	static SPI_HandleTypeDef spi = { .Instance = SPI1 };
	spi.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256;
	spi.Init.Direction = SPI_DIRECTION_2LINES;
	spi.Init.CLKPhase = SPI_PHASE_2EDGE;
	spi.Init.CLKPolarity = SPI_POLARITY_HIGH;
	spi.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLED;
	spi.Init.DataSize = SPI_DATASIZE_8BIT;
	spi.Init.FirstBit = SPI_FIRSTBIT_LSB;
	spi.Init.NSS = SPI_NSS_SOFT;
	spi.Init.TIMode = SPI_TIMODE_DISABLED;
	spi.Init.Mode = SPI_MODE_MASTER; 
	
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
    
	GPIO_InitStruct.Pin  = SPI_CS | NRF_CE;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	
    char message[] = "0123456789";
	char READ_R0[] = { 0x04 };
	char READ_R1[] = { 0x05 };
	char READ_R2[] = { 0x06 };
	char READ_R3[] = { 0x07 };
	char READ_R4[] = { 0x08 };
	char READ_R5[] = { 0x09 };
	char READ_R6[] = { 0x0A };
	char READ_R7[] = { 0x0B };

	int w, x, y, z;
	
	forever
	{
		HAL_GPIO_WritePin(GPIOA, SPI_CS, GPIO_PIN_RESET);
		HAL_SPI_Transmit(&spi, (uint8_t *)READ_R0, sizeof(READ_R0), HAL_MAX_DELAY);
		HAL_GPIO_WritePin(GPIOA, SPI_CS, GPIO_PIN_SET);
		
		HAL_GPIO_WritePin(GPIOA, SPI_CS, GPIO_PIN_RESET);
		HAL_SPI_Transmit(&spi, (uint8_t *)READ_R1, sizeof(READ_R0), HAL_MAX_DELAY);
		HAL_GPIO_WritePin(GPIOA, SPI_CS, GPIO_PIN_SET);
		
		HAL_GPIO_WritePin(GPIOA, SPI_CS, GPIO_PIN_RESET);
		HAL_SPI_Transmit(&spi, (uint8_t *)READ_R2, sizeof(READ_R0), HAL_MAX_DELAY);
		HAL_GPIO_WritePin(GPIOA, SPI_CS, GPIO_PIN_SET);
		
		HAL_GPIO_WritePin(GPIOA, SPI_CS, GPIO_PIN_RESET);
		HAL_SPI_Transmit(&spi, (uint8_t *)READ_R3, sizeof(READ_R0), HAL_MAX_DELAY);
		HAL_GPIO_WritePin(GPIOA, SPI_CS, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOA, SPI_CS, GPIO_PIN_RESET);
		HAL_SPI_Transmit(&spi, (uint8_t *)READ_R4, sizeof(READ_R0), HAL_MAX_DELAY);
		HAL_GPIO_WritePin(GPIOA, SPI_CS, GPIO_PIN_SET);
		
		HAL_GPIO_WritePin(GPIOA, SPI_CS, GPIO_PIN_RESET);
		HAL_SPI_Transmit(&spi, (uint8_t *)READ_R5, sizeof(READ_R0), HAL_MAX_DELAY);
		HAL_GPIO_WritePin(GPIOA, SPI_CS, GPIO_PIN_SET);
		
		HAL_GPIO_WritePin(GPIOA, SPI_CS, GPIO_PIN_RESET);
		HAL_SPI_Transmit(&spi, (uint8_t *)READ_R6, sizeof(READ_R0), HAL_MAX_DELAY);
		HAL_GPIO_WritePin(GPIOA, SPI_CS, GPIO_PIN_SET);
		
		HAL_GPIO_WritePin(GPIOA, SPI_CS, GPIO_PIN_RESET);
		HAL_SPI_Transmit(&spi, (uint8_t *)READ_R7, sizeof(READ_R0), HAL_MAX_DELAY);
		HAL_GPIO_WritePin(GPIOA, SPI_CS, GPIO_PIN_SET);

		HAL_Delay(10);

	}
}
 
int main(void)
{
	HAL_Init();
	GenerateTestSPISignal();
}