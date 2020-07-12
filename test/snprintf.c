#include <CUnit/CUnit.h>
#include "snprintf.h"
#include "snprintf_string.h"

void test_snprintf_plain() {
	char format[] = "hello world";
	char dst[22] = { '\0' };
	int res = _ps2_cunit_snprintf(dst, 22, format);
	CU_ASSERT_STRING_EQUAL(dst, "hello world");
	CU_ASSERT_EQUAL(res, 11);
}

void test_snprintf_plain_smalln() {
	char format[] = "hello world";
	char dst[22] = { '\0' };
	int res = _ps2_cunit_snprintf(dst, 6, format);
	CU_ASSERT_STRING_EQUAL(dst, "hello ");
	CU_ASSERT_EQUAL(res, 11);
}


void test_snprintf_plain_pct_literal() {
	char format[] = "hello world %%";
	char dst[22] = { '\0' };
	int res = _ps2_cunit_snprintf(dst, 22, format);
	CU_ASSERT_STRING_EQUAL(dst, "hello world %");
	CU_ASSERT_EQUAL(res, 13);
}

void test_snprintf_int() {
	char format[] = "hello %d world";
	char dst[22] = { '\0' };
	int res = _ps2_cunit_snprintf(dst, 22, format, 1530008);
	CU_ASSERT_STRING_EQUAL(dst, "hello 1530008 world");
	CU_ASSERT_EQUAL(res, 19);
}

void test_snprintf_int_zero() {
	char format[] = "hello %d world";
	char dst[22] = { '\0' };
	int res = _ps2_cunit_snprintf(dst, 22, format, 0);
	CU_ASSERT_STRING_EQUAL(dst, "hello 0 world");
	CU_ASSERT_EQUAL(res, 13);
}

void test_snprintf_int_zero_precision_zero() {
	char format[] = "hello %.0d world";
	char dst[22] = { '\0' };
	int res = _ps2_cunit_snprintf(dst, 22, format, 0);
	printf("act :'%s'\n", dst);
	CU_ASSERT_STRING_EQUAL(dst, "hello  world");
	CU_ASSERT_EQUAL(res, 12);
}

void test_snprintf_int_negative() {
	char format[] = "hello world %%";
	char dst[22] = { '\0' };
	int res = _ps2_cunit_snprintf(dst, 22, format);
	CU_ASSERT_STRING_EQUAL(dst, "hello world %");
	CU_ASSERT_EQUAL(res, 13);
}

void test_snprintf_int_smalln() {
	CU_ASSERT(0);
}

void test_snprintf_uint() {
	CU_ASSERT(0);
}

void test_snprintf_uint_smalln() {
	CU_ASSERT(0);
}

void test_snprintf_float() {
	char *format = "lovely %f float";
	format = "lovely %4.2f float";
	format = "lovely %8.3f float";
	CU_ASSERT(0);
}

void test_snprintf_uint_float() {
	CU_ASSERT(0);
}

CU_pSuite snprintf_suite() {
	CU_pSuite snprintf_suite = CU_add_suite("snprintf", NULL, NULL);
	CU_ADD_TEST(snprintf_suite, test_snprintf_plain);
	CU_ADD_TEST(snprintf_suite, test_snprintf_plain_smalln);
	CU_ADD_TEST(snprintf_suite, test_snprintf_plain_pct_literal);
	ps2snpftest_add_string_tests(snprintf_suite);
	CU_ADD_TEST(snprintf_suite, test_snprintf_int);
	CU_ADD_TEST(snprintf_suite, test_snprintf_int_negative);
	CU_ADD_TEST(snprintf_suite, test_snprintf_int_zero);
	CU_ADD_TEST(snprintf_suite, test_snprintf_int_zero_precision_zero);
	CU_ADD_TEST(snprintf_suite, test_snprintf_int_smalln);
	CU_ADD_TEST(snprintf_suite, test_snprintf_uint);
	CU_ADD_TEST(snprintf_suite, test_snprintf_uint_smalln);
	return snprintf_suite;
}
