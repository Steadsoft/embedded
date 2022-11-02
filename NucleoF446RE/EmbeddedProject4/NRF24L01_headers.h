#include <NRF24L01_macros.h>
#include <NRF24L01_typedefs.h>
#include <NRF24L01_structs.h>

// This defintion is expected to appear in source code that IMPLEMENTS the library. In this case it pulls
// in static function declarations and global name declarations. CONSUMING code never defines the library
// name and so will never see static functions and will use 'extern' to declare a library's global names.

#if defined(NRF24L01)
#include <NRF24L01_statics.h>
#include <NRF24L01_globals.h>
#else
#include <NRF24L01_externs.h>
#endif

#include <NRF24L01_functions.h>
