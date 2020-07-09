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

void test_format_snpf_str_default_fmt_plenty() {
	struct snpf_format fmt;
	reset_snpf_format(&fmt);
	char dst[] = "**********";
	char *src = "test";
	int dstlen = strlen(dst);

	int res = format_snpf_str(dst, dstlen, &fmt, src);
	CU_ASSERT_STRING_EQUAL(dst, "test******");
	CU_ASSERT_STRING_EQUAL(src, "test");
	CU_ASSERT_EQUAL(res, 4);
}

void test_format_snpf_str_default_fmt_soon() {
	struct snpf_format fmt;
	reset_snpf_format(&fmt);
	char dst[] = "***";
	char *src = "test";
	int dstlen = strlen(dst);

	int res = format_snpf_str(dst, dstlen, &fmt, src);
	CU_ASSERT_STRING_EQUAL(dst, "tes");
	CU_ASSERT_STRING_EQUAL(src, "test");
	CU_ASSERT_EQUAL(res, 4);
}

void test_format_snpf_str_default_fmt_empty() {
	struct snpf_format fmt;
	reset_snpf_format(&fmt);
	char dst[] = "***";
	char *src = "test";
	int dstlen = 0;

	int res = format_snpf_str(dst, dstlen, &fmt, src);
	CU_ASSERT_STRING_EQUAL(dst, "***");
	CU_ASSERT_STRING_EQUAL(src, "test");
	CU_ASSERT_EQUAL(res, 4);
}

void test_format_snpf_str_width_0_plenty() {
	struct snpf_format fmt;
	reset_snpf_format(&fmt);
	fmt.width = 0;
	char dst[] = "**********";
	char *src = "test";
	int dstlen = 10;

	int res = format_snpf_str(dst, dstlen, &fmt, src);
	CU_ASSERT_STRING_EQUAL(dst, "test******");
	CU_ASSERT_STRING_EQUAL(src, "test");
	CU_ASSERT_EQUAL(res, 4);
}

void test_format_snpf_str_width_0_soon() {
	struct snpf_format fmt;
	reset_snpf_format(&fmt);
	fmt.width = 0;
	char dst[] = "**********";
	char *src = "test";
	int dstlen = 3;

	int res = format_snpf_str(dst, dstlen, &fmt, src);
	CU_ASSERT_STRING_EQUAL(dst, "tes*******");
	CU_ASSERT_STRING_EQUAL(src, "test");
	CU_ASSERT_EQUAL(res, 4);
}

void test_format_snpf_str_width_0_empty() {
	struct snpf_format fmt;
	reset_snpf_format(&fmt);
	fmt.width = 0;
	char dst[] = "**********";
	char *src = "test";
	int dstlen = 0;

	int res = format_snpf_str(dst, dstlen, &fmt, src);
	CU_ASSERT_STRING_EQUAL(dst, "**********");
	CU_ASSERT_STRING_EQUAL(src, "test");
	CU_ASSERT_EQUAL(res, 4);
}

void test_format_snpf_str_width_10_plenty() {
	struct snpf_format fmt;
	reset_snpf_format(&fmt);
	fmt.width = 10;
	char dst[] = "****************";
	char *src = "test";
	int dstlen = 10;

	int res = format_snpf_str(dst, dstlen, &fmt, src);
	CU_ASSERT_STRING_EQUAL(dst, "      test******");
	CU_ASSERT_STRING_EQUAL(src, "test");
	CU_ASSERT_EQUAL(res, 10);
}

void test_format_snpf_str_width_10_soon() {
	struct snpf_format fmt;
	reset_snpf_format(&fmt);
	fmt.width = 10;
	char dst[] = "****************";
	char *src = "test";
	int dstlen = 6;

	int res = format_snpf_str(dst, dstlen, &fmt, src);
	CU_ASSERT_STRING_EQUAL(dst, "      **********");
	CU_ASSERT_STRING_EQUAL(src, "test");
	CU_ASSERT_EQUAL(res, 10);
}

void test_format_snpf_str_width_10_empty() {
	struct snpf_format fmt;
	reset_snpf_format(&fmt);
	fmt.width = 10;
	char dst[] = "****************";
	char *src = "test";
	int dstlen = 0;

	int res = format_snpf_str(dst, dstlen, &fmt, src);
	CU_ASSERT_STRING_EQUAL(dst, "****************");
	CU_ASSERT_STRING_EQUAL(src, "test");
	CU_ASSERT_EQUAL(res, 10);
}

