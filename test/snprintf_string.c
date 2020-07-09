#include "snprintf_string.h"
#include "snprintf.h"
#include <CUnit/CUnit.h>

void test_snprintf_string() {
	char *format = "hello %s world";
	char beautiful[] = "beautiful";
	char dst[22] = { '\0' };
	int res = _ps2_cunit_snprintf(dst, 22, format, beautiful);
	CU_ASSERT_STRING_EQUAL(dst, "hello beautiful world");
	CU_ASSERT_EQUAL(res, 21);
}

void test_snprintf_string_precision_exact() {
	char *format = "hello %.9s world";
	char beautiful[] = "beautiful";
	char dst[20] = { '\0' };
	int res = _ps2_cunit_snprintf(dst, 22, format, beautiful);
	CU_ASSERT_STRING_EQUAL(dst, "hello beautiful world");
	CU_ASSERT_EQUAL(res, 21);
}

void test_snprintf_string_precision_small() {
	char *format = "hello %.5s world";
	char beautiful[] = "beautiful";
	char dst[20] = { '\0' };
	int res = _ps2_cunit_snprintf(dst, 22, format, beautiful);
	CU_ASSERT_STRING_EQUAL(dst, "hello beaut world");
	CU_ASSERT_EQUAL(res, 17);
}

void test_snprintf_string_precision_large() {
	char *format = "hello %.12s world";
	char beautiful[] = "beautiful";
	char dst[20] = { '\0' };
	int res = _ps2_cunit_snprintf(dst, 22, format, beautiful);
	CU_ASSERT_STRING_EQUAL(dst, "hello beautiful world");
	CU_ASSERT_EQUAL(res, 21);
}

void test_snprintf_string_width_large_minus() {
	char *format = "hello %-19s world";
	char beautiful[] = "beautiful";
	char dst[32] = { '\0' };
	int res = _ps2_cunit_snprintf(dst, 32, format, beautiful);
	CU_ASSERT_STRING_EQUAL(dst, "hello beautiful           world");
	CU_ASSERT_EQUAL(res, 31);
}

void test_snprintf_string_smalln() {
	char *format = "hello %s world";
	char beautiful[] = "beautiful";
	char dst[22] = { '\0' };
	int res = _ps2_cunit_snprintf(dst, 15, format, beautiful);
	CU_ASSERT_STRING_EQUAL(dst, "hello beautiful");
	CU_ASSERT_EQUAL(res, 21);
}

void ps2snpftest_add_string_tests(CU_pSuite snprintf_suite) {
	CU_ADD_TEST(snprintf_suite, test_snprintf_string);
	CU_ADD_TEST(snprintf_suite, test_snprintf_string_smalln);
	CU_ADD_TEST(snprintf_suite, test_snprintf_string_precision_small);
	CU_ADD_TEST(snprintf_suite, test_snprintf_string_precision_exact);
	CU_ADD_TEST(snprintf_suite, test_snprintf_string_precision_large);
	CU_ADD_TEST(snprintf_suite, test_snprintf_string_width_large_minus);
}
