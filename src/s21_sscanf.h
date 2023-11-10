#include <stdarg.h>

struct Pattern {
  int isChar;
  int skipping;
  int width;
  char lengh;
  char sym;
};

struct PatternVec {
  int size;
  int sizeArgs;
  int capacity;
  struct Pattern* data;
};

int s21_sscanf(const char* str, const char* format, ...);

void getPatterns(struct PatternVec* patterns, const char* format);

void scanPattern(const char** str, struct Pattern pattern, va_list dest, int* succ_cntr, int* err);

void scanInt(const char** str, struct Pattern pattern, int* dest);