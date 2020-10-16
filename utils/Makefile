CFLAGS=-Wall -pedantic -std=c11 -I. -g

OFILES=queue.o hash.o webpage.o

all: $(OFILES)
			ar cr ../lib/libutils.a $(OFILES)


webpage.o: webpage.c webpage.h
						gcc $(CFLAGS) -c webpage.c


clean:
				rm -f *.o webpage
