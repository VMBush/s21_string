#include "../s21_string.h"
#include "unit_tests.h"
#define CK_FORK no

START_TEST(test_s21_strcat_test_1) {
  char str1[20] = "Hello, ";
  const char* str2 = "Kitti!";

  char* result = s21_strcat(str1, str2);
  char* expected = strcat(str1, str2);

  ck_assert_str_eq(result, expected);
}

START_TEST(test_s21_strcat_test_2) {
  char str1[20] = "";
  const char* str2 = "Kitti!";

  char* result = s21_strcat(str1, str2);
  char* expected = strcat(str1, str2);

  ck_assert_str_eq(result, expected);
}

START_TEST(test_s21_strcat_test_3) {
  char str1[20] = "Hello, ";
  const char* str2 = "";

  char* result = s21_strcat(str1, str2);
  char* expected = strcat(str1, str2);

  ck_assert_str_eq(result, expected);
}

START_TEST(test_s21_strcat_test_4) {
  char str1[20] = "";
  const char* str2 = "";

  char* result = s21_strcat(str1, str2);
  char* expected = strcat(str1, str2);

  ck_assert_str_eq(result, expected);
}

Suite* make_s21_strcat_suite(void) {
  Suite* s = suite_create("s21_strcat");
  TCase* tc = tcase_create("s21_strcat");

  tcase_add_test(tc, test_s21_strcat_test_1);
  tcase_add_test(tc, test_s21_strcat_test_2);
  tcase_add_test(tc, test_s21_strcat_test_3);
  tcase_add_test(tc, test_s21_strcat_test_4);

  suite_add_tcase(s, tc);
  return s;
}
