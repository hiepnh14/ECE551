testing: search.o test-bsearch.o
	g++ -o testing search.o test-bsearch.o
search.o: search.cpp function.h
	g++ -std=gnu++98 -pedantic -Wall -Werror -c search.cpp
test-bsearch.o: test-bsearch.cpp function.h
	g++ -std=gnu++98 -pedantic -Wall -Werror -c test-bsearch.cpp

.PHONY: clean
clean:
	rm -f testing *~ %.c
