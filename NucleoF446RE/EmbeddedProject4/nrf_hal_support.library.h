#include "nrf_hal_support.macros.h"
#include "nrf_hal_support.typedefs.h"
#include "nrf_hal_support.structs.h"

// The library implementation source file defines this because it also declares globals.
// Library using, consumers, refer to these globals using 'extern' and so use that header.

#if !defined(nrf_hal_support)
#include "nrf_hal_support.externs.h"
#endif

#include "nrf_hal_support.functions.h"
