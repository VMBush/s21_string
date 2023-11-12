#include "s21_string.h"


s21_size_t s21_strcspn(const char *str1, const char *str2) {
    const char *result = s21_strpbrk(str1, str2);

    if (result == NULL) {
        return s21_strlen(str1);
    }
    size_t final_result = result - str1;

    return final_result;
}