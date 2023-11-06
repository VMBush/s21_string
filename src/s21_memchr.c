#include "s21_string.h"

// Выполняет поиск первого вхождения символа c (беззнаковый тип) в первых n
// байтах строки, на которую указывает аргумент str.

void *s21_memchr(const void *str, int c, s21_size_t n) {
  unsigned char *p = (unsigned char*)str;
  int result = 1;
  for (s21_size_t i = 0; i < n; i++) {
    if (*p == (unsigned char)c) {
      result = 0;
      break;
    }
    p++;
  }
  if (result) {
    p = s21_NULL;
  }
  return p;
}