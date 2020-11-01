L=../lib
U=../utils

CFLAGS=-Wall -pedantic -std=c11 -I${U} -L${L} -g
LIBS=-lutils -lcurl


query:
			gcc $(CFLAGS) query.c $(LIBS) -o $@

query2:
			gcc $(CFLAGS) query2.c $(LIBS) -o $@
