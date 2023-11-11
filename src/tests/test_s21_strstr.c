#include "../s21_string.h"
#include "unit_tests.h"

START_TEST(test_s21_strstr_test_1) {
  const char* str = "Hello, School21!";
  const char* str2 = "School21";

  char* result = s21_strstr(str, str2);
  char* expected = strstr(str, str2);

  ck_assert_ptr_eq(result, expected);
}

START_TEST(test_s21_strstr_test_2) {
  const char* str = "";
  const char* str2 = "School21";

  char* result = s21_strstr(str, str2);
  char* expected = strstr(str, str2);

  ck_assert_ptr_eq(result, expected);
}

START_TEST(test_s21_strstr_test_3) {
  const char* str = "Hello, School 21!";
  const char* str2 = "";

  char* result = s21_strstr(str, str2);
  char* expected = strstr(str, str2);

  ck_assert_ptr_eq(result, expected);
}

START_TEST(test_s21_strstr_test_4) {
  const char* str = "Hello, School21!";
  const char* str2 = "PokaPoka!";

  char* result = s21_strstr(str, str2);
  char* expected = strstr(str, str2);

  ck_assert_ptr_eq(result, expected);
}

Suite* make_s21_strstr_suite(void) {
  Suite* s = suite_create("s21_strstr");
  TCase* tc = tcase_create("s21_strstr");

  tcase_add_test(tc, test_s21_strstr_test_1);
  tcase_add_test(tc, test_s21_strstr_test_2);
  tcase_add_test(tc, test_s21_strstr_test_3);
  tcase_add_test(tc, test_s21_strstr_test_4);

  suite_add_tcase(s, tc);
  return s;
}
