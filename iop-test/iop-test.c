#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdint.h>
#include <stdbool.h>

#ifndef _IOP
int main(int argc, char **argv) {
#else
int _start(int argc, char **argv) {
#endif
  if (CUE_SUCCESS != CU_initialize_registry()) {
    return 2;
  }
  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();
  if (CU_get_error() != 0) {
    return 2;
  } else if (CU_get_number_of_tests_failed() > 0) {
    return 1;
  } else {
    return 0;
  }
}
