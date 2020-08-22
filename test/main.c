#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

// beats writing a header file..
CU_pSuite snprintf_suite();
CU_pSuite snprintf_utils_suite();
CU_pSuite ps2cunit_toa_suite();
// CU_pSuite snprintf_suite();


#ifdef _IOP
int _start(int argc, char **argv) {
#else
int main(int argc, char **argv) {
#endif
	CU_initialize_registry();
	//CU_basic_set_mode(CU_BRM_VERBOSE);

	snprintf_suite();
	snprintf_utils_suite();
	ps2cunit_toa_suite();

	CU_ErrorCode err = CU_basic_run_tests();
	if (err != CUE_SUCCESS) {
		printf("Error running the tests: %s", CU_get_error_msg);
		return 2;
	}

	int failures = CU_get_number_of_tests_failed();
	CU_cleanup_registry();

	if (failures > 0) {
		return 1;
	}
}
