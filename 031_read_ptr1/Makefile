CFLAGS=-std=gnu99 -pedantic -Wall
test: test.o
	gcc -o test test.o
test.o: test.c
	gcc -std=gnu99 -pedantic -Wall -c test.c
.PHONY: clean
clean:
	rm -f test *.o *.c~ *.h~
