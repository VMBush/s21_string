#include "s21_string.h"

//первый вариант

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
    s21_size_t len_dst = s21_strlen(dest);
    s21_size_t len_src = s21_strlen(src);
    int i = 0;
    for(; i < n && i < len_src; i++) {
        dest[len_dst+i] = src[i];
    }
    dest[len_dst+i] = '\0';
    return dest;
}

//второй вариант

// char *s21_strncat(char *dest, const char *src, s21_size_t n) {
//   s21_size_t len_dest = s21_strlen(dest);
//   s21_size_t len_src = s21_strlen(src);
//   char *vallue = dest;
//   if (len_src < n)
//     s21_strcpy(&dest[len_dest], src);
//   else
//     s21_strncpy(&dest[len_dest], src, n);
//   return vallue;
// }