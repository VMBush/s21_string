#include "../s21_string.h"
#include "unit_tests.h"
#define CK_FORK no

START_TEST(test_s21_strcspn_test_1) {
  const char *str1 = "Hello, Slava_Otrava!";
  const char *str2 = "oSl";

  size_t result = s21_strcspn(str1, str2);
  size_t expected = strcspn(str1, str2);

  ck_assert_int_eq(result, expected);
}

START_TEST(test_s21_strcspn_test_2) {
  const char *str1 = "";
  const char *str2 = "abc";

  size_t result = s21_strcspn(str1, str2);
  size_t expected = strcspn(str1, str2);

  ck_assert_int_eq(result, expected);
}

START_TEST(test_s21_strcspn_test_3) {
  const char *str1 = "Hello, Kitchen!";
  const char *str2 = "";

  size_t result = s21_strcspn(str1, str2);
  size_t expected = strcspn(str1, str2);

  ck_assert_int_eq(result, expected);
}

START_TEST(test_s21_strcspn_test_4) {
  const char *str1 = "";
  const char *str2 = "";

  size_t result = s21_strcspn(str1, str2);
  size_t expected = strcspn(str1, str2);

  ck_assert_int_eq(result, expected);
}

Suite *make_s21_strcspn_suite(void) {
  Suite *s = suite_create("s21_strcspn");
  TCase *tc = tcase_create("s21_strcspn");

  tcase_add_test(tc, test_s21_strcspn_test_1);
  tcase_add_test(tc, test_s21_strcspn_test_2);
  tcase_add_test(tc, test_s21_strcspn_test_3);
  tcase_add_test(tc, test_s21_strcspn_test_4);

  suite_add_tcase(s, tc);
  return s;
}
