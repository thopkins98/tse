L=../lib
U=../utils

CFLAGS=-Wall -pedantic -std=c11 -I${U} -L${L} -g
LIBS=-lutils -lcurl

all: query query2 query3 query4 query5

query:
			gcc $(CFLAGS) query.c $(LIBS) -o $@

query2:
			gcc $(CFLAGS) query2.c $(LIBS) -o $@

query3:
			gcc $(CFLAGS) query3.c $(LIBS) -o $@

query4:
			gcc $(CFLAGS) query4.c $(LIBS) -o $@

query5:
			gcc $(CFLAGS) query5.c $(LIBS) -o $@

clean:
			rm -f query query2 query3 query4 query5
