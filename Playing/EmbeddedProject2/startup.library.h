#include <startup.docs.h>
#include <startup.macros.h>
#include <startup.typedefs.h>
#include <startup.types.h>

// The library implementation source file defines this because it also declares globals.
// Library consumers, refer to these globals using 'extern' and so include that header.

#if !defined(startup_implementer)
#include <startup.externs.h>
#endif
