#ifndef TESTS_H
#define TESTS_H

#define CLEAR "\033[0m"
#define GREEN "\x1B[32m"
#define RED   "\x1B[31m"
#define CYAN  "\x1B[36m"

#define RUN_TEST(test) \
if(test()){ printf(GREEN "%-24s| %5s\n" CLEAR, "["#test"]","OK!"); } \
else{ printf(RED "%-24s| %7s\n" CLEAR, "["#test"]", "FAIL!"); }

/* 
	This macro requires:
		size_t test_no = 0;
	To be declared in the same scope.

	Also requires:
		size_t g_total_tests = 0;
		size_t g_total_success = 0;
		size_t g_total_failed = 0;
	To be declared in the global scope.	
*/
#define TEST_EQUAL(res, expected) \
++test_no; ++g_total_tests;\
printf("\ttest %lu: expected: %d, got: %d\n",\
test_no, expected, res); result *= (expected == res); \
(expected == res) ? (++g_total_success) : (++g_total_failed);

#define TEST_NOT_EQUAL(res, expected) \
++test_no; ++g_total_tests;\
printf("\ttest %lu: expected not: %d, got: %d\n",\
test_no, expected, res); result *= (expected != res); \
(expected != res) ? (++g_total_success) : (++g_total_failed);

#define TEST_SUMMARY(tot, success, fail) \
printf(CYAN "\nTest Result Summary:\n" CLEAR); \
printf("Total:     %lu [100.0%%]\n", tot); \
printf(RED "Failed:     %lu [%.1f%%]\n" CLEAR, fail, \
((float)fail / tot) * 100); \
printf(GREEN "Succeeded: %lu [%.1f%%]\n" CLEAR, success, \
((float)success / tot) * 100);

#endif
