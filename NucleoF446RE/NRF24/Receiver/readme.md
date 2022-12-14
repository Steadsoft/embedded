This project is primarily concerned with the nRF24L01 device, but is also where the library idea was thrashed out. The code is implemented as a set of "libraries" and the conventions used to represent a library has been crafted to make things as easy as possible for users of the library, so a word about libraries as I used them here.

## Why Libraries?
When I started exploring the world of microcontrollers I was somewhat overwhelmed by the nature of the examples and code that I saw on blogs and in public repositories. The code - in many but not all cases - was a mish mash of source code, header files, macro defintions and so on. It was sometimes unclear how to actually *use* a "library" because the conventions, assumptions and expectations of the library writer varied wildly.

I had no idea how to structure my own projects but as an experienced software engineer (aside from microcontrollers) felt that this was an extremely important aspect of development, particularly for things inherently rich in detail like microcontrollers and hardware. So I stopped working at the hardware level for a time and addressed the problem of exactly how to go about writing code that was easy to reuse.

## Libraries
A library is something intended for *easy reuse* at the source level. The structure of a library insofar as files are concerned is as follows, let the library be named `stm32_utilities` for example:
 
- A single implemenetation file, the source `stm32_utilities.c` file.
- A single macro header file `stm32_utilities.macros.h`
- A single typedefs header file `stm32_utilities.typedefs.h`
- A single types header file `stm32_utilities.types.h`
- A single externs header file `stm32_utilities.externs.h`
- A single library heade file `stm32_utilities.library.h`
- A single doc header files `stm32_utilities.docs.h`

This structure can support any desired implementation or functionality. By adopting the same pattern for all libraries we can build a complete system from simply libraries, that is, all the code will follow the same structural pattern in terms of files. The system imposes no constraints on *how* one writes the code, what techniques are used etc, it is only imposed on the way we *represent the library* in terms of source files.

## Library Features
A library implemenetd with this pattern is easy to reuse. The consumer simply include a single *library* header file like `stm32_utilities.library.h`. So long as all the files are present in the project and can be built, this is *all a consumer needs to include*.

## Library Name
This is whatever you want it to be, it is repeated in the names of the header files and also appears as a prefix in several important place. In the `types` header we always have a type `<library_name>_interface` a struct. This struct defines a set of function pointers that represent every function we want to expose to the library consumer. 

e.g.

```c
struct nrf_hal_support_interface
{
	void (*init_spi)(SPI_HandleTypeDef * spi_ptr);
	void (*init_control_pins)();
	void (*spi_ce_lo)(void *);
	void (*spi_ce_hi)(void *);
	void (*spi_cs_lo)(void *);
	void (*spi_cs_hi)(void *);
	void (*exchange_bytes)(void *, uint8_t[], uint8_t[], uint8_t);
	void (*read_bytes)(void *, uint8_t bytes_in_ptr[], uint8_t count);
	void (*write_bytes)(void *, uint8_t bytes_out_ptr[], uint8_t count);
	void(*init_device)(SPI_HandleTypeDef * spi_ptr, NrfSpiDevice_ptr device_ptr, NrfIoDescriptor_ptr descriptor_ptr);
	void(*flash_led_forever)(uint32_t interval);

};
```

In the typedefs header we define a typename for this struct type, e.g.

```c
typedef const struct nrf24_hal_support_interface nrf24_hal_support_struct, * nrf_hal_support_ptr;
```

In the implementation source file all functions are static, there are no exported functions. We have three distinct things in this file:

1. Forward prototype declarations for all implemented functions.
2. A global declaration of a single initialized instance of the interface type.
3. Implementations of the library functions.

Here's an example of how the global interface is defined in the source file:

```c
nrf24_hal_support_struct nrf24_hal_support =
{
	.init_spi = init_spi,
	.init_control_pins = init_control_pins,
	.spi_ce_lo = spi_ce_lo,
	.spi_ce_hi = spi_ce_hi,
	.spi_cs_lo = spi_cs_lo,
	.spi_cs_hi = spi_cs_hi,
	.exchange_bytes = exchange_bytes,
	.read_bytes = read_bytes,
	.write_bytes = write_bytes,
	.init_device = init_device,
	.flash_led_forever = flash_led_forever
};
```

This global name is also define in the `externs` file, this file's content is only seen by consumers of the library.

```c
extern nrf24_hal_support_struct nrf24_hal_support;
```

The library consumer can now regard the library as being a namespace, and refer to function by a qualified a name,a great help in C:

```c
	nrf24_hal_support.init_spi(&spi);
```
The `.library.` header file consolidates the inlcuding of all the other needed files. This same file is included in the implementation source file and the consumer's source file, here it is:

```c
#include "nrf_hal_support.macros.h"
#include "nrf_hal_support.typedefs.h"
#include "nrf_hal_support.types.h"

// The library implementation source file defines this because it also declares globals.
// Library consumers, refer to these globals using 'extern' and so include that header.

#if !defined(nrf_hal_support_implementer)
#include "nrf_hal_support.externs.h"
#endif
```

The macro `nrf_hal_support_implementer` name is a private defintion, only defined within the implementation source file, this is how consuming code is able to define the externs exposed by the library.

The global name that represents the interface is named with the library name, this makes it easy to infer the name of the global interface simply by knowing the name of a library. These are conventions and must be maintained by developers but the benefits are significant in terms of uniformity, consisteny and readability.

Consumer code thus looks like these exampples:

```c
	nrf24_package.GetRegister.RF_SETUP(device_ptr, &rf_setup, &status);
```

```c
	nrf24_hal_support.init_spi(&spi);
```

## Benefits of the Library pattern

