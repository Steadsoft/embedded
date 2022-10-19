
#include <stm32f4xx_hal.h>
#include <stm32_hal_legacy.h>

#ifdef __cplusplus
extern "C"
#endif
	
void SysTick_Handler(void);

void multiplex();	
	
void SysTick_Handler(void)
{
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
	multiplex();
}

#define A 0
#define B 1
#define C 2
#define D 3
#define E 4
#define F 5
#define G 6

typedef struct 
{
	GPIO_TypeDef * gpio_ptr;
	uint16_t	   gpio_pin;
} Segment;

Segment segment[7];
GPIO_PinState place = GPIO_PIN_RESET;
void write(int digit);
uint16_t LSD;
uint16_t MSD;
uint16_t pos = 0;
GPIO_PinState invert(GPIO_PinState * state);
/*
User LD2: the green LED is a user LED connected to ARDUINO® signal D13 corresponding
to STM32 I/O PA5 (pin 21) or PB13 (pin 34) depending on the STM32 target. Refer to
Table 11 to Table 23 when:
• the I/O is HIGH value, the LED is on
• the I/O is LOW, the LED is off 
• the I O is LOW, the LED is off 
• the I O is LOW, the LED is off 
*/
	
int main(void)
{
	
		
	HAL_Init();
	
	__GPIOA_CLK_ENABLE();
	__GPIOB_CLK_ENABLE();
	__GPIOC_CLK_ENABLE();

	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	
	uint16_t PORT_A_PINS = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_4;
	uint16_t PORT_B_PINS = GPIO_PIN_0 | GPIO_PIN_8 | GPIO_PIN_9;
	uint16_t PORT_C_PINS = GPIO_PIN_0 | GPIO_PIN_1;

	// Init the pins for port A
	
	GPIO_InitStructure.Pin = PORT_A_PINS;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	// Init the pin for port B
	
	GPIO_InitStructure.Pin = PORT_B_PINS;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	// Init the pins for port C

	GPIO_InitStructure.Pin = PORT_C_PINS;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	segment[0].gpio_ptr = GPIOA; // A
	segment[0].gpio_pin = GPIO_PIN_0;
	
	segment[1].gpio_ptr = GPIOA; // B
	segment[1].gpio_pin = GPIO_PIN_1;

	segment[2].gpio_ptr = GPIOA; // C
	segment[2].gpio_pin = GPIO_PIN_4;
	
	segment[3].gpio_ptr = GPIOB; // D
	segment[3].gpio_pin = GPIO_PIN_0;
	
	segment[4].gpio_ptr = GPIOC; // E
	segment[4].gpio_pin = GPIO_PIN_1;
	
	segment[5].gpio_ptr = GPIOC; // F
	segment[5].gpio_pin = GPIO_PIN_0;
	
	segment[6].gpio_ptr = GPIOB; // G
	segment[6].gpio_pin = GPIO_PIN_8;
	
	GPIO_PinState state = GPIO_PIN_RESET;
	
	uint16_t nibble;
	
	while (true)
	{
		for (uint16_t idx = 0; idx < 256; idx++)
		{
			LSD = idx % 16;
			MSD = idx / 16;
			HAL_Delay(100);
		}
	}
}

