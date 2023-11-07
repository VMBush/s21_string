CC = gcc
FLAGS = -Werror -Wextra -Wall
TST_LIBS = $(shell pkg-config --libs check)

TEST_SOURCES = ./tests/*.c ./*.c

all:
	gcc *.c

test:
	$(CC) $(FLAGS) $(TEST_SOURCES) -o test $(TST_LIBS)
