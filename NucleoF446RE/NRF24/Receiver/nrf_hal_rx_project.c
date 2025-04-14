#include <stdatomic.h>
#include <stdbool.h>
#include <malloc.h>
#include <stm32f4xx_hal.h>
#include <nrf24_hal_support.library.h>
#include <nrf24_package.library.h>

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


volatile uint32_t tx_ds_interrupt_count = 0;
volatile uint32_t sent_messages_count = 0;

volatile uint8_t tx_ds_irq_clear_pending = 0;
void initialize_nrf24_device(NrfSpiDevice_ptr device_ptr);
void TM_NRF24L01_PowerUpRx(NrfSpiDevice_ptr device_ptr);
int get_board_id();
void spin_100_uS();
void spin_20_uS();
void spin_500_uS();

static void fault_handler(NrfSpiDevice_ptr device_ptr, NrfErrorCode code);


void TM_NRF24L01_PowerUpTx(NrfSpiDevice_ptr device_ptr);

void TM_NRF24L01_Transmit(NrfSpiDevice_ptr device_ptr, uint8_t * data, uint8_t len);
void CreateMemoryPool(uint8_t Size, uint8_t Quantity, uint8_t Alignment, PoolHeader_ptr * Pool_ptr);
void EXTI0_IRQPostHandler(NrfSpiDevice_ptr device_ptr);

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

NrfSpiDevice device = { 0 }; 

int msgs_rx = 0;

int main(void)
{
	NrfReg_ALL_REGISTERS everything_before = { 0 };
	NrfReg_ALL_REGISTERS everything_after = { 0 };
	NrfReg_CONFIG cfg = { 0 };
	NrfReg_SETUP_AW aw = { 0 };
	NrfReg_STATUS status;
	NrfReg_STATUS status_mask_irq = { 0 };
	NrfReg_STATUS status_irq = { 0 };
	SPI_HandleTypeDef spi = { 0 }; 
	uint32_t state = 0;
	uint8_t buffer[32] = { 0 };
	uint8_t send_polls = 0;
	PoolHeader_ptr pool_ptr; 
	uint8_t rx_addr[] = { 0xE7, 0xE7, 0xE7, 0xE7, 0xE7 }; // this is just the default system reset value for the RX_ADDR_P0 reg

//	CreateMemoryPool(17, 64, 8, &pool_ptr);
//	CreateMemoryPool(23, 64, 8, &pool_ptr);
//	CreateMemoryPool(24, 64, 8, &pool_ptr);

	HAL_Init();
	
	// Perform all IO related initialization
	
	nrf24_hal_support.Configure(SPI1, TIM1, GPIO_PIN_0, EXTI0_IRQn, NRF_CE, SPI_CS, &device, fault_handler); 

	// Force all register into their hardware reset state.
	
	nrf24_package.Action.PowerOnReset(&device);
		
	nrf24_package.Action.Initialize(&device);
	
	nrf24_package.Action.EnterReceiveMode(&device, rx_addr, 1, 100, 32); 
	
	nrf24_package.Read.ALL_REGISTERS(&device, &everything_after, &status);

	while (1)
	{
		//HAL_Delay(-1);
		
		//nrf24_package.Read.ALL_REGISTERS(&device, &everything_after, &status);
		
		//if (everything_after.Status.RX_DR)
		//	break;

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
} 

void EXTI0_IRQPostHandler(NrfSpiDevice_ptr device_ptr)
{
	NrfReg_STATUS status_irq;
	
	tx_ds_interrupt_count++;
	
	nrf24_package.Read.STATUS(device_ptr, &status_irq);

	if (status_irq.TX_DS)
	{
		nrf24_package.Write.STATUS(device_ptr, status_irq, &status_irq);
	}
	
	tx_ds_irq_clear_pending = 0;
}



void AllocateInPool(PoolHeader_ptr * Pool_ptr)
{
	
}

static void fault_handler(NrfSpiDevice_ptr device_ptr, NrfErrorCode code)
{
	;
}
