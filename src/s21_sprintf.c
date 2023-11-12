#include "s21_string.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

// Структура для хранения совпадений
typedef struct {
    int start;
    int end;
} Match;

void extractMatches(const char *input, const char *pattern, Match **matches, size_t *numMatches) {
    regex_t regex;
    int ret;

    // Компилируем регулярное выражение
    ret = regcomp(&regex, pattern, 0);
    if (ret != 0) {
        char error_message[100];
        regerror(ret, &regex, error_message, sizeof(error_message));
        fprintf(stderr, "Error compiling regex: %s\n", error_message);
        return;
    }

    regmatch_t match;
    int offset = 0;

    while (1) {
        ret = regexec(&regex, input + offset, 1, &match, 0);

        if (ret == REG_NOMATCH) {
            break; // Совпадений больше нет
        }

        // Извлечение совпадения из строки
        int start = match.rm_so + offset;
        int end = match.rm_eo + offset;

        // Расширяем массив совпадений
        *matches = realloc(*matches, (*numMatches + 1) * sizeof(Match));
        (*matches)[*numMatches].start = start;
        (*matches)[*numMatches].end = end;
        (*numMatches)++;

        offset = end; // Устанавливаем новый сдвиг для поиска следующего совпадения
    }

    regfree(&regex);
}

int main() {
    // Строка в которой происходит поиск шаблонов
    const char *input = "%..d;;FDSDF%.f %d %+++++- 123123.123Ld  %+++++- 123123.3d %+++++- 123123123.0f ";
    
    //  Паттерн для поиска шаблонов  sprintf 
    const char *pattern = "%[-+ 0#]*[0-9]*\\([.][0-9]*\\)\\?[hlL]\\?[diouxXfFeEgGcspn%]";

    Match *matches = NULL;
    size_t numMatches = 0;

    extractMatches(input, pattern, &matches, &numMatches);

    // Выводим найденные совпадения
    for (size_t i = 0; i < numMatches; ++i) {
        printf("Match %zu: %.*s\n", i + 1, matches[i].end - matches[i].start, input + matches[i].start);
    }

    // Освобождаем память
    free(matches);


    // char buff[255];
    // char format[] = "%.s";
    // char param[] = "123456789";
    // sprintf(buff, format, param);
    // printf("\n!%s!\n", buff);

    return 0;
}
