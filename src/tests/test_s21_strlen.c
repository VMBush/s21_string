#include "../s21_string.h"
#include "unit_tests.h"
#define CK_FORK no

START_TEST(test_s21_strlen_test_1) {
  const char* str = "Hello, Slava";

  s21_size_t result = s21_strlen(str);
  s21_size_t expected = strlen(str);

  ck_assert_int_eq(result, expected);
}

START_TEST(test_s21_strlen_test_2) {
  const char* str = "";

  s21_size_t result = s21_strlen(str);
  s21_size_t expected = strlen(str);

  ck_assert_int_eq(result, expected);
}

Suite* make_s21_strlen_suite(void) {
  Suite* s = suite_create("s21_strlen");
  TCase* tc = tcase_create("s21_strlen");

  tcase_add_test(tc, test_s21_strlen_test_1);
  tcase_add_test(tc, test_s21_strlen_test_2);

  suite_add_tcase(s, tc);
  return s;
}
