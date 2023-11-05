#include "s21_string.h"

char *s21_strchr(const char *str, int c) {
  int l = (int)s21_strlen(str);
  char *t = s21_NULL;
  for (int i = 0; i < l; i++) {
    if (c == (int)str[i]) {
      t = (char *)&str[i];
      break;
    }
  }
  return t;
}