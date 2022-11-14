#include <stm32f4xx_hal.h>
#include <nrf24_package.macros.h>
#include <nrf24_package.library.h>
#include <nrf24_hal_support.library.h>


//#include <cmsis_gcc.h>

// SEE: http://blog.gorski.pm/stm32-unique-id

#ifdef __cplusplus
extern "C"
#endif
typedef struct
{
	unsigned long fields[3];
} BoardId;


void update(NrfReg_RF_SETUP, NrfReg_RF_SETUP, NrfReg_RF_SETUP, NrfReg_RF_SETUP_ptr);

void enter_rx_mode(NrfSpiDevice_ptr device_ptr);

int get_board_id();
void spin_100_uS();
void send_commands(NrfSpiDevice_ptr device_ptr, int count);
void trapif(int, NrfSpiDevice_ptr);
void initialize_nrf(NrfSpiDevice_ptr device_ptr);

void print_register(uint8_t Register, uint8_t Value);

volatile uint8_t lock = 0;

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

int maintest(void)
{
	uint32_t state;

	HAL_Init();
	
	NrfReg_ALL_REGISTERS everything_before = { 0 };
	NrfReg_ALL_REGISTERS everything_after = { 0 };
	
	HAL_Delay(1000);
	
	int board = get_board_id();
	
	// Allocate these data structures on the stack.
	
	NrfReg_STATUS status;
	SPI_HandleTypeDef spi; 
	NrfSpiDevice device; 
	NrfIoDescriptor descriptor;
	NrfReg_CONFIG cfg;
	NrfReg_SETUP_AW aw = { 0 };
	
	// Perform all IO related initialization
	
	nrf24_hal_support.init_spi(&spi);
	nrf24_hal_support.init_control_pins();
	nrf24_hal_support.init_device(&spi, &device, &descriptor);
	
	// Snapshot all regsiters
	
	nrf24_package.GetRegister.ALL_REGISTERS(&device, &everything_before, &status);
	
	// Force all register into their hardware reset state.
	
	nrf24_package.DeviceControl.PowerOnReset(&device);
	
	// Snapshot all regsiters
	
	nrf24_package.GetRegister.ALL_REGISTERS(&device, &everything_after, &status);
		
	initialize_nrf(&device);
	
	enter_rx_mode(&device);
	
	// Slowly flash the Nucleo's LED to indicate that command sending is over.

	nrf24_hal_support.flash_led_forever(1000);

	return (0);
}



void send_commands(NrfSpiDevice_ptr device_ptr, int count)
{
	
	// Declare some NRF register variables.
	
	NrfReg_STATUS status;
	NrfReg_CONFIG configuration;
	NrfReg_EN_AA auto_acknowledge_flags;
	NrfReg_EN_RXADDR rx_addresses_flags;
	NrfReg_RX_ADDR_SHORT rx_address;
	NrfReg_RF_CH rf_channel;
	NrfReg_RF_SETUP rf_setup = { 0 };
	NrfReg_FEATURE device_features;
	NrfReg_SETUP_AW saw;
	
	nrf24_package.GetRegister.FEATURE(device_ptr, &device_features, &status);

	nrf24_package.GetRegister.RF_SETUP(device_ptr, &rf_setup, &status);
	
	nrf24_package.GetRegister.RF_CH(device_ptr, &rf_channel, &status);

	// Just a bunch of test calls into the various register read/write functions.
	
	nrf24_package.GetRegister.CONFIG(device_ptr, &configuration, &status);
	
	for (int X = 0; X < count; X++)
	{
		rf_setup.PLL_LOCK = 1;
		rf_setup.RF_PWR = 2;
	
		nrf24_package.GetRegister.RF_SETUP(device_ptr, &rf_setup, &status);
		
		//trapif(rf_setup.LNA_HCURR != 1 || rf_setup.RF_PWR != 3 || rf_setup.RF_DR != 1);
		
		nrf24_package.GetRegister.RX_ADDR_SHORT(device_ptr, &rx_address, 2, &status);
	
		trapif(rx_address.value != 0xC3, device_ptr);
		
		nrf24_package.GetRegister.RX_ADDR_SHORT(device_ptr, &rx_address, 3, &status);
		
		trapif(rx_address.value != 0xC4, device_ptr);
		
		nrf24_package.GetRegister.RX_ADDR_SHORT(device_ptr, &rx_address, 4, &status);
		
		trapif(rx_address.value != 0xC5, device_ptr);
		
		nrf24_package.GetRegister.RX_ADDR_SHORT(device_ptr, &rx_address, 5, &status);
		
		trapif(rx_address.value != 0xC6, device_ptr);
		
		nrf24_package.GetRegister.RF_CH(device_ptr, &rf_channel, &status);
		
		trapif(rf_channel.RF_CH != 0x02, device_ptr);

		rf_channel.RF_CH = 23;
		
		nrf24_package.SetRegister.RF_CH(device_ptr, rf_channel, &status);

		nrf24_package.GetRegister.RF_CH(device_ptr, &rf_channel, &status);
		
		trapif(rf_channel.RF_CH != 23, device_ptr);
		
		rf_channel.RF_CH = 2;

		nrf24_package.SetRegister.RF_CH(device_ptr, rf_channel, &status);

		nrf24_package.GetRegister.CONFIG(device_ptr, &(configuration), &status);
		nrf24_package.GetRegister.EN_AA(device_ptr, &(auto_acknowledge_flags), &status);
		nrf24_package.GetRegister.RX_ADDR_SHORT(device_ptr, &(rx_address), 3, &status);
		nrf24_package.GetRegister.SETUP_AW(device_ptr, &saw, &status);
		
		trapif(saw.AW != 0x03, device_ptr);
		
		nrf24_package.GetRegister.STATUS(device_ptr, &status);

		spin_100_uS();
	}
}

void trapif(int value, NrfSpiDevice_ptr device_ptr)
{
	if (!value)
		return;

	NrfReg_SETUP_AW saw;
	NrfReg_STATUS status;

	while (1)
	{
		nrf24_package.GetRegister.SETUP_AW(device_ptr, &saw, &status);
		spin_100_uS();
	}
	
	// Rapidly flash the Nucleo's LED to indicate an unexpected register read.
	
	nrf24_hal_support.flash_led_forever(20);
}
void print_register(uint8_t Register, uint8_t Value)
{
	switch (Register)
	{
	case 0x05:
		{
			NrfReg_RF_CH reg;
			//			BYTE_VALUE(reg) = Value;
			//			printf("RF_CH: RF_CH %d, ", reg.RF_CH);
			//			printf("RF.RESERVED %d\n", reg.RESERVED);
			return;
		}
	case 0x06:
		{
			NrfReg_RF_SETUP reg;
			//			BYTE_VALUE(reg) = Value;
			//			printf("RF_SETUP: LNA_HCURR %d, ", reg.LNA_HCURR);
			//			printf("RF_PWR %d, ", reg.RF_PWR);
			//			printf("RF_DR %d, ", reg.RF_DR);
			//			printf("PLL_LOCK %d, ", reg.PLL_LOCK);
			//			printf("RF.RESERVED %d\n", reg.RESERVED);
			return;
		}
	}
}

