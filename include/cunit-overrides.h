#ifndef CUNIT_OVERRIDES_H
#define CUNIT_OVERRIDES_H

#include "snprintf.h"
#ifdef _IOP
#include <stdio.h>
#include <alloc.h>
#include <thbase.h>
#include "clock.h"

#define snprintf _ps2_cunit_snprintf
#define stderr 1
#define stdout 1
#define stdin 0
#define fprintf fdprintf
#define FILE int
#define _IONBF 0

#define setvbuf _ps2_setvbuf

// TODO: extract into .c file
void _ps2_setvbuf(int fd, char *buf, int mode, int whatever);
void _ps2_cunit_exit(int code);

#define exit _ps2_cunit_exit

#endif

#endif
