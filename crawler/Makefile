L=../lib
U=../utils

CFLAGS=-Wall -pedantic -std=c11 -I${U} -L${L} -g
LIBS=-lutils -lcurl

crawler:
				gcc $(CFLAGS) crawler.c $(LIBS) -o $@

crawler2:
				gcc $(CFLAGS) crawler2.c $(LIBS) -o $@

crawler3:
				gcc $(CFLAGS) crawler3.c $(LIBS) -o $@

crawler_step5:
				gcc $(CFLAGS) crawler_step5.c $(LIBS) -o $@

crawler_final:
				gcc $(CFLAGS) crawler_final.c $(LIBS) -o $@

clean:
	rm -f crawler crawler2 crawler3 crawler_step5 crawler_final
	rm -f ../test/*
