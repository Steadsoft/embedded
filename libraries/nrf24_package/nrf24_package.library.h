/*---------------------------------------------------------------------------------------*/
/*                          Library structure and conventions                            */
/*---------------------------------------------------------------------------------------*/
/* A library is implemented as a single source file. It exposes no public functions.     */
/* Instead it defines a public type that represents an 'interface' a structure that      */
/* itself contains a set of preinitialized function pointers to the static functions in  */
/* the library that we wish to export to the library consumer.                           */
/*	                                                                                     */
/* The interface structure is an initialized global declaration, exists once only.       */
/*                                                                                       */
/* The source file conatins three kinds of things 1. Function protyptyes, 2 Global names */
/* and 3. Implementations of the function.                                               */
/*                                                                                       */
/* The 'interface' is defined in the source file and accessed by consumers via 'extern'  */
/* declarations found in the 'externs' header.                                           */
/*                                                                                       */
/* A library consists of these distinct files:                                           */
/* 1. A docs text file - Contains library specific helpful documentation.                */
/* 2. A macros header file - Contains all #defines.                                      */
/* 3. A typdefs header file - Contains all typdefs for structs and unions.               */
/* 4. A types header file - Conatins all struct and union bodies.                        */
/* 5. A externs header file - Contains declares of globals declared by library code.     */
/* 6. A single source file - Contains all implementation code and globals.               */
/*                                                                                       */
/* This strict uniformity applies to all libraries.                                      */
/*                                                                                       */
/* Consumers need only include a single header, the .library.h file, in order to use the */
/* library. All functions calls are - effectively - in a 'namespace' so are prefixed by  */
/* the library interface extern structure name.                                          */
/*                                                                                       */
/* This structue does not define how code is implemented, only how it is represented by  */
/* the various files.                                                                    */
/*                                                                                       */
/* Libraries can be layered but a lower layer library cannot refer to a higher one.      */
/*                                                                                       */
/* Only the library implementation source or consumer source files should include any    */
/* non-package headers like HAL and STM32 headers and so on, NONE of the package header  */
/* files should ever include scch headers.                                               */
/*---------------------------------------------------------------------------------------*/

// These heaader files must always be ordered this way.

#include <nrf24_package.docs.h>
#include <nrf24_package.macros.h>
#include <nrf24_package.typedefs.h>
#include <nrf24_package.types.h>

// The library implementation source file defines this macro because it also declares globals.
// Library consumers, refer to these globals using 'extern' and so include the 'extern' header.
// Only the implementation source file defines the 'implementer' macro name.

#if !defined(nrf24_package_implementer)
	#include <nrf24_package.externs.h>
#else
	void __attribute__((weak)) ApplicationFaultHandler(char * LibName, char * LibMessage);
	void __attribute__((weak, naked)) ApplicationFaultHandler(char * LibName, char * LibMessage)
	{
		__asm("bkpt 255");
		__asm("bx lr");
	}
#endif