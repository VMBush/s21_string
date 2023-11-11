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

clean:
	rm test