#pragma once

//#define R_REGISTER 0x00
//#define W_REGISTER 0x20


#define BYTE_VALUE(V)    (*((uint8_t*)(&V)))
#define BYTE_ADDRESS(V)  ((uint8_t*)(V))

