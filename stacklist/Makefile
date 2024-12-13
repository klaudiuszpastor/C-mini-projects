flags = -O2 -Wall -std=c2x
ldflags =-lbu

.PHONY: all clean

all: clean stacklist

stacklist: stacklist.c
	$(CC) $(flags) $^ -o $@ $(ldflags)

stacklist.o: stacklist.c stacklist.h
	cc $(flags) -c $<

clean:
	rm -f *.o stacklist
