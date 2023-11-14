#include <stdarg.h>
#include <math.h>

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

void scanPattern(const char** str, struct Pattern pattern, va_list dest,
                 int* succ_cntr, const char* str_start, int* err);

int scanInt(const char** str, struct Pattern pattern, void* dest);

int scanHex(const char** str, struct Pattern pattern, void* dest);

int scanOct(const char** str, struct Pattern pattern, void* dest);

int scanFloat_Sci(const char** str, struct Pattern pattern, void* dest);

int scanFloat(const char** str, struct Pattern pattern, void* dest);