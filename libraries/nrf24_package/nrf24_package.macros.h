#pragma once

//#define R_REGISTER 0x00
//#define W_REGISTER 0x20


#if defined(nrf24_package_implementer)
	#define LIBNAME "nrf24_package"
	#define private static
    #define public 
	#define E7 0xE7
	#define C2 0xC2
	#define C3 0xC3
	#define C4 0xC4
	#define C5 0xC5
	#define C6 0xC6	
	#define BYTE_VALUE(V)    (*((uint8_t*)(&V)))
	#define BYTE_ADDRESS(V)  ((uint8_t*)(V))

	// Convert any register struct into a unisgned int
	#define REG_TO_INT(Register) (*(uint8_t*)(&(Register)))

	// Compute the result register from a Current value after applying New bit values as indicated by a Mask struct
	#define TWIDDLE(Current,New,Mask) (~(REG_TO_INT(Mask)) & REG_TO_INT(Current)) | (REG_TO_INT(Mask) & REG_TO_INT(New))
#endif

#define MAX_POWER  3   // 0dBm    
#define HIGH_POWER 2   // -6dBm
#define LOW_POWER  1   // -12dBm
#define MIN_POWER  0   // -18dBm

#define MIN_RATE 1 // 250 kbps
#define MED_RATE 0 // 1 Mbps
#define MAX_RATE 2 // 2 Mbps

#define NRF_SPI_NUCLEO_F446RE	\
{								\
	.pin_alt  = GPIO_AF5_SPI2,	\
	.cs_pin   = PB12,           \
	.sck_pin  = PB13,			\
	.miso_pin = PB14,			\
	.mosi_pin = PB15,			\
	.spi      = SPI2			\
}

#define NRF_AUX_NUCLEO_F446RE		\
{									\
	.timer			= TIM1,			\
	.nrf_int_type	= EXTI0_IRQn,   \
	.nrf_int_pin	= PA0,			\
	.nrf_ce_pin		= PA1,			\
}


#define FIVE(X) {0x##X, 0x##X, 0x##X, 0x##X, 0x##X}
