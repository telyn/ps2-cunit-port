#include <CUnit/CUnit.h>
#include "snprintf_utils.h"

void test_snpf_pad_str_width_neg1_dst_plenty() {
	char dst[] = "old rectangular green French silver whittling knife";
	int dstc = 10;
	char *newPtr = snpf_pad_str(dst, ' ', -1, &dstc, strlen(dst));
	CU_ASSERT_STRING_EQUAL(dst, "old rectangular green French silver whittling knife");
	CU_ASSERT_STRING_EQUAL(dst, newPtr);
	CU_ASSERT_EQUAL(dstc, 10);
}

void test_snpf_pad_str_width_0_dst_plenty() {
	char dst[] = "old rectangular green French silver whittling knife";
	int dstc = 10;
	char *newPtr = snpf_pad_str(dst, ' ', 0, &dstc, strlen(dst));
	CU_ASSERT_STRING_EQUAL(dst, "old rectangular green French silver whittling knife");
	CU_ASSERT_STRING_EQUAL(dst, newPtr);
	CU_ASSERT_EQUAL(dstc, 10);
}

void test_snpf_pad_str_width_3_dst_plenty() {
	char dst[] = "old rectangular green French silver whittling knife";
	int dstc = 10;
	char *newPtr = snpf_pad_str(dst, ' ', 4, &dstc, strlen(dst));
	CU_ASSERT_STRING_EQUAL(dst, "    rectangular green French silver whittling knife");
	CU_ASSERT_STRING_EQUAL(newPtr, "rectangular green French silver whittling knife");
	CU_ASSERT_EQUAL(dstc, 14);
}

void test_snpf_pad_str_width_16_dst_plenty() {
	char dst[] = "old rectangular green French silver whittling knife";
	int dstc = 10;
	char *newPtr = snpf_pad_str(dst, ' ', 16, &dstc, strlen(dst));
	CU_ASSERT_STRING_EQUAL(dst, "                green French silver whittling knife");
	CU_ASSERT_STRING_EQUAL(newPtr, "green French silver whittling knife");
	CU_ASSERT_EQUAL(dstc, 26);
}

void test_snpf_str_width_16_dst_soon() {
	char dst[] = "knife";
	int dstc = 100;
	char *newPtr = snpf_pad_str(dst, ' ', 16, &dstc, strlen(dst));
	CU_ASSERT_STRING_EQUAL(dst, "     ");
	CU_ASSERT_STRING_EQUAL(newPtr, "");
	CU_ASSERT_EQUAL(dstc, 116);
}

void test_snpf_pad_str_width_16_dst_empty() {
	char dst[] = "green French silver whittling knife";
	int dstc = 100;
	char *newPtr = snpf_pad_str(dst, ' ', 16, &dstc, 0);
	CU_ASSERT_STRING_EQUAL(dst, "green French silver whittling knife");
	CU_ASSERT_STRING_EQUAL(newPtr, "green French silver whittling knife");
	CU_ASSERT_EQUAL(dstc, 116);
}

CU_pSuite snprintf_utils_suite() {
	CU_pSuite suite = CU_add_suite("snprintf_utils", NULL, NULL);

	// pad_str tests
	CU_ADD_TEST(suite, test_snpf_pad_str_width_neg1_dst_plenty);
	CU_ADD_TEST(suite, test_snpf_pad_str_width_0_dst_plenty);
	CU_ADD_TEST(suite, test_snpf_pad_str_width_3_dst_plenty);
	CU_ADD_TEST(suite, test_snpf_pad_str_width_16_dst_plenty);
	CU_ADD_TEST(suite, test_snpf_pad_str_width_16_dst_empty);

	// format_snpf_str tests
	// TODO: more here

	return suite;
}
