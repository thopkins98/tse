L=../lib
U=../utils

CFLAGS=-Wall -pedantic -std=c11 -I${U} -L${L} -g
LIBS=-lutils -lcurl

all: indexer.c

indexer:
			gcc $(CFLAGS) indexer.c $(LIBS) -o $@

clean:
		rm -f indexer
