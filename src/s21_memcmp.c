#include "s21_string.h"

// Сравнивает первые n байтов str1 и str2.

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  unsigned char *ch1 = (unsigned char *)str1;
  unsigned char *ch2 = (unsigned char *)str2;
  int flag = 0;
  while (n--) {
    if (*ch1 != *ch2) {
      flag = (*ch1 - *ch2);
      ;
      break;
    }
    ch1++;
    ch2++;
  }
  return flag;
}