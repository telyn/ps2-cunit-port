#ifndef ASSERT_H
#define ASSERT_H
#include <stdio.h>

void _ps2_cunit_assert(char *condition, int value);

#define assert(x) (_ps2_cunit_assert(#x, x))
#endif
