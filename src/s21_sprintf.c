#include <ctype.h>
#include <regex.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_string.h"

// Структура для хранения совпадений
typedef struct {
  int start;
  int end;
} Match;

typedef struct {
  int isFlagPlus;   // указывает на флаг +
  int isFlagMinus;  // указывает на флаг -
  int isFlagZero;   // указывает на флаг 0
  int isFlagSpace;  // указывает на флаг ' '
  int isFlagSharp;  // указывает на флаг #
  int width;        //  указывает на ширину вывода
  int precision;    // указывает на точность
  int length_h;     // указывает на длинну h
  int length_l;     // указывает на длинну l
  int length_L;     // указывает на длинну L
  char specifier;   // указывает на спецификатор типа
} formatSpecifier;

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

// Подсчет количества вхождений подстроки в строку
int countSubStr(const char *str, const char *subStr) {
  int count = 0;
  size_t subStrLen = strlen(subStr);

  if (subStrLen == 0) {
    return -1;
  }

  const char *ptr = str;
  while ((ptr = strstr(ptr, subStr)) != NULL) {
    count++;
    ptr += subStrLen;
  }

  return count;
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
formatSpecifier *initFormatSpecifier(char *template, int *params,
                                     int paramsCount) {
  formatSpecifier *specific = calloc(1, sizeof(formatSpecifier));
  printf("template: %s\n", template);
  int offset = 1;
  fillFlags(template, &offset, specific);
  if (template[offset] == '*') {
    specific->width = params[0];
    offset++;
  } else {
    specific->width = getInt(template, &offset);
  }

  if (template[offset] == '.') {
    offset++;
    if (template[offset] == '*') {
      specific->precision = params[paramsCount - 1];
      offset++;
    } else {
      specific->width = getInt(template, &offset);
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
    int countParam = countSubStr(template, "*");
    int paramsForTemplate[2];
    for (int i = 0; i < countParam; i++) {
      paramsForTemplate[i] = va_arg(args, int);
    }
    formatSpecifier *specific =
        initFormatSpecifier(template, paramsForTemplate, countParam);

    printFormatSpecifier(specific);
    printf("\n");

    // Вывод результата:

    free(specific);
    offset = matches[i].end;
  }
  va_end(args);
  free(matches);
}

int printTemplate();

int main() {
  // Строка в которой происходит поиск шаблонов
  const char *str = "%Le";
  char buff[255];
  s21_sprintf(buff, str, 10, 20, 2);
  // char buffer[256];
  // char format[] = "%hld";
  // char format[] = "%hhd";
  // char format[] = "%lld";
  // char format[] = "%Lf";
  // char format[] = "%d";
  // int param = -123;
  // sprintf(buffer, format, param);
  // printf("!%s!\n", buffer);
  return 0;
}
