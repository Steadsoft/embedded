#include <nrf24_package.macros.h>
#include <nrf24_package.typedefs.h>
#include <nrf24_package.structs.h>

// This defintion is expected to appear in source code that IMPLEMENTS the library. In this case it pulls
// in static function declarations and global name declarations. CONSUMING code never defines the library
// name and so will never see static functions and will use 'extern' to declare a library's global names.

#if defined(nrf24_package)
#include <nrf24_package.statics.h>
#include <nrf24_package.globals.h>
#else
#include <nrf24_package.externs.h>
#endif

#include <nrf24_package.functions.h>
