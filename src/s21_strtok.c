#include "s21_string.h"

char *s21_strtok(char *str, const char *delim) {
    static char *token = s21_NULL;
    if (str != s21_NULL)
        token = str;
    else if (token == s21_NULL)
        return s21_NULL;
    printf("%c", *(token+3));
    char *result = token;
    int len = s21_strchr(token, (int)*delim) - token;
    
    token += len;
    // if (*token != '\0')
    //     *(token++) = '\0';
    // else
    //     token = s21_NULL;

    return result;
}
