#include "s21_sprintf.h"

#include "s21_string.h"

void printFormatSpecifier(const formatSpecifier *spec) {
  printf("isFlagPlus: %d\n", spec->isFlagPlus);
  printf("isFlagMinus: %d\n", spec->isFlagMinus);
  printf("isFlagZero: %d\n", spec->isFlagZero);
  printf("isFlagSpace: %d\n", spec->isFlagSpace);
  printf("isFlagSharp: %d\n", spec->isFlagSharp);
  printf("width: %d\n", spec->width);
  printf("precision: %d\n", spec->precision);
  printf("length h: %d\n", spec->length_h);
  printf("length l: %d\n", spec->length_l);
  printf("length L: %d\n", spec->length_L);
  printf("specifier: %c\n", spec->specifier);
}

void fillFlags(char *template, int *offset, formatSpecifier *specific) {
  // Парсинг флагов
  while (template[*offset] == '+' || template[*offset] == '-' ||
         template[*offset] == ' ' || template[*offset] == '0' ||
         template[*offset] == '#') {
    switch (template[*offset]) {
      case '+':
        specific->isFlagPlus = 1;
        break;
      case '-':
        specific->isFlagMinus = 1;
        break;
      case '0':
        specific->isFlagZero = 1;
        break;
      case ' ':
        specific->isFlagSpace = 1;
        break;
      case '#':
        specific->isFlagSharp = 1;
        break;
    }
    (*offset)++;
  }
}

// Парсинг длинны
void fillLength(char *template, int *offset, formatSpecifier *specific) {
  while (template[*offset] == 'h' || template[*offset] == 'l' ||
         template[*offset] == 'L') {
    switch (template[*offset]) {
      case 'h':
        specific->length_h += 1;
        break;
      case 'l':
        specific->length_l += 1;
        break;
      case 'L':
        specific->length_L += 1;
        break;
    }
    (*offset)++;
  }
}

// Метод получения числа из шаблона
int getInt(char *template, int *offset) {
  char strDigit[128];
  int idx = 0;
  while (isdigit(template[*offset])) {
    strDigit[idx++] = template[(*offset)++];
  }
  strDigit[idx] = '\0';
  return atoi(strDigit);
}

// Метод для формирования настроек для конкретного template
formatSpecifier *initFormatSpecifier(char *template, va_list args) {
  formatSpecifier *specific = calloc(1, sizeof(formatSpecifier));
  int offset = 1;
  fillFlags(template, &offset, specific);
  if (template[offset] == '*') {
    specific->width = va_arg(args, int);
    offset++;
  } else {
    specific->width = getInt(template, &offset);
  }

  if (template[offset] == '.') {
    offset++;
    if (template[offset] == '*') {
      specific->precision = va_arg(args, int);
      offset++;
    } else {
      specific->precision = getInt(template, &offset);
    }
  }
  fillLength(template, &offset, specific);
  specific->specifier = template[offset];

  return specific;
}

// Метод для перебора всех совпадений регулярного выражения
void extractMatches(const char *input, const char *pattern, Match **matches,
                    size_t *numMatches) {
  regex_t regex;
  int ret;

  // Компилируем регулярное выражение
  ret = regcomp(&regex, pattern, REG_EXTENDED);
  if (ret == 0) {
    regmatch_t match;
    int offset = 0;

    while (1) {
      ret = regexec(&regex, input + offset, 1, &match, 0);

      if (ret == REG_NOMATCH) {
        break;  // Совпадений больше нет
      }

      // Извлечение совпадения из строки
      int start = match.rm_so + offset;
      int end = match.rm_eo + offset;

      // Расширяем массив совпадений
      *matches = realloc(*matches, (*numMatches + 1) * sizeof(Match));
      (*matches)[*numMatches].start = start;
      (*matches)[*numMatches].end = end;
      (*numMatches)++;

      offset =
          end;  // Устанавливаем новый сдвиг для поиска следующего совпадения
    }
  }
  regfree(&regex);
}

void write_c(char *result, formatSpecifier *specific, va_list args) {
  if (specific->length_l > 0) {
    wchar_t longChar = va_arg(args, wchar_t);
    char srt[] = {longChar, '\0'};
    s21_strcpy(result, srt);
  } else {
    int ch = va_arg(args, int);
    char srt[] = {ch, '\0'};
    s21_strcpy(result, srt);
  }
}

