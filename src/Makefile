CC = gcc
FLAGS = -Werror -Wextra -Wall -g
TST_LIBS = $(shell pkg-config --libs check)

TEST_SOURCES = ./tests/*.c ./*.c

all:
	gcc *.c -g

test :
	$(CC) $(FLAGS) $(TEST_SOURCES) -o test $(TST_LIBS)

test : 
	-rm ./test
	$(CC) $(FLAGS) $(TEST_SOURCES) -o test $(TST_LIBS)
	./test

clean:
	rm test