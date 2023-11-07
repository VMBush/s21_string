#include <check.h>
#include <string.h>

#include "../s21_string.h"
#include "unit_tests.h"
#define CK_FORK no

START_TEST(test_s21_memcmp_base) {
  char str1[] =
      "This string contains SPESIAL characters: "
      "!@#$%^&*()_+-={}|[]\\�:\";'<>?,./~`12345\t6789\nрусские символы тут "
      "тоже ЕСТЬ";
  char str2[] = "This \nрусские символы тут тоже ЕСТЬ";
  for (s21_size_t n = 0; n < 170; n++) {
    int res1 = s21_memcmp(str1, str2, n);
    int res2 = memcmp(str1, str2, n);
    if (res1 == 0 && res2 == 0) {
      ck_assert_int_eq(res1, res2);
    } else {
      ck_assert_int_eq((res2 > 0) == (res1 > 0), 1);
    }
  }
}
END_TEST

START_TEST(test_s21_memcmp_base_reverse) {
  char str1[] =
      "This string contains SPESIAL characters: "
      "!@#$%^&*()_+-={}|[]\\�:\";'<>?,./~`12345\t6789\nрусские символы тут "
      "тоже ЕСТЬ";
  char str2[] = "This \nрусские символы тут тоже ЕСТЬ";
  for (s21_size_t n = 0; n < 170; n++) {
    int res1 = s21_memcmp(str2, str1, n);
    int res2 = memcmp(str2, str1, n);
    if (res1 == 0 && res2 == 0) {
      ck_assert_int_eq(res1, res2);
    } else {
      ck_assert_int_eq((res2 > 0) == (res1 > 0), 1);
    }
  }
}
END_TEST

Suite* make_s21_memcmp_suite(void) {
  Suite* s = suite_create("s21_memcmp");
  TCase* tc = tcase_create("s21_memcmp");

  tcase_add_test(tc, test_s21_memcmp_base);
  tcase_add_test(tc, test_s21_memcmp_base_reverse);

  suite_add_tcase(s, tc);
  return s;
}
