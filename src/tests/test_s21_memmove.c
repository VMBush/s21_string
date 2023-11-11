#include "unit_tests.h"
#define CK_FORK no

START_TEST(test_s21_memmove_test_1){
    char str[17] = "Hello, School21!";
    s21_size_t n = 5;
    char* result = s21_memmove(str+5, str, n);
    strcpy(str, "Hello, School21!");
    char* expected = memmove(str+5, str, n);
    ck_assert_ptr_eq(result, expected);
} 
END_TEST

START_TEST(test_s21_memmove_test_2){
    const char str[17] = "Hello, School21!";
    char str2 [strlen(str)];
    s21_size_t n = 15;
    char* result = s21_memmove(str2, str, n);
    strcpy(str2, "Hello, School21!");
    char* expected = memmove(str2, str, n);
    ck_assert_ptr_eq(result, expected);
} 
END_TEST

START_TEST(test_s21_memmove_test_3){
    char str[17] = "";
    s21_size_t n = 5;
    char* result = s21_memmove(str+5, str, n);
    strcpy(str, "");
    char* expected = memmove(str+5, str, n);
    ck_assert_ptr_eq(result, expected);
} 
END_TEST

Suite *make_s21_memmove_suite (void){
    Suite* s = suite_create("s21_memmove");
    TCase* tc = tcase_create ("s21_memmove");
    tcase_add_test(tc, test_s21_memmove_test_1);
    tcase_add_test(tc, test_s21_memmove_test_2);
    tcase_add_test(tc, test_s21_memmove_test_3);
    suite_add_tcase(s, tc);
    return s;
}