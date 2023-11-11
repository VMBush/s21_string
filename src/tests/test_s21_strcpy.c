#include "unit_tests.h"
#define CK_FORK no

START_TEST(test_s21_strcpy_test_1) {
  char dest[20] = "test";
  const char* src = "Test copy";

  char* result = s21_strcpy(dest, src);
  char* expected = strcpy(dest, src);

  ck_assert_str_eq(result, expected);
}

START_TEST(test_s21_strcpy_test_2) {
  char dest[20] = "";
  const char* src = "copy Test";

  char* result = s21_strcpy(dest, src);
  char* expected = strcpy(dest, src);

  ck_assert_str_eq(result, expected);
}

START_TEST(test_s21_strcpy_test_3) {
  char dest[20] = "test";
  const char* src = "";

  char* result = s21_strcpy(dest, src);
  char* expected = strcpy(dest, src);

  ck_assert_str_eq(result, expected);
}

Suite* make_s21_strcpy_suite(void) {
  Suite* s = suite_create("s21_strcpy");
  TCase* tc = tcase_create("s21_strcpy");

  tcase_add_test(tc, test_s21_strcpy_test_1);
  tcase_add_test(tc, test_s21_strcpy_test_2);
  tcase_add_test(tc, test_s21_strcpy_test_3);

  suite_add_tcase(s, tc);
  return s;
}
