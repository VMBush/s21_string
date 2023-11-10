#include "s21_string.h"

void *s21_memmove (void *dest, const void *src, s21_size_t n) {
    char *d = (char *)dest;
    const char *s = src;
    if (d < s) {
        while (n--) {
            *d++ = *s++;
        }
    } else {
        d += n;
        s += n;
        while (n--) {
            *(--d) = *(--s);
        }
    }
    return dest;
}