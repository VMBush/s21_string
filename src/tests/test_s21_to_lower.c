#include "unit_tests.h"
#define CK_FORK no

START_TEST(test_s21_to_lower_test_1) { 
    char *str = "AABBCCDD";
    char *result = s21_to_lower(str);
    char *expected = "aabbccdd";
    ck_assert_str_eq(result, expected);
    free(result);
} END_TEST

START_TEST(test_s21_to_lower_test_2) { 
    char *str = s21_NULL;
    char *result = s21_to_lower(str);
    ck_assert_ptr_eq(result, s21_NULL);
    free(result);
} END_TEST

START_TEST(test_s21_to_lower_test_3) { 
    char *str = "AaBbCcDd";
    char *result = s21_to_lower(str);
    char *expected = "aabbccdd";
    ck_assert_str_eq(result, expected);
    free(result);
} END_TEST

START_TEST(test_s21_to_lower_test_4) { 
    char *str = "Hello, SCHOOL21!";
    char *result = s21_to_lower(str);
    char *expected = "hello, school21!";
    ck_assert_str_eq(result, expected);
    free(result);
} END_TEST

START_TEST(test_s21_to_lower_test_5) { 
    char *str = "";
    char *result = s21_to_lower(str);
    ck_assert_str_eq(result, "");
    free(result);
} END_TEST

Suite *make_s21_to_lower_suite (void){
    Suite* s = suite_create("s21_to_lower");
    TCase* tc = tcase_create ("s21_to_lower");
    tcase_add_test(tc, test_s21_to_lower_test_1);
    tcase_add_test(tc, test_s21_to_lower_test_2);
    tcase_add_test(tc, test_s21_to_lower_test_3);
    tcase_add_test(tc, test_s21_to_lower_test_4);
    suite_add_tcase(s, tc);
    return s;
}