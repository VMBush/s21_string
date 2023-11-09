#include "unit_tests.h"

#include <check.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  Suite *s_memchr = make_s21_memchr_suite();
  Suite *s_memcpy = make_s21_memcpy_suite();
  Suite *s_memcmp = make_s21_memcmp_suite();
  //Suite *s_memset = make_s21_memset_suite();
  Suite *s_strtok = make_s21_strtok_suite();

  SRunner *runner = srunner_create(s_memchr);
  srunner_add_suite(runner, s_memcpy);
  srunner_add_suite(runner, s_memcmp);
  //srunner_add_suite(runner, s_memset);
  srunner_add_suite(runner, s_strtok);

  srunner_run_all(runner, CK_NORMAL);
  int failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
