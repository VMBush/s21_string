#include <string.h>

#include "s21_string.h"


char *s21_strtok(char *str, const char *delim) {
  static char *token = s21_NULL;
  if (str != s21_NULL)
    token = str;
  else if (token == s21_NULL)
    return s21_NULL;

  // skip all delims
  token += s21_strspn(token, delim);

  // check if part is found
  char *beginniig;
  if (*token == '\0') {
    beginniig = s21_NULL;
  } else {
    beginniig = token;
    token += strcspn(token, delim);
  }

  // check if there is end of line
  if (*token != '\0') {
    *token = '\0';
    token++;
  } else {
    token = s21_NULL;
  }

  return beginniig;
}
