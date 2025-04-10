#pragma once

//#define R_REGISTER 0x00
//#define W_REGISTER 0x20


#if defined(nrf24_package_implementer)
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