void test_format_snpf_str_width_10_left_plenty() {
	struct snpf_format fmt;
	reset_snpf_format(&fmt);
	fmt.width = 10;
	fmt.align = PS2SNPF_LEFT;
	char dst[] = "****************";
	char *src = "test";
	int dstlen = 10;

	int res = format_snpf_str(dst, dstlen, &fmt, src);
	CU_ASSERT_STRING_EQUAL(dst, "test      ******");
	CU_ASSERT_STRING_EQUAL(src, "test");
	CU_ASSERT_EQUAL(res, 10);
}

void test_format_snpf_str_width_10_left_soon() {
	struct snpf_format fmt;
	reset_snpf_format(&fmt);
	fmt.width = 10;
	fmt.align = PS2SNPF_LEFT;
	char dst[] = "****************";
	char *src = "test";
	int dstlen = 6;

	int res = format_snpf_str(dst, dstlen, &fmt, src);
	CU_ASSERT_STRING_EQUAL(dst, "test  **********");
	CU_ASSERT_STRING_EQUAL(src, "test");
	CU_ASSERT_EQUAL(res, 10);
}

void test_format_snpf_str_width_10_left_empty() {
	struct snpf_format fmt;
	reset_snpf_format(&fmt);
	fmt.width = 10;
	fmt.align = PS2SNPF_LEFT;
	char dst[] = "****************";
	char *src = "test";
	int dstlen = 0;

	int res = format_snpf_str(dst, dstlen, &fmt, src);
	CU_ASSERT_STRING_EQUAL(dst, "****************");
	CU_ASSERT_STRING_EQUAL(src, "test");
	CU_ASSERT_EQUAL(res, 10);
}

void test_format_snpf_str_precision_3_plenty() {
	struct snpf_format fmt;
	reset_snpf_format(&fmt);
	fmt.precision = 3;
	char dst[] = "**********";
	char *src = "test";
	int dstlen = 10;

	int res = format_snpf_str(dst, dstlen, &fmt, src);
	CU_ASSERT_STRING_EQUAL(dst, "tes*******");
	CU_ASSERT_STRING_EQUAL(src, "test");
	CU_ASSERT_EQUAL(res, 3);
}

void test_format_snpf_str_precision_3_soon() {
	struct snpf_format fmt;
	reset_snpf_format(&fmt);
	fmt.precision = 3;
	char dst[] = "**********";
	char *src = "test";
	int dstlen = 2;

	int res = format_snpf_str(dst, dstlen, &fmt, src);
	CU_ASSERT_STRING_EQUAL(dst, "te********");
	CU_ASSERT_STRING_EQUAL(src, "test");
	CU_ASSERT_EQUAL(res, 3);
}

void test_format_snpf_str_precision_3_empty() {
	struct snpf_format fmt;
	reset_snpf_format(&fmt);
	fmt.precision = 3;
	char dst[] = "**********";
	char *src = "test";
	int dstlen = 0;

	int res = format_snpf_str(dst, dstlen, &fmt, src);
	CU_ASSERT_STRING_EQUAL(dst, "**********");
	CU_ASSERT_STRING_EQUAL(src, "test");
	CU_ASSERT_EQUAL(res, 3);
}

void test_format_snpf_str_precision_3_width_7_plenty() {
	struct snpf_format fmt;
	reset_snpf_format(&fmt);
	fmt.width = 7;
	fmt.precision = 3;
	char dst[] = "**********";
	char *src = "test";
	int dstlen = 10;

	int res = format_snpf_str(dst, dstlen, &fmt, src);
	CU_ASSERT_STRING_EQUAL(dst, "    tes***");
	CU_ASSERT_STRING_EQUAL(src, "test");
	CU_ASSERT_EQUAL(res, 7);
}

void test_format_snpf_str_precision_3_width_7_soon() {
	struct snpf_format fmt;
	reset_snpf_format(&fmt);
	fmt.width = 7;
	fmt.precision = 3;
	char dst[] = "**********";
	char *src = "test";
	int dstlen = 5;

	int res = format_snpf_str(dst, dstlen, &fmt, src);
	CU_ASSERT_STRING_EQUAL(dst, "    t*****");
	CU_ASSERT_STRING_EQUAL(src, "test");
	CU_ASSERT_EQUAL(res, 7);
}

void test_format_snpf_str_precision_3_width_7_soon2() {
	struct snpf_format fmt;
	reset_snpf_format(&fmt);
	fmt.width = 7;
	fmt.precision = 3;
	char dst[] = "**********";
	char *src = "test";
	int dstlen = 3;

	int res = format_snpf_str(dst, dstlen, &fmt, src);
	CU_ASSERT_STRING_EQUAL(dst, "   *******");
	CU_ASSERT_STRING_EQUAL(src, "test");
	CU_ASSERT_EQUAL(res, 7);
}

