#include "unit_tests.h"
#define CK_FORK no 

START_TEST (test_s21_insert_test_1){
    const char *src = "Hello, 21!";
    const char *str = "School";
    size_t n = 7;
    char* result = (char *)s21_insert(src, str, n);
    ck_assert_str_eq(result, "Hello, School21!");
    free(result);

} END_TEST

START_TEST (test_s21_insert_test_2){
    const char *src = "hello!";
    const char *str = "School21, ";
    size_t n = 0;
    char* result = (char *)s21_insert(src, str, n);
    ck_assert_str_eq(result, "School21, hello!");
    free(result);

} END_TEST

START_TEST (test_s21_insert_test_3){
    const char *src = "";
    const char *str = "School";
    size_t n = 2;
    char* result = (char *)s21_insert(src, str, n);
    ck_assert_ptr_eq(result, s21_NULL);
    free(result);

} END_TEST

START_TEST (test_s21_insert_test_4){
    const char *src = "goodbye";
    const char *str = " ";
    size_t n = 4;
    char* result = (char *)s21_insert(src, str, n);
    ck_assert_str_eq(result, "good bye");
    free(result);

} END_TEST

Suite *make_s21_insert_suite (void){
    Suite* s = suite_create("s21_insert");
    TCase* tc = tcase_create ("s21_insert");
    tcase_add_test(tc, test_s21_insert_test_1);
    tcase_add_test(tc, test_s21_insert_test_2);
    tcase_add_test(tc, test_s21_insert_test_3);
    tcase_add_test(tc, test_s21_insert_test_4);
    suite_add_tcase(s, tc);
    return s;
}