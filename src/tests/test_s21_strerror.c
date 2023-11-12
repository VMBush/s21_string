#include "unit_tests.h"
#define CK_FORK no

START_TEST (test_s21_strerror_test_1){
    int n = 0;
    char *result = s21_strerror(n);
    char *expected = strerror(n);
    ck_assert_str_eq(result, expected);
}END_TEST

START_TEST (test_s21_strerror_test_2){
    int n = -2;
    char *result = s21_strerror(n);
    char *expected = strerror(n);
    ck_assert_str_eq(result, expected);
}END_TEST

START_TEST (test_s21_strerror_test_3){
    int n = 10000000;
    char *result = s21_strerror(n);
    char *expected = strerror(n);
    ck_assert_str_eq(result, expected);
}END_TEST

START_TEST (test_s21_strerror_test_4){
    int n = 22;
    char *result = s21_strerror(n);
    char *expected = strerror(n);
    ck_assert_str_eq(result, expected);
}END_TEST


Suite *make_s21_strerror_suite (void){
    Suite* s = suite_create("s21_strerror");
    TCase* tc = tcase_create ("s21_strerrore");
    tcase_add_test(tc, test_s21_strerror_test_1);
    tcase_add_test(tc, test_s21_strerror_test_2);
    tcase_add_test(tc, test_s21_strerror_test_3);
    tcase_add_test(tc, test_s21_strerror_test_4);
    suite_add_tcase(s, tc);
    return s;
}