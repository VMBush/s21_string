#include "s21_string.h"

char *s21_strcat(char *str1, const char *str2) {
  int start = (int)s21_strlen(str1);
  for (int i = 0; i <= (int)s21_strlen(str2); i++) {
    str1[start + i] = str2[i];
  }
  return str1;
}