void write_d(char *result, formatSpecifier *specific, va_list args) {
  char *str = NULL;
  int isNegative = 0;
  if (specific->length_h == 1) {
    short int arg = va_arg(args, int);
    isNegative = arg < 0;
    str = convertIntToStr(arg, 10);
  } else if (specific->length_l == 1) {
    long int arg = va_arg(args, long int);
    isNegative = arg < 0;
    str = convertIntToStr(arg, 10);
  } else if (specific->length_l == 2) {
    long long int arg = va_arg(args, long long int);
    isNegative = arg < 0;
    str = convertIntToStr(arg, 10);
  } else {
    int arg = va_arg(args, int);
    isNegative = arg < 0;
    str = convertIntToStr(arg, 10);
  }
  if (str != NULL) {
    formatSpecifier SettingsForPrecision = {0, 0, 1, 0, 0,  specific->precision,
                                            0, 0, 0, 0, 'e'};
    printSpace(str, &SettingsForPrecision);
    char *newStr = NULL;
    if (specific->isFlagPlus) {
      newStr = s21_insert(str, isNegative ? "-" : "+", 0);
    } else if (specific->isFlagSpace) {
      newStr = s21_insert(str, isNegative ? "-" : " ", 0);
    } else {
      newStr = s21_insert(str, isNegative ? "-" : "", 0);
    }
    if (newStr != NULL) {
      s21_strcpy(result, newStr);
    }
    free(newStr);
  }
  free(str);
}
char *convertIntToStr(long long int number, int numberSystem) {
  int bufferSize = BUFFER_SIZE / 2;
  char *buffer = calloc(bufferSize, sizeof(char));
  int idx = 0;
  if (number < 0) {
    number *= -1;
  }
  do {
    int remainder = number % numberSystem;
    buffer[idx++] =
        (remainder < 10) ? ('0' + remainder) : ('a' + remainder - 10);
    number /= numberSystem;
  } while (number > 0 && idx < bufferSize - 1);
  buffer[idx] = '\0';

  // Переворачиваем строку в обратном порядке
  int start = 0;
  int end = idx - 1;

  while (start < end) {
    char temp = buffer[start];
    buffer[start] = buffer[end];
    buffer[end] = temp;
    ++start;
    --end;
  }
  return buffer;
}

int isZeroPrint(formatSpecifier *specific) {
  return specific->specifier == 'e' || specific->specifier == 'E' ||
         specific->specifier == 'f' || specific->specifier == 'g' ||
         specific->specifier == 'G';
}

void printSpace(char *result, formatSpecifier *specific) {
  int len = s21_strlen(result);
  int isZero = isZeroPrint(specific) && !specific->isFlagMinus;
  int spaceStrLen = specific->width - len;
  if (spaceStrLen > 0) {
    char spaceStr[spaceStrLen];
    s21_memset(spaceStr, isZero ? '0' : ' ', spaceStrLen);
    spaceStr[spaceStrLen] = '\0';
    if (specific->isFlagMinus) {
      char *res = s21_insert(result, spaceStr, s21_strlen(result));
      s21_strcpy(result, res);
    } else {
      char *res = s21_insert(result, spaceStr, 0);
      s21_strcpy(result, res);
    }
  }
}

// Метод для получения строки из шаблона
char *getStrFromTemplate(formatSpecifier *specific, va_list args) {
  char *result = calloc(BUFFER_SIZE, sizeof(char));
  switch (specific->specifier) {
    case 'c':
      write_c(result, specific, args);
      break;
    case 'd':
      write_d(result, specific, args);
      break;
    case 'i':
      /* code */
      break;
    case 'e':
      /* code */
      break;
    case 'E':
      /* code */
      break;
    case 'f':
      /* code */
      break;
    case 'g':
      /* code */
      break;
    case 'G':
      /* code */
      break;
    case 'o':
      /* code */
      break;
    case 'x':
      /* code */
      break;
    case 'X':
      /* code */
      break;
    case 'p':
      /* code */
      break;
    case 'n':
      /* code */
      break;
    case '%':
      /* code */
      break;
  }
  printSpace(result, specific);
  return result != NULL ? result : "";
}

int s21_sprintf(char *str, const char *format, ...) {
  const char *pattern =
      "%[-+ "
      "0#]*([0-9]*|[*])([.]([0-9]*|[*]))?(hl|ll|hh|[hlL])?[diouxXfFeEgGcspn%]";
  Match *matches = NULL;
  size_t numMatches = 0;
  extractMatches(format, pattern, &matches, &numMatches);
  int offset = 0;
  va_list args;
  va_start(args, format);
  for (size_t i = 0; i < numMatches; ++i) {
    printf("%.*s", matches[i].start - offset, format + offset);

    char template[255] = "";
    s21_memcpy(template, format + matches[i].start,
               matches[i].end - matches[i].start);
    formatSpecifier *specific = initFormatSpecifier(template, args);

    printFormatSpecifier(specific);
    printf("\n");

    // Вывод результата:
    char *result = getStrFromTemplate(specific, args);
    printf("!%s!\n", result);
    free(result);
    free(specific);
    offset = matches[i].end;
  }
  va_end(args);
  free(matches);
}

int main() {
  // Строка в которой происходит поиск шаблонов
  const char *format = "%- 30.15d";
  int param1 = 27123;
  double param2 = 1.123;
  char param3[] = "Hello";
  char param4 = 'h';
  char buff[256];
  s21_sprintf(buff, format, param1);

  char buffer[256];
  sprintf(buffer, format, param1);
  printf("\n!%s!\n", buffer);
  // int num = 9871;
  // char *res1 = convertIntToStr(num, 10);
  // char *res2 = convertIntToStr(num, 8);
  // char *res3 = convertIntToStr(num, 16);

  // printf("!%s!\n", res1);
  // printf("!%s!\n", res2);
  // printf("!%s!\n", res3);

  // free(res1);
  // free(res2);
  // free(res3);
  return 0;
}
