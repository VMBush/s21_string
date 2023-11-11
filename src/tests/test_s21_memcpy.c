#include <check.h>
#include <string.h>

#include "../s21_string.h"
#include "unit_tests.h"
#define CK_FORK no

START_TEST(test_s21_memcpy) {
  char src[] =
      "This string contains SPESIAL characters: "
      "!@#$%^&*()_+-={}|[]\\�:\";'<>?,./~`12345\t6789\nрусские символы тут "
      "тоже ЕСТЬ";
  char dest[200];
  for (s21_size_t n = 0; n < 200; n++) {
    ck_assert_pstr_eq(s21_memcpy(dest, src, n), memcpy(dest, src, n));
  }
}
END_TEST

Suite* make_s21_memcpy_suite(void) {
  Suite* s = suite_create("s21_memcpy");
  TCase* tc = tcase_create("s21_memcpy");

  tcase_add_test(tc, test_s21_memcpy);

  suite_add_tcase(s, tc);
  return s;
}
