#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
CU_pSuite snprintf_suite();
CU_pSuite snprintf_utils_suite();
CU_pSuite ps2cunit_toa_suite();
// CU_pSuite snprintf_suite();

int main(int argc, char **argv) {
	CU_initialize_registry();
	//CU_basic_set_mode(CU_BRM_VERBOSE);

	snprintf_suite();
	snprintf_utils_suite();
	ps2cunit_toa_suite();

	CU_basic_run_tests();
	CU_cleanup_registry();
	return 0;
}
