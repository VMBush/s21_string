#include "unit_tests.h"

#include <check.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  Suite *s21_memchr = make_s21_memchr_suite();
  // Suite *s21_other = make_s21_other_suite();

  SRunner *runner = srunner_create(s21_memchr);
  // srunner_add_suite(runner, s21_other);

  srunner_run_all(runner, CK_NORMAL);
  int failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
