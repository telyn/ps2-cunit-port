#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

#ifndef _IOP
int main(int argc, char **argv) {
#else
int _start(int argc, char **argv) {
#endif
  CU_initialize_registry();
  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();
}
