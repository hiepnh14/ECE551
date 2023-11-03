CCFLAGS=--std=gnu++98 -pedantic -Wall -Werror -ggdb3
sort: sort.o
	g++ -o sort $(CCFLAGS) sortLines.o

sort.o: sortLines.cpp
	g++ -c $(CCFLAGS) $<

clean:
	rm -f *.o  *~ sort

