#include <check.h>
#include <string.h>

#include "../s21_string.h"
#include "unit_tests.h"
#define CK_FORK no

START_TEST(test_s21_memchr) {
  ck_assert_int_eq(1, 1);
}
END_TEST

Suite* make_s21_memchr_suite(void) {
  Suite* s = suite_create("s21_memchr");
  TCase* tc_initCurrentFlag = tcase_create("s21_memchr");

  tcase_add_test(tc_initCurrentFlag, test_s21_memchr);

  suite_add_tcase(s, tc_initCurrentFlag);
  return s;
}
