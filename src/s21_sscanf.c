
#include "s21_string.h"

// error 0 если не удалось считать

struct PatternVec patternVecInit() {
  struct PatternVec vec = {0, 0, 5, malloc(5 * sizeof(struct Pattern))};
  return vec;
}

void patternVecPush(struct PatternVec* vec, struct Pattern pattern) {
  if (vec->capacity == vec->size) {
    vec->data = realloc(vec->data, vec->capacity * 2 * sizeof(struct Pattern));
    vec->capacity *= 2;
  }

  vec->data[vec->size] = pattern;
  vec->size++;
}

void patternVecDel(struct PatternVec vec) { free(vec.data); }

int s21_sscanf(const char* str, const char* format, ...) {
  int err = 0;
  int cntr = 0;
  va_list dest;
  va_start(dest, format);

  struct PatternVec patterns = patternVecInit();
  //просканировать паттерны
  getPatterns(&patterns, format);
  for (int i = 0; i < patterns.size && err == 0; i++) {
    scanPattern(&str, patterns.data[i], dest, &cntr, &err);
  }
  
  va_end(dest);
  patternVecDel(patterns);
  return cntr;
}

void getPatterns(struct PatternVec* patterns, const char* format) {
  // пропускаем пробелы
  while (1) {
    while (*format == ' ') {
      format++;
    }
    // обрабатываем конец строки
    if (*format == '\0') {
      break;
    }
    // считываем обычные символы
    if (*format != '%') {
      struct Pattern new = {1, 0, 0, '\0', *format};
      patternVecPush(patterns, new);
      format++;
    }
    // обрабатываем спецификатор
    else {
      // создаем новый паттерн
      struct Pattern new = {0, 0, -1, '\0', '\0'};
      format++;
      // обрабатываем пропуск
      if (*format == '*') {
        new.skipping = 1;
        format++;
      }
      // обрабатываем ширину
      if (*format >= '0' && *format <= '9') {
        struct Pattern forScan = {0, 0, -1, '\0', 'd'};
        scanInt(&format, forScan, &new.width);
      }
      // обрабатываем длину
      if (s21_strchr("hIL", *format)) {
        new.lengh = *format;
        format++;
      }
      // обрабатываем спецификатор
      if (!s21_strchr("cdieEfgGosuxXpn%", *format)) {
        printf(
            "Введен непозволительный спецификатор: %c! Дальнейшее поведение не "
            "определено.",
            *format);
        format++;
      } else {
        new.sym = *format;
        format++;
      }

      // добавляем паттерн
      patternVecPush(patterns, new);
    }
  }
}

// Считывает один паттерн, двигая указатель
void scanPattern(const char** str, struct Pattern pattern, va_list dest, int* succ_cntr,
                 int* err) {
  int i = 0;
}

void scanInt(const char** str, struct Pattern pattern, int* dest) {}