#include "unit_tests.h"
#define CK_FORK no

START_TEST(test_s21_strcmp_test_1) {
  const char* str1 = "Hello, Zina!";
  const char* str2 = "Hello, Zina!";

  int result = s21_strcmp(str1, str2);
  int expected = strcmp(str1, str2);

  ck_assert_int_eq(result, expected);
}

START_TEST(test_s21_strcmp_test_2) {
  const char* str1 = "Hello";
  const char* str2 = "Hello, Zina!";

  int result = s21_strcmp(str1, str2);
  int expected = strcmp(str1, str2);

  ck_assert_int_eq(result, expected);
}

START_TEST(test_s21_strcmp_test_3) {
  const char* str1 = "Hello, Zina!";
  const char* str2 = "Hello";

  int result = s21_strcmp(str1, str2);
  int expected = strcmp(str1, str2);

  ck_assert_int_eq(result, expected);
}

START_TEST(test_s21_strcmp_test_4) {
  const char* str1 = "";
  const char* str2 = "";

  int result = s21_strcmp(str1, str2);
  int expected = strcmp(str1, str2);

  ck_assert_int_eq(result, expected);
}

Suite* make_s21_strcmp_suite(void) {
  Suite* s = suite_create("s21_strcmp");
  TCase* tc = tcase_create("s21_strcmp");

  tcase_add_test(tc, test_s21_strcmp_test_1);
  tcase_add_test(tc, test_s21_strcmp_test_2);
  tcase_add_test(tc, test_s21_strcmp_test_3);
  tcase_add_test(tc, test_s21_strcmp_test_4);

  suite_add_tcase(s, tc);
  return s;
}
