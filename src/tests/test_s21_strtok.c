#include "unit_tests.h"
#define CK_FORK no

START_TEST(test_s21_strtok) {
  char str1_1[] = "xxxxxxx";
  char str1_2[] = "xxxxxxx";

  ck_assert_pstr_eq(s21_strtok(str1_1, "x"), strtok(str1_2, "x"));
  ck_assert_pstr_eq(s21_strtok(s21_NULL, "x"), strtok(NULL, "x"));
  ck_assert_pstr_eq(s21_strtok(s21_NULL, "x"), strtok(NULL, "x"));

  char str2_1[] = "xxaaayyybbbxx";
  char str2_2[] = "xxaaayyybbbxx";

  ck_assert_pstr_eq(s21_strtok(str2_1, "yx"), strtok(str2_2, "yx"));
  ck_assert_pstr_eq(s21_strtok(s21_NULL, "yx"), strtok(NULL, "yx"));
  ck_assert_pstr_eq(s21_strtok(s21_NULL, "yx"), strtok(NULL, "yx"));

  char str3_1[] = "aaaa";
  char str3_2[] = "aaaa";

  ck_assert_pstr_eq(s21_strtok(str3_1, "x"), strtok(str3_2, "x"));
  ck_assert_pstr_eq(s21_strtok(s21_NULL, "x"), strtok(NULL, "x"));
  ck_assert_pstr_eq(s21_strtok(s21_NULL, "x"), strtok(NULL, "x"));
}
END_TEST

Suite* make_s21_strtok_suite(void) {
  Suite* s = suite_create("s21_strtok");
  TCase* tc = tcase_create("s21_strtok");

  tcase_add_test(tc, test_s21_strtok);

  suite_add_tcase(s, tc);
  return s;
}
