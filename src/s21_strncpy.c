#include "s21_string.h"


char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
    // Получаем длину строки src
    s21_size_t src_len =  s21_strlen(src);

    // Выбираем, сколько символов копировать
    s21_size_t copy_len;
    if (src_len < n) {
        // Если длина строки src меньше n, копируем src_len символов
        copy_len = src_len;
    } else {
        // Иначе копируем n символов
        copy_len = n;
    }

    // Копируем символы 
    s21_memcpy(dest, src, copy_len);

    // Возвращаем указатель на dest
    return dest;
}
