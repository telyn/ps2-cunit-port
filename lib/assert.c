#include <stdio.h>
#include "assert.h"

void _ps2_cunit_assert(char *condition, int value) {
	if (value == 0) {
		printf("ASSERT(%s) FAILED\n", condition);
	}
}
