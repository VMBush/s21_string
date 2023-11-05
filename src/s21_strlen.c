#include "s21_string.h"

s21_size_t s21_strlen(const char *str) {
  s21_size_t res = -1;
  while (str[++res] != '\0')
    ;
  return res;
}
