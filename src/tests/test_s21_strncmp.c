
#include "unit_tests.h"
#define CK_FORK no


START_TEST (test_s21_strncmp_test_1){
    const char* str = "Hello, School21!";
    const char* str2 = "School21";
    s21_size_t n = 4;
    int result = s21_strncmp(str, str2, n);
    int expected = strncmp (str, str2, n);
    ck_assert_int_eq (result, expected);
}
END_TEST

START_TEST (test_s21_strncmp_test_2){
    const char* str = "School21!";
    const char* str2 = "School21";
    s21_size_t n = 4;
    int result = s21_strncmp(str, str2, n);
    int expected = strncmp (str, str2, n);
    ck_assert_int_eq (result, expected);
}
END_TEST

START_TEST (test_s21_strncmp_test_3){
    const char* str = "School21!";
    const char* str2 = "Hello, School21!";
    s21_size_t n = 4;
    int result = s21_strncmp(str, str2, n);
    int expected = strncmp (str, str2, n);
    ck_assert_int_eq (result, expected);
}
END_TEST

START_TEST (test_s21_strncmp_test_4){
    const char* str = "Hello, School21!";
    const char* str2 = "";
    s21_size_t n = 4;
    int result = s21_strncmp(str, str2, n);
    int expected = strncmp (str, str2, n);
    ck_assert_int_eq (result, expected);
}
END_TEST

START_TEST (test_s21_strncmp_test_5){
    const char* str = "";
    const char* str2 = "Hello, School21!";
    s21_size_t n = 4;
    int result = s21_strncmp(str, str2, n);
    int expected = strncmp (str, str2, n);
    ck_assert_int_eq (result, expected);
}
END_TEST

Suite *make_s21_strncmp (void){
    Suite* s = suite_create("s21_strncmp");
    TCase* tc = tcase_create ("s21_strncmp");

    tcase_add_test(tc, test_s21_strncmp_test_1);
    tcase_add_test(tc, test_s21_strncmp_test_2);
    tcase_add_test(tc, test_s21_strncmp_test_3);
    tcase_add_test(tc, test_s21_strncmp_test_4);
    tcase_add_test(tc, test_s21_strncmp_test_5);


    suite_add_tcase(s, tc);
    return s;
}