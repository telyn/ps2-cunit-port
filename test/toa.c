#include <CUnit/CUnit.h>
#include "toa.h"

void test_ps2_itoa() {
	int n_tests = 15;
	int tests[] = {
		0, 1, 20, 300, 4500, 67000, 890001,
		22, 33, 44, 55, 66, 77, 88, 99
	};
	char *expecteds[] = {
		"0", "1", "20", "300", "4500", "67000", "890001",
	    "22", "33", "44", "55", "66", "77", "88", "99"
	};
	int i;
	char dst[13] = { '\0' };
	for(i = 0; i < n_tests; i++) {
		strcpy(dst, "testtesttest");
		ps2_itoa(tests[i], dst);
		CU_ASSERT_STRING_EQUAL(dst, expecteds[i]);

		if (tests[i] == 0) {
			// can't have a -0??
			continue;
		}
		char expected[10] = { '-', '\0' };
		strcpy(expected+1, expecteds[i]);
		ps2_itoa(-tests[i], dst);
		CU_ASSERT_STRING_EQUAL(dst, expected);
	}
}

int close_enough(char *expected, char *actual) {
	int len = strlen(expected);
	int i;
	int decimals = 0;
	int had_dot = 0;
	char expt, act;

	for(i = 0; i < len; i++) {
		expt = expected[i];
		act = actual[i];

		if(had_dot) {
			if(decimals > 2 && (act < '0' || act > '9')) {
				return 0;
			}
			decimals++;
		} else {
			if(expt != act) {
				return 0;
			} else if(expt == '.') {
				had_dot = 1;
			}
		}
	}
	return 1;
}

void test_ps2_ftoa() {
	int n_tests = 15;
	double tests[] = {
		0.1,
		1.0,
		20.63,
		300.999,
		4500.2324323,
		67000.9999111,
		890001.99992222,
		22.0021341,
		33.000000012,
		44.00123404235,
		55.04572,
		66.0235764,
		77.0244563,
		88.0135612,
		99.2455812
	};
	char *expecteds[] = {
		"0.10000000",
		"1.00000000",
		"20.62999999",
		"300.99900000",
		"4500.23243230",
		"67000.99991110",
		"890001.99992222",
	    "22.00213409",
		"33.00000001",
		"44.00123404",
		"55.04572000",
		"66.02357640",
		"77.02445630",
		"88.01356120",
		"99.24558120"
	};
	int i;
	char dst[32] = { '\0' };
	for(i = 0; i < n_tests; i++) {
		strcpy(dst, "testtesttest");
		ps2_ftoa(tests[i], dst);
		CU_ASSERT(close_enough(expecteds[i], dst));

		char expected[32] = { '-', '\0' };
		strcpy(expected+1, expecteds[i]);
		ps2_ftoa(-tests[i], dst);
		CU_ASSERT(close_enough(expected, dst));
	}
}


CU_pSuite ps2cunit_toa_suite() {
	CU_pSuite suite = CU_add_suite("toa", NULL, NULL);
	//CU_ADD_TEST(suite, test_ps2_itoa);
	CU_ADD_TEST(suite, test_ps2_ftoa);
	return suite;
}
