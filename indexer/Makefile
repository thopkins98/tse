L=../lib
U=../utils

CFLAGS=-Wall -pedantic -std=c11 -I${U} -L${L} -g
LIBS=-lutils -lcurl

all: indexer.c indexer_step3.c indexer_step4.c

indexer:
			gcc $(CFLAGS) indexer.c $(LIBS) -o $@

indexer_step3:
			gcc $(CFLAGS) indexer_step3.c $(LIBS) -o $@

indexer_step4:
			gcc $(CFLAGS) indexer_step4.c $(LIBS) -o $@

clean:
		rm -f indexer indexer_step3.c indexer_step4.c