The library pattern is nothing more than a disciplined organizational practice, by enabling functional blocks to be represented as distinct libraries, it aids in the decomposition of the larger problem that one's application must implement.

Because every library follows the same regular structure, there's no uncertainty about where to find a type or a function defintion.

Libraries are not solely intended for exporting code for reuse across applications, it serves well for that need but is just as helpful as a way of breaking up a problem into smaller pieces, you might create libraries that are only ever used by one application.

Libraries provide a well defined way for library code to define and use "private" types, typedefs and macros; these are totally unseen by consuming code and so name collisions are far less likely than in a less undisciplined code structure.

A library is not an attempt at providing OO features, the concepts used are standard C concepts using stanadard C scoping and header file policies, yes the "interface" seems to sound OO but is not really, it is just a way to provide a namespace for functions and aids in code readability as well as exoploiting an IDEs itellisense features.

A library strives to be a pattern that can serve any need. All code could be structured this way in principle and so gives the C developer a helpful abstraction for code decomposition and reuse than the language alone provides.

## Example

The following is helpful as a summary of the library concept, this is a typical small project created in Microsoft's Visual Studio using the 3rd party tool Visual GDB:

![image](https://user-images.githubusercontent.com/12262952/200022652-3bdd8073-c3d7-4c7e-a03f-9556f69ac779.png)

There are two libraries here `nrf24_hal_support` and `nrf24_package` as well as a small application that uses them `nrf_hal_project`. You can see the various header files and their names as well as the code implementation files. 

The application project source file contains only these headers:

```c
#include <stm32f4xx_hal.h>
#include <nrf24_package.library.h>
#include <nrf24_hal_support.library.h>
```

The application code interacts with the code in the libraries strictly through the interfaces defined by the library `.types.` headers:


```c
struct nrf24_hal_support_interface
{
	void (*init_spi)(SPI_HandleTypeDef * spi_ptr);
	void (*init_control_pins)();
	void (*spi_ce_lo)(void *);
	void (*spi_ce_hi)(void *);
	void (*spi_cs_lo)(void *);
	void (*spi_cs_hi)(void *);
	void (*exchange_bytes)(void *, uint8_t[], uint8_t[], uint8_t);
	void (*read_bytes)(void *, uint8_t bytes_in_ptr[], uint8_t count);
	void (*write_bytes)(void *, uint8_t bytes_out_ptr[], uint8_t count);
	void(*init_device)(SPI_HandleTypeDef * spi_ptr, NrfSpiDevice_ptr device_ptr, NrfIoDescriptor_ptr descriptor_ptr);
	void(*flash_led_forever)(uint32_t interval);
};
```
and
```c
struct nrf24_package_interface
{
	NrfIoCallbacks_ptr ptr;
	struct nrf_set_register_interface GetRegister;
	struct nrf_get_register_interface SetRegister;
};
```
The last interface is an example of a hieracrchical interface, `GetRegister` is itself an interface exposing a set of functions:

```c
struct nrf_get_register_interface
{
	void(* CONFIG)(NrfSpiDevice_ptr device_ptr, NrfReg_CONFIG Value, NrfReg_STATUS_ptr NrfStatus);
	void(* EN_AA)(NrfSpiDevice_ptr device_ptr, NrfReg_EN_AA Value, NrfReg_STATUS_ptr NrfStatus);
	void(* EN_RX_ADDR)(NrfSpiDevice_ptr device_ptr, NrfReg_EN_RXADDR Value, NrfReg_STATUS_ptr NrfStatus);
	void(* SETUP_AW)(NrfSpiDevice_ptr device_ptr, NrfReg_SETUP_AW Value, NrfReg_STATUS_ptr NrfStatus);
	void(* SETUP_RETR)(NrfSpiDevice_ptr device_ptr, NrfReg_SETUP_RETR Value, NrfReg_STATUS_ptr NrfStatus);
	void(* STATUS)(NrfSpiDevice_ptr device_ptr, NrfReg_STATUS Value, NrfReg_STATUS_ptr NrfStatus);
	void(* OBSERVE_TX)(NrfSpiDevice_ptr device_ptr, NrfReg_OBSERVE_TX Value, NrfReg_STATUS_ptr NrfStatus);
	void(* CD)(NrfSpiDevice_ptr device_ptr, NrfReg_CD Value, NrfReg_STATUS_ptr NrfStatus);
	void(* RX_ADDR)(NrfSpiDevice_ptr device_ptr, NrfReg_RX_ADDR Value, uint8_t Pipe, NrfReg_STATUS_ptr NrfStatus);
	void(* RX_PW)(NrfSpiDevice_ptr device_ptr, NrfReg_RX_PW Value, uint8_t Pipe, NrfReg_STATUS_ptr NrfStatus);
	void(* DYNPD)(NrfSpiDevice_ptr device_ptr, NrfReg_DYNPD Value, NrfReg_STATUS_ptr NrfStatus);
	void(* RF_CH)(NrfSpiDevice_ptr device_ptr, NrfReg_RF_CH Value, NrfReg_STATUS_ptr NrfStatus);
	void(* RF_SETUP)(NrfSpiDevice_ptr device_ptr, NrfReg_RF_SETUP Value, NrfReg_STATUS_ptr NrfStatus);
	void(* FEATURE)(NrfSpiDevice_ptr device_ptr, NrfReg_FEATURE Value, NrfReg_STATUS_ptr NrfStatus);
};
```

This means we can use the same name for two functions:

```c
	nrf24_package.GetRegister.RX_ADDR(device_ptr, &rx_address, 3, &status);
	nrf24_package.SeRegister.RX_ADDR(device_ptr, rx_address, 3, &status);
```

There are in fact two methods named `RX_ADDR` but there's no conflict because they are in different namespaces.










