#include "cunit-overrides.h"
#include <stdio.h>
#include <thbase.h>

void _ps2_cunit_exit(int code) {
	printf("Exiting with code %d\n", code);
	ExitThread();
}
