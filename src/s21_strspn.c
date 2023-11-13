#include "s21_string.h"

// Вычисления длины начального сегмента строки str1, который состоит только из
// символов, присутствующих в строке str2.

s21_size_t s21_strspn(const char *str1, const char *str2) {
  s21_size_t count = 0;

  while (*str1 && s21_strchr(str2, *str1)) {
    count++;
    str1++;
  }

  return count;  // Возвращаем длину начального сегмента
}
