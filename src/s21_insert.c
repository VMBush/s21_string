#include "s21_string.h"

void *s21_insert(const char *src, const char *str, s21_size_t start_index){
  char *res = s21_NULL;
  if (src && str && start_index <= s21_strlen(src)) {
    s21_size_t len_src = s21_strlen(src);
    s21_size_t len_str = s21_strlen(str);
    res = malloc((len_src + len_str + 1) * sizeof(char));
    if (res != s21_NULL){
        s21_strncpy(res, src, start_index);
        s21_strcpy(res + start_index, str);
        s21_strcpy(res + start_index + len_str, src + start_index);
    }
  }
    return res;
}