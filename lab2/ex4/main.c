#include "test.h"

int main()
{
	int number_failed;
	Suite *s;
	SRunner *sr;

	s = ex4_suite();
	sr = srunner_create(s);

	srunner_run_all(sr, CK_NORMAL);
	number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);
	return (number_failed == 0) ? 0 : 1;
}