void test_format_snpf_str_precision_3_width_7_empty() {
	struct snpf_format fmt;
	reset_snpf_format(&fmt);
	fmt.width = 7;
	fmt.precision = 3;
	char dst[] = "**********";
	char *src = "test";
	int dstlen = 0;

	int res = format_snpf_str(dst, dstlen, &fmt, src);
	CU_ASSERT_STRING_EQUAL(dst, "**********");
	CU_ASSERT_STRING_EQUAL(src, "test");
	CU_ASSERT_EQUAL(res, 7);
}

void test_format_snpf_str_precision_3_plenty_left() {
	struct snpf_format fmt;
	reset_snpf_format(&fmt);
	fmt.precision = 3;
	fmt.align = PS2SNPF_LEFT;
	char dst[] = "**********";
	char *src = "test";
	int dstlen = 10;

	int res = format_snpf_str(dst, dstlen, &fmt, src);
	CU_ASSERT_STRING_EQUAL(dst, "tes*******");
	CU_ASSERT_STRING_EQUAL(src, "test");
	CU_ASSERT_EQUAL(res, 3);
}

void test_format_snpf_str_precision_3_soon_left() {
	struct snpf_format fmt;
	reset_snpf_format(&fmt);
	fmt.precision = 3;
	fmt.align = PS2SNPF_LEFT;
	char dst[] = "**********";
	char *src = "test";
	int dstlen = 2;

	int res = format_snpf_str(dst, dstlen, &fmt, src);
	CU_ASSERT_STRING_EQUAL(dst, "te********");
	CU_ASSERT_STRING_EQUAL(src, "test");
	CU_ASSERT_EQUAL(res, 3);
}

void test_format_snpf_str_precision_3_empty_left() {
	struct snpf_format fmt;
	reset_snpf_format(&fmt);
	fmt.precision = 3;
	fmt.align = PS2SNPF_LEFT;
	char dst[] = "**********";
	char *src = "test";
	int dstlen = 0;

	int res = format_snpf_str(dst, dstlen, &fmt, src);
	CU_ASSERT_STRING_EQUAL(dst, "**********");
	CU_ASSERT_STRING_EQUAL(src, "test");
	CU_ASSERT_EQUAL(res, 3);
}

void test_format_snpf_str_precision_3_width_7_plenty_left() {
	struct snpf_format fmt;
	reset_snpf_format(&fmt);
	fmt.width = 7;
	fmt.precision = 3;
	fmt.align = PS2SNPF_LEFT;
	char dst[] = "**********";
	char *src = "test";
	int dstlen = 10;

	int res = format_snpf_str(dst, dstlen, &fmt, src);
	CU_ASSERT_STRING_EQUAL(dst, "tes    ***");
	CU_ASSERT_STRING_EQUAL(src, "test");
	CU_ASSERT_EQUAL(res, 7);
}

void test_format_snpf_str_precision_3_width_7_soon_left() {
	struct snpf_format fmt;
	reset_snpf_format(&fmt);
	fmt.width = 7;
	fmt.precision = 3;
	fmt.align = PS2SNPF_LEFT;
	char dst[] = "**********";
	char *src = "test";
	int dstlen = 5;

	int res = format_snpf_str(dst, dstlen, &fmt, src);
	CU_ASSERT_STRING_EQUAL(dst, "tes  *****");
	CU_ASSERT_STRING_EQUAL(src, "test");
	CU_ASSERT_EQUAL(res, 7);
}

void test_format_snpf_str_precision_3_width_7_soon2_left() {
	struct snpf_format fmt;
	reset_snpf_format(&fmt);
	fmt.width = 7;
	fmt.precision = 3;
	fmt.align = PS2SNPF_LEFT;
	char dst[] = "**********";
	char *src = "test";
	int dstlen = 2;

	int res = format_snpf_str(dst, dstlen, &fmt, src);
	CU_ASSERT_STRING_EQUAL(dst, "te********");
	CU_ASSERT_STRING_EQUAL(src, "test");
	CU_ASSERT_EQUAL(res, 7);
}

