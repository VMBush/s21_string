#include "../s21_string.h"
#include "unit_tests.h"
#define CK_FORK no

START_TEST(test_s21_strchr_test1) {
  const char* str = "Privet, Anna!";
  int c = 'a';

  char* result = s21_strchr(str, c);
  char* expected = strchr((char*)str, c);

  ck_assert_ptr_eq(result, expected);
}

START_TEST(test_s21_strchr_test_2) {
  const char* str = "Privet, Anna!";
  int c = 'x';

  char* result = s21_strchr(str, c);
  char* expected = strchr((char*)str, c);

  ck_assert_ptr_eq(result, expected);
}

START_TEST(test_s21_strchr_test_3) {
  const char* str = "";
  int c = 'x';

  char* result = s21_strchr(str, c);
  char* expected = strchr((char*)str, c);

  ck_assert_ptr_eq(result, expected);
}

START_TEST(test_s21_strchr_test_4) {
  const char* str = (char*)s21_NULL;
  int c = 'x';

  char* result = s21_strchr(str, c);
  char* expected = strchr((char*)str, c);

  ck_assert_ptr_eq(result, expected);
}

Suite* make_s21_strchr_suite(void) {
  Suite* s = suite_create("s21_strchr");
  TCase* tc = tcase_create("s21_strchr");

  tcase_add_test(tc, test_s21_strchr_test1);
  tcase_add_test(tc, test_s21_strchr_test_2);
  tcase_add_test(tc, test_s21_strchr_test_3);
  tcase_add_test(tc, test_s21_strchr_test_4);

  suite_add_tcase(s, tc);
  return s;
}
