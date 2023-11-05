#include "s21_string.h"

char *s21_strcpy(char *str1, const char *str2) {
  int i;
  for (i = 0; i < (int)s21_strlen(str2); i++) {
    str1[i] = str2[i];
  }
  str1[i] = '\0';

  return str1;
}
