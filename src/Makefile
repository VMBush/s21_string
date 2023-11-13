CC = gcc
FLAGS = -Werror -Wextra -Wall -g
TST_LIBS = $(shell pkg-config --libs check) #-lcheck -I/usr/local/include

TEST_SOURCES = ./tests/*.c ./*.c

all:
	gcc *.c -g

test :
	$(CC) $(FLAGS) $(TEST_SOURCES) -o test $(TST_LIBS)

runTest : 
	-rm ./test
	$(CC) $(FLAGS) $(TEST_SOURCES) -o test $(TST_LIBS)
	./test

s21_string.a:
	$(CC) $(FLAGS) -c s21_memchr.c -o s21_memchr.o
	$(CC) $(FLAGS) -c s21_memcmp.c -o s21_memcmp.o
	$(CC) $(FLAGS) -c s21_memcpy.c -o s21_memcpy.o
	$(CC) $(FLAGS) -c s21_memmove.c -o s21_memmove.o
	$(CC) $(FLAGS) -c s21_memset.c -o s21_memset.o
	$(CC) $(FLAGS) -c s21_strcat.c -o s21_strcat.o
	$(CC) $(FLAGS) -c s21_strchr.c -o s21_strchr.o
	$(CC) $(FLAGS) -c s21_strcmp.c -o s21_strcmp.o
	$(CC) $(FLAGS) -c s21_strcpy.c -o s21_strcpy.o
	$(CC) $(FLAGS) -c s21_strcspn.c -o s21_strcspn.o
	$(CC) $(FLAGS) -c s21_strlen.c -o s21_strlen.o
	$(CC) $(FLAGS) -c s21_strncmp.c -o s21_strncmp.o
	$(CC) $(FLAGS) -c s21_strncpy.c -o s21_strncpy.o
	$(CC) $(FLAGS) -c s21_strpbrk.c -o s21_strpbrk.o
	$(CC) $(FLAGS) -c s21_strrchr.c -o s21_strrchr.o
	$(CC) $(FLAGS) -c s21_strspn.c -o s21_strspn.o
	$(CC) $(FLAGS) -c s21_strstr.c -o s21_strstr.o
	$(CC) $(FLAGS) -c s21_strtok.c -o s21_strtok.o
	$(CC) $(FLAGS) -c s21_strerror.c -o s21_strerror.o
	$(CC) $(FLAGS) -c s21_strncat.c -o s21_strncat.o
	$(CC) $(FLAGS) -c s21_insert.c -o s21_insert.o
	$(CC) $(FLAGS) -c s21_to_lower.c -o s21_to_lower.o
	# $(CC) $(FLAGS) -c s21_to_upper.c -o s21_to_upper.o
	# $(CC) $(FLAGS) -c s21_trim.c -o s21_trim.o
	# $(CC) $(FLAGS) -c s21_sprintf.c -o s21_sprintf.o
	# $(CC) $(FLAGS) -c s21_sscanf.c -o s21_sscanf.o
	ar rcs s21_string.a s21_str*.o s21_mem*.o

clean:
	rm test *.o *.a