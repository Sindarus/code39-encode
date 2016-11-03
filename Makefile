all: do_code39 tests

code39.o: code39.c code39.h
	gcc -Wall -Wextra -g code39.c -c

do_code39: main.c code39.o
	gcc -Wall -Wextra -g main.c code39.o -o do_code39


tests: code39.o tests.c
	gcc -g -std=c99 -Wall -Wextra tests.c code39.o -lcunit -o tests
	

clean:
	rm *.o; rm do_code39
