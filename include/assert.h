#ifndef ASSERT_H
#define ASSERT_H
#include <stdio.h>

void _ps2_cunit_assert(char *condition, int value) {
	if (value == 0) {
		printf("ASSERT(%s) FAILED\n", condition);
	}
}

#define assert(x) (_ps2_cunit_assert(#x, x))
#endif
