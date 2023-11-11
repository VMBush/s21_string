#include "../s21_string.h"
#include "unit_tests.h"
#define CK_FORK no

START_TEST(test_s21_strrchr_test_1) {
  const char* str = "Test string";
  int ch = 's';

  char* result = s21_strrchr(str, ch);
  char* expected = strrchr(str, ch);

  ck_assert_ptr_eq(result, expected);
}

START_TEST(test_s21_strrchr_test_2) {
  const char* str = "Test string";
  int ch = 'x';

  char* result = s21_strrchr(str, ch);
  char* expected = strrchr(str, ch);

  ck_assert_ptr_eq(result, expected);
}

START_TEST(test_s21_strrchr_test_3) {
  const char* str = "";
  int ch = 'x';

  char* result = s21_strrchr(str, ch);
  char* expected = strrchr(str, ch);

  ck_assert_ptr_eq(result, expected);
}

Suite* make_s21_strrchr_suite(void) {
  Suite* s = suite_create("s21_strrchr");
  TCase* tc = tcase_create("s21_strrchr");

  tcase_add_test(tc, test_s21_strrchr_test_1);
  tcase_add_test(tc, test_s21_strrchr_test_2);
  tcase_add_test(tc, test_s21_strrchr_test_3);

  suite_add_tcase(s, tc);
  return s;
}
