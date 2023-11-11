#include "unit_tests.h"

#include <check.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  Suite *s_memchr = make_s21_memchr_suite();
  Suite *s_memcpy = make_s21_memcpy_suite();
  Suite *s_memcmp = make_s21_memcmp_suite();
  // Suite *s_memset = make_s21_memset_suite();
  Suite *s_strtok = make_s21_strtok_suite();
  Suite *s_strspn = make_s21_strspn_suite();
  Suite *s_strrchr = make_s21_strrchr_suite();
  Suite *s_strcat = make_s21_strcat_suite();
  Suite *s_strlen = make_s21_strlen_suite();
  Suite *s_strchr = make_s21_strchr_suite();
  Suite *s_strstr = make_s21_strstr_suite();
  Suite *s_strcpy = make_s21_strcpy_suite();
  Suite *s_strcmp = make_s21_strcmp_suite();
  Suite *s_strcspn = make_s21_strcspn_suite();

  SRunner *runner = srunner_create(s_memchr);
  srunner_add_suite(runner, s_memcpy);
  srunner_add_suite(runner, s_memcmp);
  // srunner_add_suite(runner, s_memset);
  srunner_add_suite(runner, s_strtok);
  srunner_add_suite(runner, s_strspn);
  srunner_add_suite(runner, s_strrchr);
  srunner_add_suite(runner, s_strcat);
  srunner_add_suite(runner, s_strlen);
  srunner_add_suite(runner, s_strchr);
  srunner_add_suite(runner, s_strstr);
  srunner_add_suite(runner, s_strcpy);
  srunner_add_suite(runner, s_strcmp);
  srunner_add_suite(runner, s_strcspn);

  srunner_run_all(runner, CK_NORMAL);
  int failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
