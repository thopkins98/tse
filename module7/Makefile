L=../lib
U=../utils

CFLAGS=-Wall -pedantic -std=c11 -I${U} -L${L} -g
LIBS= -lutils -lcurl


all: step1_test test

step1_test:
			gcc $(CFLAGS) step1_test.c $(LIBS) -o $@

test1:
			gcc $(CFLAGS) test1.c $(LIBS) -o $@

test2:
			gcc $(CFLAGS) test2.c $(LIBS) -o $@

concurrent:
			gcc $(CFLAGS) concurrent.c $(LIBS) -o concurrent -lpthread

concurrent2_test1:
			gcc $(CFLAGS) concurrent2_test1.c $(LIBS) -o concurrent2_test1 -lpthread

concurrent2:
			gcc $(CFLAGS) concurrent2.c $(LIBS) -o concurrent2 -lpthread



utils:
			(cd ../utils; make clean)
			(cd ../utils; make all)

clean:
			rm -f step1_test test
