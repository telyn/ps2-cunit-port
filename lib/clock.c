#include "clock.h"
#ifdef _IOP
#include <thbase.h>

clock_t clock() {
  iop_sys_clock_t clk;
  GetSystemTime(&clk);

  clock_t ret = (clock_t)clk.lo;
  clock_t hi = (clock_t)clk.hi;
  ret |= hi << 32;

  return ret;
}
#endif
