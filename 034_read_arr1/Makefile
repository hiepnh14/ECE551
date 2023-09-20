CLFAGS=-std=gnu99 -pedantic -Wall
test: test.o
	gcc -o test test.o
test.0: test.c
	gcc $(CFLAGS) -c $<
.PHONY: clean
clean:
	rm -f test *.o *.c~ *.h~
