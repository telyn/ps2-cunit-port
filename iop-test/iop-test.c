#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdint.h>
#include <stdbool.h>
uint8_t chr;
bool b = false;
long int i = 100;

#ifndef _IOP
int main(int argc, char **argv) {
#else
int _start(int argc, char **argv) {
#endif
  if (i == 100) {
    printf("jeff");
  }
  CU_initialize_registry();
  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();
}
