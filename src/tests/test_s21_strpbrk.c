#include "unit_tests.h"
#define CK_FORK no

START_TEST (test_s21_strpbk_test_1){
    const char* str = "Hello, School21!";
    const char* str2 = "School21";
    char *result = s21_strpbrk(str, str2);
    char *expected = strpbrk (str, str2);
    ck_assert_ptr_eq (result, expected);
}
END_TEST

START_TEST (test_s21_strpbk_test_2){
    const char* str = "";
    const char* str2 = "School21";
    char *result = s21_strpbrk(str, str2);
    char *expected = strpbrk (str, str2);
    ck_assert_ptr_eq (result, expected);
}
END_TEST

START_TEST (test_s21_strpbk_test_3){
    const char* str = "Hello, School21!";
    const char* str2 = "";
    char *result = s21_strpbrk(str, str2);
    char *expected = strpbrk (str, str2);
    ck_assert_ptr_eq (result, expected);
}
END_TEST

START_TEST (test_s21_strpbk_test_4){
    const char* str = "Hello, School21!";
    const char* str2 = "parapam";
    char *result = s21_strpbrk(str, str2);
    char *expected = strpbrk (str, str2);
    ck_assert_ptr_eq (result, expected);
}
END_TEST

START_TEST (test_s21_strpbk_test_5){
    const char* str = "Hello, School21! Have a nice day";
    const char* str2 = "parapam";
    char *result = s21_strpbrk(str, str2);
    char *expected = strpbrk (str, str2);
    ck_assert_ptr_eq (result, expected);
}
END_TEST


Suite* make_s21_strpbrk_suite(void){
    Suite* s = suite_create("s21_strpbrk");
    TCase* tc = tcase_create ("s21_strpbrk");
    tcase_add_test(tc, test_s21_strpbk_test_1);
    tcase_add_test(tc, test_s21_strpbk_test_2);
    tcase_add_test(tc, test_s21_strpbk_test_3);
    tcase_add_test(tc, test_s21_strpbk_test_4);
    tcase_add_test(tc, test_s21_strpbk_test_5);
    suite_add_tcase(s, tc);
    return s;
}