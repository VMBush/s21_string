#include "s21_string.h"

// Функция my_strrchr ищет последнее вхождение символа ch в строке str.

char* s21_strrchr(const char* str, int ch) {
  const char* last_symbol = s21_NULL;

  while (*str) {
    if (*str == ch) {
      // Если текущий символ равен искомому символу ch,
      // обновляем указатель на последнее вхождение.
      last_symbol = str;
    }
    str++;
  }

  return (char*)last_symbol;
}
