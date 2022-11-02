#include "nrf_hal_support.macros.h"
#include "nrf_hal_support.typedefs.h"
#include "nrf_hal_support.structs.h"

// This defintion is expected to appear in source code that IMPLEMENTS the library. In this case it pulls
// in static function declarations and global name declarations. CONSUMING code never defines the library
// name and so will never see static functions and will use 'extern' to declare a library's global names.

#if defined(nrf_hal_support)
#include "nrf_hal_support.statics.h"
#include "nrf_hal_support.globals.h"
#else
#include "nrf_hal_support.externs.h"
#endif

#include "nrf_hal_support.functions.h"
