#include "../s21_string.h"
#include "unit_tests.h"
#define CK_FORK no

START_TEST(test_s21_strrchr_found) {
  const char* str = "Test string";
  int ch = 's';

  char* result = s21_strrchr(str, ch);
  char* expected = strrchr(str, ch);

  ck_assert_ptr_eq(result, expected);
}

START_TEST(test_s21_strrchr_not_found) {
  const char* str = "Test string";
  int ch = 'x';

  char* result = s21_strrchr(str, ch);
  char* expected = strrchr(str, ch);

  ck_assert_ptr_eq(result, expected);
}

START_TEST(test_s21_strrchr_empty_string) {
  const char* str = "";
  int ch = 'x';

  char* result = s21_strrchr(str, ch);
  char* expected = strrchr(str, ch);

  ck_assert_ptr_eq(result, expected);
}

START_TEST(test_s21_strrchr_null_string) {
  const char* str = s21_NULL;
  int ch = 'x';

  char* result = s21_strrchr(str, ch);
  char* expected = strrchr(str, ch);

  ck_assert_ptr_eq(result, expected);
}

Suite* make_s21_strrchr_suite(void) {
  Suite* s = suite_create("s21_strrchr");
  TCase* tc = tcase_create("s21_strrchr");

  tcase_add_test(tc, test_s21_strrchr_found);
  tcase_add_test(tc, test_s21_strrchr_not_found);
  tcase_add_test(tc, test_s21_strrchr_empty_string);
  tcase_add_test(tc, test_s21_strrchr_null_string);

  suite_add_tcase(s, tc);
  return s;
}
