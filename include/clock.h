#ifndef _CLOCK_H
#define _CLOCK_H

#ifdef _IOP
#include <sys/time.h>
clock_t clock();
#endif

#endif
