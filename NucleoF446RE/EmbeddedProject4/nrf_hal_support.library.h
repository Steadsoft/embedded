/*---------------------------------------------------------------------------------------*/
/*                          Library structure and conventions                            */
/*---------------------------------------------------------------------------------------*/
/* A library is implemented as a single source file. It exposes no public functions.     */
/* Instead it defines a public type that represents an 'interface' a structure that      */
/* itself contains a set of preinitialized function pointers to the static functions in  */
/* the library that we wish to export to the library consumer.                           */
/*                                                                                       */
/* The source file conatins three kinds of things 1. Function protyptyes, 2 Global names */
/* and 3. Implementations of the function.                                               */
/*                                                                                       */
/* The 'interface' is defined in the source file and accessd by consumers via 'extern'   */
/* declarations found in the 'externs' header.                                           */
/*                                                                                       */
/* A library consists of these distinct files:                                           */
/* 1. A macros header file - Contains all #defines.                                      */
/* 2. A typdefs header file - Contains all typdefs for structs and unions.               */
/* 3. A types header file - Conatins all struct and union bodies.                        */
/* 4. A externs header file - Contains declares of globals declared by library code.     */
/* 5. A single source file - Contains all implementation code and globals.               */
/*                                                                                       */
/* This strict uniformity applies to all libraries.                                      */
/*                                                                                       */
/* Consumers need only include a single header, the .library.h file, in order to use the */
/* library. All functions calls are - effectively - in a 'namespace' so are prefixed by  */
/* the library interface extern.                                                         */
/*                                                                                       */
/* This structue does not define how code is implemented, only how it is represented by  */
/* the various files.                                                                    */
/*---------------------------------------------------------------------------------------*/

#include "nrf_hal_support.macros.h"
#include "nrf_hal_support.typedefs.h"
#include "nrf_hal_support.types.h"

// The library implementation source file defines this because it also declares globals.
// Library consumers, refer to these globals using 'extern' and so include that header.

#if !defined(nrf_hal_support_implementer)
#include "nrf_hal_support.externs.h"
#endif
