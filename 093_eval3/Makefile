CFLAGS = std-gnu++98 -pedantic -Wall -ggdb3 -Werror
PROGS=cyoa-step1 #cyoa-step2 cyoa-step3 cyoa-step4
OBJS=$(patsubst %,%.o,$(PROGS)) cyoa.o
all: $(PROGS)
cyoa-step%: cyoa-step%.o cyoa.o
	g++ -o $@ $^
%.o: %.cpp %.hpp
	g++ $(CPPFLAGS) -c $<
.PHONY: clean
clean:
	rm -f *~ $(PROGS) $(OBJS)
