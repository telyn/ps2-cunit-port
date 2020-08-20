#include "cunit-overrides.h"
#include <stdio.h>

#ifdef _IOP
  #include <thbase.h>
#else
  void ExitThread() {
  }
#endif

void _ps2_cunit_exit(int code) {
	printf("Exiting with code %d\n", code);
	ExitThread();
}
