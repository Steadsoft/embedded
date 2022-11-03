#include <nrf24_package.macros.h>
#include <nrf24_package.typedefs.h>
#include <nrf24_package.structs.h>

// The library implementation source file defines this because it also declares globals.
// Library using, consumers, refer to these globals using 'extern' and so use that header.

#if !defined(nrf24_package_implementer)
#include <nrf24_package.externs.h>
#endif