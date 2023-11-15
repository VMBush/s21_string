
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
    if (!patterns.data[i].isChar && !patterns.data[i].skipping) {
      va_arg(dest, void*);
    }
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
    switch (pattern.sym) {  // *s
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

      case 'o':
        *err = scanOct(str, pattern, va_arg(dest, void*));
        *succ_cntr += 1 - *err;
        break;
      case 'e':
      case 'E':
      case 'f':
      case 'g':
      case 'G':
        *err = scanFloat_Sci(str, pattern, va_arg(dest, void*));
        *succ_cntr += 1 - *err;
        break;
      case 'i':
        *err = scanMultiDec(str, pattern, va_arg(dest, void*));
        *succ_cntr += 1 - *err;
        break;
      case 'c':
        *err = scanChar(str, pattern, va_arg(dest, void*));
        *succ_cntr += 1 - *err;
        break;
    }
  }
}

int scanInt(const char** str, struct Pattern pattern, void* dest) {
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
  long long res = 0;

  // считывание символов
  for (int i = 0; i < len; i++) {
    res *= 10;
    res += (*str)[i] - '0';
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
      *(unsigned short*)dest = (unsigned short)res;
    } else if (pattern.lengh == 'l') {
      *(unsigned long*)dest = res;
    } else {
      *(unsigned int*)dest = (unsigned int)res;
    }
  }

  return 0;
}

int scanMultiDec(const char** str, struct Pattern pattern, void* dest) {
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

  long int res = 0;
  int err = 0;
  struct Pattern forScan = {0, 0, pattern.width, 'l', 'd'};

  if (**str == '0') {
    if (*(*str + 1) == 'x') {
      forScan.sym = 'x';
      err = scanHex(str, forScan, &res);
    } else {
      forScan.sym = 'o';
      err = scanOct(str, forScan, &res);
    }
  } else {
    forScan.sym = 'd';
    err = scanInt(str, forScan, &res);
  }

  if (sign == '-') {
    res *= -1;
  }

  if (pattern.lengh == 'h') {
    *(short*)dest = (short)res;
  } else if (pattern.lengh == 'l') {
    *(long*)dest = res;
  } else {
    *(int*)dest = (int)res;
  }

  return err;
}
// Если считываем хекс, записываем инт, если указатель, то преобразуем инт в
// (void*)
int scanHex(const char** str, struct Pattern pattern, void* dest) {
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

  // обрабатываем начало даты на 0х, а также на конец даты в том же месте
  int prrefix = 0;
  if (!s21_strncmp(*str, "0x", 2)) {
    prrefix = 1;
    if (pattern.width == 1 || pattern.width == 2) {
      *(int*)dest = 0;
      (*str) += pattern.width;
      return 0;
    }

    pattern.width -= 2;
    *str += 2;
  }

  // сколько символов нужно считать
  int len = s21_strspn(*str, "0123456789abcdefABCDEF");
  if (len == 0) {
    if (prrefix == 1) {
      if (pattern.sym == 'p') {
        *(void**)dest = (void*)0;
        return 0;
      } else {
        *(int*)dest = 0;
        return 0;
      }
    }
    return 1;
  }
  if (pattern.width > 0 && pattern.width < len) {
    len = pattern.width;
  }
  long long res = 0;

  // понижаем регистр строки
  char* number_str = malloc((len + 1) * sizeof(char));
  s21_strncpy(number_str, *str, len);
  number_str[len] = '\0';
  char* lower_str = s21_to_lower(number_str);
  free(number_str);

  // считывание символов
  for (int i = 0; i < len; i++) {
    res *= 16;
    if (s21_strchr("1234567890", lower_str[i])) {
      res += lower_str[i] - '0';
    } else {
      res += lower_str[i] - 'a' + 10;
    }
  }
  free(lower_str);

  *str += len;

  if (sign == '-') {
    res *= -1;
  }

  // возвращение результата
  if (pattern.sym == 'p') {
    *(void**)dest = (void*)res;
  } else {  // x или X
    if (pattern.lengh == 'h') {
      *(unsigned short*)dest = (unsigned short)res;
    } else if (pattern.lengh == 'l') {
      *(unsigned long*)dest = res;
    } else {
      *(unsigned int*)dest = (unsigned int)res;
    }
  }

  return 0;
}

int scanOct(const char** str, struct Pattern pattern, void* dest) {
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
  int len = s21_strspn(*str, "01234567");

  if (len == 0) {
    return 1;
  }

  if (pattern.width > 0 && pattern.width < len) {
    len = pattern.width;
  }
  long long res = 0;

  // считывание символов
  for (int i = 0; i < len; i++) {
    res *= 8;
    res += (*str)[i] - '0';
  }

  *str += len;

  if (sign == '-') {
    res *= -1;
  }

  // возвращение результата
  if (pattern.lengh == 'h') {
    *(unsigned short*)dest = (unsigned short)res;
  } else if (pattern.lengh == 'l') {
    *(unsigned long*)dest = res;
  } else {
    *(unsigned int*)dest = (unsigned int)res;
  }

  return 0;
}

int scanFloat_Sci(const char** str, struct Pattern pattern, void* dest) {
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
  if (*(*str + len) == '.') {
    len += 1 + s21_strspn(*str + len + 1, "0123456789");
  }

  // считывание части до E
  struct Pattern forScan = {0, 0, pattern.width, 'L', 'f'};
  long double res;
  scanFloat(str, forScan, &res);

  // нужно ли читать дальше
  if (s21_strspn(*str, "eE") && (pattern.width > len || pattern.width <= 0)) {
    // обрабатываем предыдущий ввод и е
    pattern.width = pattern.width - len - 1;
    (*str)++;
    // если ширина не закончилась на е
    if (pattern.width != 0) {
      long int power = 0;
      struct Pattern forScanInt = {0, 0, pattern.width, 'l', 'd'};
      scanInt(str, forScanInt, &power);
      res *= pow(10, power);
    }
  }

  if (sign == '-') {
    res *= -1;
  }

  // возвращение результата

  if (pattern.lengh == 'L') {
    *(long double*)dest = res;
  } else {
    *(float*)dest = (float)res;
  }

  return 0;
}

int scanFloat(const char** str, struct Pattern pattern, void* dest) {
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

  // считывание целой части
  struct Pattern forScan = {0, 0, pattern.width, 'l', 'd'};
  long double res;
  long int_part;
  long dec_part = 0;
  scanInt(str, forScan, &int_part);
  // printf("asas%ld", rrr);
  res = int_part;

  // считывание десятичной части
  if (**str == '.' && (pattern.width > len || pattern.width <= 0)) {
    pattern.width = pattern.width - len - 1;
    (*str)++;

    if (pattern.width != 0) {
      int len = s21_strspn(*str, "0123456789");
      if (pattern.width > 0 && pattern.width < len) {
        len = pattern.width;
      }
      forScan.width = pattern.width;
      scanInt(str, forScan, &dec_part);
      res += dec_part * pow(10, -1 * len);
    }
  }

  if (sign == '-') {
    res *= -1;
  }

  // возвращение результата

  if (pattern.lengh == 'L') {
    *(long double*)dest = res;
  } else {
    *(double*)dest = (double)res;
  }

  return 0;
}

int scanChar(const char** str, struct Pattern pattern, void* dest) {
  if (**str == '\0') {
    return 1;
  }
  wchar_t res = **str;
  (*str)++;

  if (pattern.lengh == 'l') {
    *(wchar_t*)dest = res;
  } else {
    *(char*)dest = (char)res;
  }
  return 0;
}

int scanStr(const char** str, struct Pattern pattern, void* dest) {}