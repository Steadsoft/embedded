#include <stm32f4xx_hal.h>
#include <stdio.h>

#include <NRF24L01_package.library.h>
#include <nrf_hal_support.library.h>


// SEE: http://blog.gorski.pm/stm32-unique-id


#ifdef __cplusplus
extern "C"
#endif
void SysTick_Handler(void)
{
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}
 
// This code works for the Nucleo F446RE board


struct bits
{
	unsigned int B0 : 1;
	unsigned int B1 : 1;
	unsigned int B2 : 1;
	unsigned int B3 : 1;
	unsigned int B4 : 1;
	unsigned int B5 : 1;
	unsigned int B6 : 2;

};


typedef struct
{
	unsigned long fields[3];
} BoardId;


void init_nrf_registers(NrfSpiDevice * device);
int get_board_id();
void sleep_100_uS();
void send_commands(NrfSpiDevice_ptr device_ptr, int count);
void trap();

void print_register(uint8_t Register, uint8_t Value);

// SEE: https://github.com/mokhwasomssi/stm32_hal_nrf24l01p

int get_board_id()
{
	static int known = -1;
	static BoardId board1 = { .fields[0] = 0x0039001E, .fields[1] = 0x31385119, .fields[2] = 0x36323738 };
	static BoardId board2 = { .fields[0] = 0x0042002F, .fields[1] = 0x4633500F, .fields[2] = 0x20353836 };

	if (known != -1)
		return known;

	// This is the MCU's unique ID, these addresses are specific to the F4 family.

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


void sleep_100_uS()
{
	for (int X = 0; X < 122; X++)
	{
		;
	}
}

int main(void)
{
	HAL_Init();
	
	int board = get_board_id();

	// Allocate these data structures on the stack.
	
	SPI_HandleTypeDef spi; 
	NrfSpiDevice device; 
	NrfIoDescriptor descriptor;
	
	// Perform all IO related initialization
	
	NrfHalSupport.init_spi(&spi);
	NrfHalSupport.init_control_pins();
	NrfHalSupport.init_device(&spi, &device, &descriptor);
	
	// Send a bunch of NRF commands to the device.
	
	send_commands(&device, 2000);
	
	// Flash the Nucleo's LED to indicate that command sending is over.
	
	NrfHalSupport.flash_led_forever();
	
	return(0);
}

void send_commands(NrfSpiDevice_ptr device_ptr, int count)
{
	
	
	uint8_t RX_ADDR1[5] = { 0x00, 0x01, 0x02, 0x03, 0x04 };
	uint8_t RX_ADDR2[5] = { 0x04, 0x03, 0x02, 0x01, 0x00 };

	uint8_t BUFFER[5];
	
	uint8_t regval;
	NrfReg_STATUS status;
	NrfReg_CONFIG configuration;
	NrfReg_EN_AA en_aa;
	NrfReg_EN_RXADDR en_rxaddr;
	NrfReg_RX_ADDR rxaddr;
	NrfReg_RF_CH rfchan;
	NrfReg_RF_SETUP rf = { 0 };
	NrfReg_FEATURE ftr;
	NrfReg_SETUP_AW saw;
	uint8_t multisize;
	
	NrfLibrary.GetRegister.FEATURE(device_ptr, &ftr, &status);

	NrfLibrary.GetRegister.RF_SETUP(device_ptr, &rf, &status);
	
	//print_register(NrfRegister.RF_SETUP, BYTE_VALUE(rf));
	
	NrfLibrary.GetRegister.RF_CH(device_ptr, &rfchan, &status);

	//print_register(NrfRegister.RF_CH, BYTE_VALUE(rfchan));

	// Just a bunch of test calls into the various register read/write functions.
	
	NrfLibrary.GetRegister.CONFIG(device_ptr, &configuration, &status);
	
	for (int X=0; X < count; X++)
	{
		rf.PLL_LOCK = 1;
		rf.RF_PWR = 2;
	
		BYTE_VALUE(rf) = 0;
		
		NrfLibrary.GetRegister.RF_SETUP(device_ptr, &rf, &status);
		
		
		NrfLibrary.GetRegister.RX_ADDR(device_ptr, &rxaddr, 2, &status);
		if (rxaddr.value != 0xC3) trap();
		
		NrfLibrary.GetRegister.RX_ADDR(device_ptr, &rxaddr, 3, &status);
		if (rxaddr.value != 0xC4) trap();
		
		NrfLibrary.GetRegister.RX_ADDR(device_ptr, &rxaddr, 4, &status);
		if (rxaddr.value != 0xC5) trap();
		
		NrfLibrary.GetRegister.RX_ADDR(device_ptr, &rxaddr, 5, &status);
		if (rxaddr.value != 0xC6) trap();
		
		NrfLibrary.GetRegister.RF_CH(device_ptr, &rfchan, &status);
		if (rfchan.RF_CH != 0x02) trap();

		rfchan.RF_CH = 23;
		
		NrfLibrary.SetRegister.RF_CH(device_ptr, rfchan, &status);

		NrfLibrary.GetRegister.RF_CH(device_ptr, &rfchan, &status);
		
		if (rfchan.RF_CH != 23) trap();
		
		rfchan.RF_CH = 2;

		NrfLibrary.SetRegister.RF_CH(device_ptr, rfchan, &status);

		NrfLibrary.GetRegister.CONFIG(device_ptr, &(configuration), &status);
		NrfLibrary.GetRegister.EN_AA(device_ptr, &(en_aa), &status);
		NrfLibrary.GetRegister.RX_ADDR(device_ptr, &(rxaddr),3, &status);
		NrfLibrary.GetRegister.SETUP_AW(device_ptr, &saw, &status);
		
		if (saw.AW != 0x03)
			break;

		sleep_100_uS();
		
//		HAL_Delay(1);
	}
}

void trap()
{
	;
}
void init_nrf_registers(NrfSpiDevice * device)
{	NrfReg_STATUS status;

	NrfReg_CONFIG config = { 0 };
	NrfReg_EN_AA en_aa = { 0 };
	NrfReg_EN_RXADDR en_rxaddr = { 0 };
	NrfReg_SETUP_RETR setup_retr = { 0 };
	NrfReg_RF_CH rf_ch = { 0 };
	NrfReg_RF_SETUP rf_setup = { 0 };
	NrfReg_SETUP_AW setup_aw = { 0 };
	
	NrfLibrary.SetRegister.CONFIG(device, config, &status);
	NrfLibrary.SetRegister.EN_AA(device, en_aa, &status);
	NrfLibrary.SetRegister.EN_RX_ADDR(device, en_rxaddr, &status);
	NrfLibrary.SetRegister.SETUP_RETR(device, setup_retr, &status);
	NrfLibrary.SetRegister.RF_CH(device, rf_ch, &status);
	NrfLibrary.SetRegister.RF_SETUP(device, rf_setup, &status);
	
	setup_aw.AW = 3;
	
	NrfLibrary.SetRegister.SETUP_AW(device, setup_aw, &status);

}

void print_register(uint8_t Register, uint8_t Value)
{
	switch (Register)
	{
	case 0x05:
		{
			NrfReg_RF_CH reg;
			BYTE_VALUE(reg) = Value;
			printf("RF_CH: RF_CH %d, ", reg.RF_CH);
			printf("RF.RESERVED %d\n", reg.RESERVED);
			return;
		}
	case 0x06:
		{
			NrfReg_RF_SETUP reg;
			BYTE_VALUE(reg) = Value;
			printf("RF_SETUP: LNA_HCURR %d, ", reg.LNA_HCURR);
			printf("RF_PWR %d, ", reg.RF_PWR);
			printf("RF_DR %d, ", reg.RF_DR);
			printf("PLL_LOCK %d, ", reg.PLL_LOCK);
			printf("RF.RESERVED %d\n", reg.RESERVED);
			return;
		}
	}
}