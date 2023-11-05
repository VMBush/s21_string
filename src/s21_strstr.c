#include "s21_string.h"

char *s21_strstr(const char *str, const char *substr) {
  if (*substr == '\0') {
    return (char *)str;
  }
  const char *res = s21_NULL;
  const char *ptr = str;
  int len = (int)s21_strlen(substr);
  while (1) {
    while (*ptr != *substr && *ptr != '\0') {
      ptr++;
    }
    int i = 0;
    if (*ptr == *substr) {
      for (i = 0; i < len; i++) {
        if (*(ptr + i) == '\0' || *(ptr + i) != *(substr + i)) break;
      }
    }
    if (i == len) {
      res = ptr;
    }
    if (i == len || *ptr == '\0' || *(ptr + i) == '\0') {
      break;
    }
    ptr++;
  }

  return (char *)res;
}
