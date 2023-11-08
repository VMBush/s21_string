#include "s21_string.h"

char *s21_strpbrk(const char *str1, const char *str2){
    s21_size_t size = s21_strlen(str1);
    char *str = s21_NULL;
    s21_size_t i = 0;
    bool flag = true;
    while (str1[i] != '\0' && flag){
        if (s21_strchr(str2, str1[i]) == s21_NULL){
            i++;
        }
        else{
            flag = false;
        }
    }
    if(i < size){
        str = (char*)str1 + i;
    }
    return str;
}