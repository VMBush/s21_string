#include <check.h>
#include <string.h>

#include "../s21_string.h"
#include "unit_tests.h"
#define CK_FORK no

START_TEST(test_s21_memchr) {
  char str[] =
      "This string contains SPESIAL characters: "
      "!@#$%^&*()_+-={}|[]\\�:\";'<>?,./~`12345\t6789\nрусские символы тут "
      "тоже ЕСТЬ";
  for (s21_size_t n = 0; n < 170; n++) {
    for (int c = 0; c <= 1000; c++) {
      ck_assert_pstr_eq(s21_memchr(str, c, n), memchr(str, c, n));
    }
  }
}
END_TEST

Suite* make_s21_memchr_suite(void) {
  Suite* s = suite_create("s21_memchr");
  TCase* tc = tcase_create("s21_memchr");

  tcase_add_test(tc, test_s21_memchr);

  suite_add_tcase(s, tc);
  return s;
}
