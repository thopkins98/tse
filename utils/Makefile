CFLAGS=-Wall -pedantic -std=c11 -I. -g

OFILES=queue.o hash.o webpage.o pageio.o indexio.o lqueue.o

all: $(OFILES)
	ar cr ../lib/libutils.a $(OFILES)
%.o:	%.c %.h
	gcc $(CFLAGS) -c $<

lqueue.o: lqueue.c lqueue.h
	gcc $(CFLAGS) -c $<

clean:
				rm -f indexio.o
				rm -f webpage.o
				rm -f pageio.o
				rm -f lqueue.o
