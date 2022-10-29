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

typedef struct
{
	unsigned long fields[3];
} BoardId;


void init_peripherals()
{
	
}
void init_nrf_registers(NrfLibrary * lib, NrfSpiDevice * device);
int get_board_id();

void GenerateTestSPISignal();

// SEE: https://github.com/mokhwasomssi/stm32_hal_nrf24l01p

int get_board_id()
{
	static int known = -1;
	static BoardId board1 = { .fields[0] = 0x0039001E, .fields[1] = 0x31385119, .fields[2] = 0x36323738 };
	static BoardId board2 = { .fields[0] = 0x0042002F, .fields[1] = 0x4633500F, .fields[2] = 0x20353836 };

	if (known != -1)
		return known;
	
	unsigned long ID0 = (*(unsigned long *)0x1FFF7A10);
	unsigned long ID1 = (*(unsigned long *)0x1FFF7A14);
	unsigned long ID2 = (*(unsigned long *)0x1FFF7A18);
	
	if (ID0 == board1.fields[0] && ID1 == board1.fields[1] && ID2 == board1.fields[2])
	{
		known = 1;
		return known;
	}
	
	if (ID0 == board2.fields[0] && ID1 == board2.fields[1] && ID2 == board2.fields[2])
	{
		known = 2;
		return known;
	}

	known = 0;
	return known;
}

int main(void)
{
	// This is the MCU's unique ID, these addresses are specific to the F4 family.
	
	SPI_HandleTypeDef spi; 
	GPIO_InitTypeDef  GPIO_InitStruct_spi;
	GPIO_InitTypeDef  GPIO_InitStruct_ctrl;
	BoardId id;
	
	int board = get_board_id();
	
	HAL_Init();
	
	board = get_board_id();
	
	__SPI1_CLK_ENABLE();
	
	spi.Instance = SPI1;
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
	
	HAL_SPI_Init(&spi);
	
	__GPIOA_CLK_ENABLE();

	GPIO_InitStruct_spi.Pin       = GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7;
	GPIO_InitStruct_spi.Mode      = GPIO_MODE_AF_PP;
	GPIO_InitStruct_spi.Pull      = GPIO_PULLUP;
	GPIO_InitStruct_spi.Speed     = GPIO_SPEED_HIGH;
	GPIO_InitStruct_spi.Alternate = GPIO_AF5_SPI1;
 
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct_spi);
    
	GPIO_InitStruct_ctrl.Pin  = NRF_CE | SPI_CS;
	GPIO_InitStruct_ctrl.Mode = GPIO_MODE_OUTPUT_PP;

	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct_ctrl);

	HAL_GPIO_WritePin(GPIOA, SPI_CS, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, NRF_CE, GPIO_PIN_RESET);

	InitializeLibrary(&library);

	library.InitializeDevice(&spi, GPIOA, SPI_CS, NRF_CE, &device);

	init_nrf_registers(&library, &device);
	
	GenerateTestSPISignal();
}

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
	
		library.ReadSingleByteRegister(&device, NrfRegister.RX_ADDR_P3, &regval, &status);
		library.ReadSingleByteRegister(&device, NrfRegister.CONFIG, &config, &status);
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


void init_nrf_registers(NrfLibrary * lib, NrfSpiDevice * device)
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