void test_format_snpf_str_precision_3_width_7_empty_left() {
	struct snpf_format fmt;
	reset_snpf_format(&fmt);
	fmt.width = 7;
	fmt.precision = 3;
	fmt.align = PS2SNPF_LEFT;
	char dst[] = "**********";
	char *src = "test";
	int dstlen = 0;

	int res = format_snpf_str(dst, dstlen, &fmt, src);
	CU_ASSERT_STRING_EQUAL(dst, "**********");
	CU_ASSERT_STRING_EQUAL(src, "test");
	CU_ASSERT_EQUAL(res, 7);
}

void test_format_snpf_compare() {
	struct snpf_format fmt;
	reset_snpf_format(&fmt);
	fmt.width = 5;
	fmt.precision = 3;
	fmt.align = PS2SNPF_LEFT;
	char dst_snpf[] = "****************";
	char dst_ps2snpf[] = "****************";
	char *src = "test";
	int dstlen = 16;

	int expected = snprintf(dst_snpf, 6, "%-5.3s", src);
	int actual = format_snpf_str(dst_ps2snpf, dstlen, &fmt, src);

	// snprintf inserts a \0 after at position [n-1] - so we must only compare
	// the first n-1 characters
	CU_ASSERT_NSTRING_EQUAL(dst_snpf, dst_ps2snpf, 5);
	CU_ASSERT_EQUAL(expected, actual);
}

void test_read_number() {
	char *subject = "100";

	int num = read_number(&subject);
	CU_ASSERT_EQUAL(100, num);
	CU_ASSERT_STRING_EQUAL("", subject);

	subject = "100!";
	num = read_number(&subject);
	CU_ASSERT_EQUAL(100, num);
	CU_ASSERT_STRING_EQUAL("!", subject);

	subject = "100.000";
	num = read_number(&subject);
	CU_ASSERT_EQUAL(100, num);
	CU_ASSERT_STRING_EQUAL(".000", subject);

	subject = "l100.000";
	num = read_number(&subject);
	CU_ASSERT_EQUAL(0, num);
	CU_ASSERT_STRING_EQUAL("l100.000", subject);

	subject = "123456789";
	num = read_number(&subject);
	CU_ASSERT_EQUAL(123456789, num);
	CU_ASSERT_STRING_EQUAL("", subject);
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
	CU_ADD_TEST(suite, test_format_snpf_str_default_fmt_plenty);
	CU_ADD_TEST(suite, test_format_snpf_str_default_fmt_soon);
	CU_ADD_TEST(suite, test_format_snpf_str_default_fmt_empty);

	CU_ADD_TEST(suite, test_format_snpf_str_width_0_plenty);
	CU_ADD_TEST(suite, test_format_snpf_str_width_0_soon);
	CU_ADD_TEST(suite, test_format_snpf_str_width_0_empty);

	CU_ADD_TEST(suite, test_format_snpf_str_width_10_plenty);
	CU_ADD_TEST(suite, test_format_snpf_str_width_10_soon);
	CU_ADD_TEST(suite, test_format_snpf_str_width_10_empty);

	CU_ADD_TEST(suite, test_format_snpf_str_width_10_left_plenty);
	CU_ADD_TEST(suite, test_format_snpf_str_width_10_left_soon);
	CU_ADD_TEST(suite, test_format_snpf_str_width_10_left_empty);

	CU_ADD_TEST(suite, test_format_snpf_str_precision_3_plenty);
	CU_ADD_TEST(suite, test_format_snpf_str_precision_3_soon);
	CU_ADD_TEST(suite, test_format_snpf_str_precision_3_empty);

	CU_ADD_TEST(suite, test_format_snpf_str_precision_3_width_7_plenty);
	CU_ADD_TEST(suite, test_format_snpf_str_precision_3_width_7_soon);
	CU_ADD_TEST(suite, test_format_snpf_str_precision_3_width_7_soon2);
	CU_ADD_TEST(suite, test_format_snpf_str_precision_3_width_7_empty);

	CU_ADD_TEST(suite, test_format_snpf_str_precision_3_plenty_left);
	CU_ADD_TEST(suite, test_format_snpf_str_precision_3_soon_left);
	CU_ADD_TEST(suite, test_format_snpf_str_precision_3_empty_left);

	CU_ADD_TEST(suite, test_format_snpf_str_precision_3_width_7_plenty_left);
	CU_ADD_TEST(suite, test_format_snpf_str_precision_3_width_7_soon_left);
	CU_ADD_TEST(suite, test_format_snpf_str_precision_3_width_7_soon2_left);
	CU_ADD_TEST(suite, test_format_snpf_str_precision_3_width_7_empty_left);

	CU_ADD_TEST(suite, test_format_snpf_compare);

	CU_ADD_TEST(suite, test_read_number);

	return suite;
}
