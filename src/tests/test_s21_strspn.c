#include "../s21_string.h"
#include "unit_tests.h"
#define CK_FORK no

START_TEST(test_s21_strspn_matching_characters) {
  const char* str1 = "abcde";
  const char* str2 = "abc";

  size_t result = s21_strspn(str1, str2);
  size_t expected = strspn(str1, str2);

  ck_assert_int_eq(result, expected);
}

START_TEST(test_s21_strspn_no_matching_characters) {
  const char* str1 = "abcde";
  const char* str2 = "xyz";

  size_t result = s21_strspn(str1, str2);
  size_t expected = strspn(str1, str2);

  ck_assert_int_eq(result, expected);
}

START_TEST(test_s21_strspn_empty_str1) {
  const char* str1 = "";
  const char* str2 = "xyz";

  size_t result = s21_strspn(str1, str2);
  size_t expected = strspn(str1, str2);

  ck_assert_int_eq(result, expected);
}

START_TEST(test_s21_strspn_empty_str2) {
  const char* str1 = "abcde";
  const char* str2 = "";

  size_t result = s21_strspn(str1, str2);
  size_t expected = strspn(str1, str2);

  ck_assert_int_eq(result, expected);
}

Suite* make_s21_strspn_suite(void) {
  Suite* s = suite_create("s21_strspn");
  TCase* tc = tcase_create("s21_strspn");

  tcase_add_test(tc, test_s21_strspn_matching_characters);
  tcase_add_test(tc, test_s21_strspn_no_matching_characters);
  tcase_add_test(tc, test_s21_strspn_empty_str1);
  tcase_add_test(tc, test_s21_strspn_empty_str2);

  suite_add_tcase(s, tc);
  return s;
}
