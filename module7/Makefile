L=../lib
U=../utils

CFLAGS=-Wall -pedantic -std=c11 -I${U} -L${L} -g
LIBS= -lutils -lcurl


all: step1_test test

step1_test:
			gcc $(CFLAGS) step1_test.c $(LIBS) -o $@

test1:
			gcc $(CFLAGS) test1.c $(LIBS) -o $@

concurrent:
			gcc $(CFLAGS) concurrent.c $(LIBS) -o concurrent -lpthread

utils:
			(cd ../utils; make clean)
			(cd ../utils; make all)

clean:
			rm -f step1_test test
