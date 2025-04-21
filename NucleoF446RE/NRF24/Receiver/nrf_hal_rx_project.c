#include <stdatomic.h>
#include <stdbool.h>
#include <malloc.h>
#include <stm32f4xx_hal.h>
#include <nrf24_hal_support.library.h>
#include <nrf24_package.library.h>

#include <nrf_hal_rx_project.h>

#define ATOMIC_FLAG_OFF (atomic_flag){0};
# define ROUNDUP(N,ALIGN)	        (((N) +  ((ALIGN)-1)) & ~((ALIGN)-1))
//#include <cmsis_gcc.h>

#define SPI_CS GPIO_PIN_4
#define NRF_CE GPIO_PIN_1


// SEE: http://blog.gorski.pm/stm32-unique-id

#ifdef __cplusplus
extern "C"
#endif
void SysTick_Handler(void)
{
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}
typedef struct
{
	unsigned long fields[3];
} BoardId;

struct memory_pool_header
{
	uint32_t size;
	uint32_t quantity;
	uint32_t alignment;
	uint32_t pool_size;
	uint8_t bitmap[32];
};

typedef struct memory_pool_header PoolHeader, * PoolHeader_ptr;

int faults = 0;

volatile uint32_t tx_ds_interrupt_count = 0;
volatile uint32_t sent_messages_count = 0;

volatile uint8_t tx_ds_irq_clear_pending = 0;
void initialize_nrf24_device(NrfDevice_ptr device_ptr);
void TM_NRF24L01_PowerUpRx(NrfDevice_ptr device_ptr);
int get_board_id();
void spin_100_uS();
void spin_20_uS();
void spin_500_uS();

static void fault_handler(NrfDevice_ptr device_ptr, NrfErrorCode code);

void pulse_led(uint32_t interval);

void GPIOA_Pin5_Init(void);


void TM_NRF24L01_PowerUpTx(NrfDevice_ptr device_ptr);

void TM_NRF24L01_Transmit(NrfDevice_ptr device_ptr, uint8_t * data, uint8_t len);

void spin_20_uS()
{
	for (int X = 0; X < 25; X++)
	{
		;
	}
}

void spin_100_uS()
{
	for (int X = 0; X < 122; X++)
	{
		;
	}
}

void spin_500_uS()
{
	for (int X = 0; X < 610; X++)
	{
		;
	}
}

NrfDevice device = { 0 }; 

int msgs_rx = 0;

volatile int8_t msg_received = 0;

int main(void)
{
	NrfReg_ALL_REGISTERS everything_before = { 0 };
	NrfReg_ALL_REGISTERS everything_after = { 0 };
	NrfReg_CONFIG cfg = { 0 };
	NrfReg_SETUP_AW aw = { 0 };
	NrfReg_STATUS status;
	NrfReg_STATUS status_mask_irq = { 0 };
	NrfReg_STATUS status_irq = { 0 };
	NrfSpiSetup spi_setup = { 0 };
	SPI_HandleTypeDef spi = { 0 }; 
	uint32_t state = 0;
	uint8_t buffer[32] = { 0 };
	uint8_t send_polls = 0;
	PoolHeader_ptr pool_ptr; 
	uint8_t rx_addr[] = { 0xE7, 0xE7, 0xE7, 0xE7, 0xE7 }; // this is just the default system reset value for the RX_ADDR_P0 reg

	HAL_Init();
	
	GPIOA_Pin5_Init();
	
	// Perform all IO related initialization
	
	spi_setup.sck_pin  = PB13;
	spi_setup.miso_pin = PB14;
	spi_setup.mosi_pin = PB15;
	spi_setup.pin_alt  = GPIO_AF5_SPI2;
	spi_setup.spi      = SPI2;
	
	nrf24_hal_support.Configure(&spi_setup, TIM1, PA0, EXTI0_IRQn, PA1, PB12, &device, fault_handler); 
	
	// Force all register into their hardware reset state.
	
	nrf24_package.Action.PowerOnReset(&device);
		
	nrf24_package.Action.Initialize(&device);
	
	nrf24_package.Action.EnterReceiveMode(&device, rx_addr, 1, 100, 32, MIN_RATE); 
	
	nrf24_package.Read.ALL_REGISTERS(&device, &everything_after, &status);
	
	while (1)
	{
		if (msg_received)
		{
			msg_received = 0;
			pulse_led(50);
		}
		
		HAL_Delay(1);
	}

	return(0);
}

void EXTI0_IRQHandler(void)
{
	uint8_t data[32];
	NrfReg_STATUS status;
	
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
	
	nrf24_package.Read.STATUS(&device, &status);
	
	if (status.RX_DR)
	{
		status.TX_DS = 0;
		status.MAX_RT = 0;
		nrf24_package.Write.STATUS(&device, status, &status);
	}
	
	nrf24_package.Command.R_RX_PAYLOAD(&device, data, 32, &status);
	
	msg_received = 1;
} 

void pulse_led(uint32_t interval)
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
	HAL_Delay(interval);	
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
}

void GPIOA_Pin5_Init(void)
{
	// Enable the GPIOA clock
	__HAL_RCC_GPIOA_CLK_ENABLE();

	// Define a GPIO_InitTypeDef structure for configuration
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	// Configure pin 5 as output
	GPIO_InitStruct.Pin = GPIO_PIN_5;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP; // Push-pull output
	GPIO_InitStruct.Pull = GPIO_NOPULL; // No pull-up or pull-down resistor
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW; // Low frequency for LED

	// Initialize the GPIOA pin
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

static void fault_handler(NrfDevice_ptr device_ptr, NrfErrorCode code)
{
	faults++;
}