void write(int digit)
{
	
	for (uint16_t idx = 0; idx < 7; idx++)
	{
		HAL_GPIO_WritePin(segment[idx].gpio_ptr, segment[idx].gpio_pin, GPIO_PIN_RESET);
	}

	
	switch (digit)
	{
	case 0:
		{
			HAL_GPIO_WritePin(segment[A].gpio_ptr, segment[A].gpio_pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(segment[B].gpio_ptr, segment[B].gpio_pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(segment[C].gpio_ptr, segment[C].gpio_pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(segment[D].gpio_ptr, segment[D].gpio_pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(segment[E].gpio_ptr, segment[E].gpio_pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(segment[F].gpio_ptr, segment[F].gpio_pin, GPIO_PIN_SET);
			return;
		}
	case 1:
		{
			HAL_GPIO_WritePin(segment[B].gpio_ptr, segment[B].gpio_pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(segment[C].gpio_ptr, segment[C].gpio_pin, GPIO_PIN_SET);
			return;
		}
	case 2:
		{
			HAL_GPIO_WritePin(segment[A].gpio_ptr, segment[A].gpio_pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(segment[B].gpio_ptr, segment[B].gpio_pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(segment[D].gpio_ptr, segment[D].gpio_pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(segment[E].gpio_ptr, segment[E].gpio_pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(segment[G].gpio_ptr, segment[G].gpio_pin, GPIO_PIN_SET);
			return;
		}
	case 3:
		{
			HAL_GPIO_WritePin(segment[A].gpio_ptr, segment[A].gpio_pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(segment[B].gpio_ptr, segment[B].gpio_pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(segment[C].gpio_ptr, segment[C].gpio_pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(segment[D].gpio_ptr, segment[D].gpio_pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(segment[G].gpio_ptr, segment[G].gpio_pin, GPIO_PIN_SET);
			return;
		}
	case 4:
		{
			HAL_GPIO_WritePin(segment[B].gpio_ptr, segment[B].gpio_pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(segment[C].gpio_ptr, segment[C].gpio_pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(segment[F].gpio_ptr, segment[F].gpio_pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(segment[G].gpio_ptr, segment[G].gpio_pin, GPIO_PIN_SET);
			return;
		}
	case 5:
		{
			HAL_GPIO_WritePin(segment[A].gpio_ptr, segment[A].gpio_pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(segment[C].gpio_ptr, segment[C].gpio_pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(segment[D].gpio_ptr, segment[D].gpio_pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(segment[F].gpio_ptr, segment[F].gpio_pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(segment[G].gpio_ptr, segment[G].gpio_pin, GPIO_PIN_SET);
			return;
		}
	case 6:
		{
			HAL_GPIO_WritePin(segment[A].gpio_ptr, segment[A].gpio_pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(segment[C].gpio_ptr, segment[C].gpio_pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(segment[D].gpio_ptr, segment[D].gpio_pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(segment[E].gpio_ptr, segment[E].gpio_pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(segment[F].gpio_ptr, segment[F].gpio_pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(segment[G].gpio_ptr, segment[G].gpio_pin, GPIO_PIN_SET);
			return;
		}

	case 7:
		{
			HAL_GPIO_WritePin(segment[A].gpio_ptr, segment[A].gpio_pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(segment[B].gpio_ptr, segment[B].gpio_pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(segment[C].gpio_ptr, segment[C].gpio_pin, GPIO_PIN_SET);
			return;
		}
	case 8:
		{
			HAL_GPIO_WritePin(segment[A].gpio_ptr, segment[A].gpio_pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(segment[B].gpio_ptr, segment[B].gpio_pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(segment[C].gpio_ptr, segment[C].gpio_pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(segment[D].gpio_ptr, segment[D].gpio_pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(segment[E].gpio_ptr, segment[E].gpio_pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(segment[F].gpio_ptr, segment[F].gpio_pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(segment[G].gpio_ptr, segment[G].gpio_pin, GPIO_PIN_SET);
			return;
		}
	case 9:
		{
			HAL_GPIO_WritePin(segment[A].gpio_ptr, segment[A].gpio_pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(segment[B].gpio_ptr, segment[B].gpio_pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(segment[C].gpio_ptr, segment[C].gpio_pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(segment[D].gpio_ptr, segment[D].gpio_pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(segment[F].gpio_ptr, segment[F].gpio_pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(segment[G].gpio_ptr, segment[G].gpio_pin, GPIO_PIN_SET);
			return;
		}
	case 10:
		{
			HAL_GPIO_WritePin(segment[A].gpio_ptr, segment[A].gpio_pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(segment[B].gpio_ptr, segment[B].gpio_pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(segment[C].gpio_ptr, segment[C].gpio_pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(segment[E].gpio_ptr, segment[E].gpio_pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(segment[F].gpio_ptr, segment[F].gpio_pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(segment[G].gpio_ptr, segment[G].gpio_pin, GPIO_PIN_SET);
			return;
		}
	case 11:
		{
			HAL_GPIO_WritePin(segment[C].gpio_ptr, segment[C].gpio_pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(segment[D].gpio_ptr, segment[D].gpio_pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(segment[E].gpio_ptr, segment[E].gpio_pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(segment[F].gpio_ptr, segment[F].gpio_pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(segment[G].gpio_ptr, segment[G].gpio_pin, GPIO_PIN_SET);
			return;
		}
	case 12:
		{
			HAL_GPIO_WritePin(segment[A].gpio_ptr, segment[A].gpio_pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(segment[D].gpio_ptr, segment[D].gpio_pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(segment[E].gpio_ptr, segment[E].gpio_pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(segment[F].gpio_ptr, segment[F].gpio_pin, GPIO_PIN_SET);
			return;
		}
	case 13:
		{
			HAL_GPIO_WritePin(segment[B].gpio_ptr, segment[B].gpio_pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(segment[C].gpio_ptr, segment[C].gpio_pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(segment[D].gpio_ptr, segment[D].gpio_pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(segment[E].gpio_ptr, segment[E].gpio_pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(segment[G].gpio_ptr, segment[G].gpio_pin, GPIO_PIN_SET);
			return;
		}
	case 14:
		{
			HAL_GPIO_WritePin(segment[A].gpio_ptr, segment[A].gpio_pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(segment[D].gpio_ptr, segment[D].gpio_pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(segment[E].gpio_ptr, segment[E].gpio_pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(segment[F].gpio_ptr, segment[F].gpio_pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(segment[G].gpio_ptr, segment[G].gpio_pin, GPIO_PIN_SET);
			return;
		}
	case 15:
		{
			HAL_GPIO_WritePin(segment[A].gpio_ptr, segment[A].gpio_pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(segment[E].gpio_ptr, segment[E].gpio_pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(segment[F].gpio_ptr, segment[F].gpio_pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(segment[G].gpio_ptr, segment[G].gpio_pin, GPIO_PIN_SET);
			return;
		}
	}
}

void multiplex()
{
	if (pos == 0)
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET);
		write(MSD);
		pos = 1;	
	}
	else
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_RESET);
		write(LSD);
		pos = 0;
	}
}

GPIO_PinState invert(GPIO_PinState * state)
{
	if (*state == GPIO_PIN_RESET)
	{
		*state = GPIO_PIN_SET;
		return *state;
	}
	
	*state = GPIO_PIN_RESET;
	return *state;
}