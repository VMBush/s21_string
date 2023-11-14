#ifndef S21_SPRINTF
#define S21_SPRINTF

#include <ctype.h>
#include <regex.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

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

void fillFlags(char *template, int *offset, formatSpecifier *specific);
void fillLength(char *template, int *offset, formatSpecifier *specific);
int getInt(char *template, int *offset);
formatSpecifier *initFormatSpecifier(char *template, va_list args);
void extractMatches(const char *input, const char *pattern, Match **matches,
                    size_t *numMatches);
void write_c(char *result, formatSpecifier *specific, va_list args);
void write_d(char *result, formatSpecifier *specific, va_list args);

char *convertIntToStr(long long int number, int numberSystem);

int isZeroPrint(formatSpecifier *specific);
void printSpace(char *result, formatSpecifier *specific);
char *getStrFromTemplate(formatSpecifier *specific, va_list args);

int s21_sprintf(char *str, const char *format, ...);
#endif