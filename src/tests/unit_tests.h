#ifndef _UNI_TEST_H
#define _UNI_TEST_H
#include <check.h>
#include "../s21_string.h"
#include "string.h"


Suite* make_s21_memchr_suite(void);
Suite* make_s21_memcpy_suite(void);
Suite* make_s21_memcmp_suite(void);
Suite* make_s21_memset_suite(void);
Suite* make_s21_strtok_suite(void);
Suite* make_s21_strspn_suite(void);
Suite* make_s21_strrchr_suite(void);
Suite* make_s21_strcat_suite(void);
Suite* make_s21_strlen_suite(void);
Suite* make_s21_strchr_suite(void);
Suite* make_s21_strstr_suite(void);
Suite* make_s21_strcpy_suite(void);
Suite* make_s21_strcmp_suite(void);
Suite* make_s21_strcspn_suite(void);
Suite* make_s21_strncmp_suite(void);
Suite* make_s21_strpbrk_suite(void);


#endif
