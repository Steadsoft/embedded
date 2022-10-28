#include <stm32f4xx_hal.h>

#define forever for(;;)

// SEE: http://blog.gorski.pm/stm32-unique-id


#ifdef __cplusplus
extern "C"
#endif
void SysTick_Handler(void)
{
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}
 
#include <string.h>

#include <NRF24L01_defs.h>
#include <NRF24L01_types.h>
#include <NRF24L01_calls.h>
 
// This code works for the Nucleo F446RE board

#define SPI_CS GPIO_PIN_4
#define NRF_CE GPIO_PIN_1

NrfLibrary library;
NrfSpiDevice device; 

void spi_cs_lo();
void spi_cs_hi();
void nrf_init();

// SEE: https://github.com/mokhwasomssi/stm32_hal_nrf24l01p

void GenerateTestSPISignal()
{
	
	
	uint8_t RX_ADDR1[5] = { 0x00, 0x01, 0x02, 0x03, 0x04 };
	uint8_t RX_ADDR2[5] = { 0x04, 0x03, 0x02, 0x01, 0x00 };

	uint8_t BUFFER[5];
	
	uint8_t regval;
	STATUS status;
	CONFIG config;
	EN_AA en_aa;
	EN_RXADDR en_rxaddr;
	
	uint8_t multisize;
	
	// Just a bunch of test calls into the various register read/write functions.
	
	forever
	{
	
		library.ReadSingleByteRegister(&device, NrfRegister.CONFIG, &config, &status);
		library.ReadSingleByteRegister(&device, NrfRegister.RX_ADDR_P3, &regval, &status);
		library.ReadSingleByteRegister(&device, NrfRegister.RX_ADDR_P4, &regval, &status);
		library.ReadSingleByteRegister(&device, NrfRegister.EN_AA, &en_aa, &status);
		library.ReadSingleByteRegister(&device, NrfRegister.EN_RXADDR, &en_rxaddr, &status);
		library.ReadSingleByteRegister(&device, NrfRegister.SETUP_AW, &regval, &status);
		library.ReadMultiBytesRegister(&device, NrfRegister.RX_ADDR_P0, BUFFER, &multisize, &status);
		
		library.WriteMultiBytesRegister(&device, NrfRegister.RX_ADDR_P0, RX_ADDR1, &multisize, &status);
		library.ReadMultiBytesRegister(&device, NrfRegister.RX_ADDR_P0, BUFFER, &multisize, &status);
		
		library.WriteMultiBytesRegister(&device, NrfRegister.RX_ADDR_P0, RX_ADDR2, &multisize, &status);
		library.ReadMultiBytesRegister(&device, NrfRegister.RX_ADDR_P0, BUFFER, &multisize, &status);

		HAL_Delay(1);
	}
}

int main(void)
{
	// This is the MCU's unique ID, these addresses are specific to the F4 family.
	
	unsigned long ID1 = (*(unsigned long *)0x1FFF7A10);
	unsigned long ID2 = (*(unsigned long *)0x1FFF7A14);
	unsigned long ID3 = (*(unsigned long *)0x1FFF7A18);
	
	HAL_Init();
	
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

	InitializeLibrary(&library);

	library.InitializeDevice(&spi, GPIOA, SPI_CS, NRF_CE, &device);

	nrf_init(&library, &device);
	
	GenerateTestSPISignal();
}

void nrf_init(NrfLibrary * lib, NrfSpiDevice * device)
{	STATUS status;

	uint8_t arg = 0;
	
	lib->WriteSingleByteRegister(device, NrfRegister.CONFIG, &arg, &status);
	lib->WriteSingleByteRegister(device, NrfRegister.EN_AA, &arg, &status);
	lib->WriteSingleByteRegister(device, NrfRegister.EN_RXADDR, &arg, &status);
	lib->WriteSingleByteRegister(device, NrfRegister.SETUP_RETR, &arg, &status);
	lib->WriteSingleByteRegister(device, NrfRegister.RF_CH, &arg, &status);
	lib->WriteSingleByteRegister(device, NrfRegister.RF_SETUP, &arg, &status);
	
	arg = 3;
	
	lib->WriteSingleByteRegister(device, NrfRegister.SETUP_AW, &arg, &status);

}