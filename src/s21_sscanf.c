
#include "s21_string.h"

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
  int succ_cntr = 0;
  va_list dest;
  va_start(dest, format);

  struct PatternVec patterns = patternVecInit();
  // просканировать паттерны
  getPatterns(&patterns, format);
  // считать данные по паттернам
  const char* str_start = str;
  for (int i = 0; i < patterns.size && err == 0; i++) {
    scanPattern(&str, patterns.data[i], dest, &succ_cntr, str_start, &err);
  }

  va_end(dest);
  patternVecDel(patterns);
  return succ_cntr;
}

void getPatterns(struct PatternVec* patterns, const char* format) {
  // пропускаем пробелы
  while (1) {
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
void scanPattern(const char** str, struct Pattern pattern, va_list dest,
                 int* succ_cntr, const char* str_start, int* err) {
  // обрабатываем простой символ
  if (pattern.isChar) {
    // обрабатываем пропуск символов при пробеле
    if (pattern.sym == ' ') {
      while (**str == ' ') {
        (*str)++;
      }
    } else if (pattern.sym == **str) {
      *str = *str + 1;
    } else {
      *err = 1;
    }

    // обрабатываем спецификаторы
  } else {
    // спецификаторы до пробела
    if (pattern.sym == 'n') {
      *va_arg(dest, int*) = *str - str_start;
      //(*succ_cntr)++; Нет
    }

    while (**str == ' ') {
      (*str)++;
    }
    // спецификаторы после пробела
    switch (pattern.sym) {  // cieEfgGosxXp
      case '%':
        if (**str == '%') {
          *str++;
          //(*succ_cntr)++; Нет
        }
        break;

      case 'd':
      case 'u':
        *err = scanInt(str, pattern, va_arg(dest, void*));
        *succ_cntr += 1 - *err;
        break;

      case 'p':
      case 'x':
      case 'X':
        *err = scanHex(str, pattern, va_arg(dest, void*));
        *succ_cntr += 1 - *err;
        break;
    }
  }
}

int scanInt(const char** str, struct Pattern pattern, void* dest) {
  //   char sym;
  char sign = '+';
  // обработка знакового ввода
  if (s21_strspn(*str, "+-")) {
    // если считали только знак
    if (pattern.width == 1) {
      return 1;
    }
    pattern.width -= 1;
    sign = **str;
    (*str)++;
  }

  // сколько символов нужно считать
  int len = s21_strspn(*str, "0123456789");
  if (len == 0) {
    return 1;
  }
  if (pattern.width > 0 && pattern.width < len) {
    len = pattern.width;
  }
  long res = 0;
  unsigned long ures = 0;

  // считывание символов
  for (int i = 0; i < len; i++) {
    res *= 10;
    ures *= 10;
    res += (*str)[i] - '0';
    ures += (*str)[i] - '0';
  }

*str += len;


  if (sign == '-') {
    res *= -1;
  }

  // возвращение результата
  if (pattern.sym == 'd') {
    if (pattern.lengh == 'h') {
      *(short*)dest = (short)res;
    } else if (pattern.lengh == 'l') {
      *(long*)dest = res;
    } else {
      *(int*)dest = (int)res;
    }
  } else if (pattern.sym == 'u') {
    if (pattern.lengh == 'h') {
      *(unsigned short*)dest = (unsigned short)ures;
    } else if (pattern.lengh == 'l') {
      *(unsigned long*)dest = ures;
    } else {
      *(unsigned int*)dest = (unsigned int)ures;
    }
  }

  return 0;
}

// Если считываем хекс, записываем инт, если указатель, то преобразуем инт в
// (void*)
int scanHex(const char** str, struct Pattern pattern, void* dest) {}