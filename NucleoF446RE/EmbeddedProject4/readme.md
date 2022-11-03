This project is primarily concerned with the nRF24L01 device, but is also where the library idea was thrashed out. The code is implemented as a set of "libraries" and the conventions used to represent a library has been crafted to make things as easy as possible for users of the library, so a word about libraries as I used them here.

## Why Libraries?
When I started exploring the world of microcontrollers I was somewhat overwhelmed by the nature of the examples and code that I saw on blogs and in public repositories. The code as - in many but not all cases - was a mish mash of source code, header files, macro defintions and so on. It was sometimes unclear how to actually *use* a "library" because the conventions, assumptions and expectations of the library writer varied wildly.

I had no idea how to structure my own projects but as an experienced software engineer (aside from microcontrollers) felt that this was an extremely important aspect of development, particularly for things inherently rich in detail like microcontrollers and hardware. So I stopped working at the hardware level for a time and addressed the problem of exactly how to go about writing code that was easy to reuse.

## Libraries
A library is something intended for *easy reuse* at the source level. The structure of a library insofar as files are concerned is as follows, let the library be named `stm32_utilities` for example:

- 
- A single implemenetation file, the source `stm32_utilities.c` file.
- A single macro header file `stm32_utilities.macros.h`
- A single typedefs header file `stm32_utilities.typedefs.h`
- A single types header file `stm32_utilities.types.h`
- A single externs header file `stm32_utilities.externs.h`
- A single library heade file `stm32_utilities.library.h`

This structure can support any desired implementation or functionality. By adopting the same pattern for all libraries we can build a complete system from simply libraries, that is all the code will follow the same structural pattern in terms of files. The system imposes no constraints on *how* one writes the code, what techniques are used etc, it is only imposed on the way we *represent the library* in terms of source files.







