#ifdef _IOP
#include <alloc.h>
#include <stdio.h>
#include <sysclib.h>
#include <thbase.h>

alloc_IMPORTS_start
I_malloc
I_free
alloc_IMPORTS_end

stdio_IMPORTS_start
I_printf
I_fdprintf
stdio_IMPORTS_end

sysclib_IMPORTS_start
I_longjmp
I_look_ctype_table
I_memcpy
I_memset
I_setjmp
I_strcmp
I_strcpy
I_strlen
I_strncmp
I_strncpy
I_toupper
sysclib_IMPORTS_end

thbase_IMPORTS_start
I_GetSystemTime
I_ExitThread
thbase_IMPORTS_end
#endif
