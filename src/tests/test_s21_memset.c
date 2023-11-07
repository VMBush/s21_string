#include <check.h>
#include <string.h>

#include "../s21_string.h"
#include "unit_tests.h"
#define CK_FORK no

START_TEST(test_s21_memset) {
  char str1[] = "This string contains characters";
  char str2[] = "This string contains characters";
  for (s21_size_t n = 0; n < 39; n++) {
    for (int c = 0; c <= 1000; c++) {
      ck_assert_pstr_eq(s21_memset(str1, c, n), memset(str2, c, n));
    }
  }
}
END_TEST

Suite* make_s21_memset_suite(void) {
  Suite* s = suite_create("s21_memset");
  TCase* tc = tcase_create("s21_memset");

  tcase_add_test(tc, test_s21_memset);

  suite_add_tcase(s, tc);
  return s;
}
