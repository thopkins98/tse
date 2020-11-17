L=../lib
U=../utils

CFLAGS=-Wall -pedantic -std=c11 -I${U} -L${L} -g
LIBS= -lutils -lcurl


all: step1_test test1 indexer_multi ctest3 ctest4 ctest5 ctest6 ctest7 concurrent2  ctest9

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

indexer_multi:
			gcc $(CFLAGS) indexer_multi.c $(LIBS) -o $@ -lpthread

ctest3:
			gcc $(CFLAGS) ctest3.c $(LIBS) -o ctest3 -lpthread

ctest4:
			gcc $(CFLAGS) ctest4.c $(LIBS) -o ctest4 -lpthread

ctest5:
			gcc $(CFLAGS) ctest5.c $(LIBS) -o ctest5 -lpthread

ctest6:
			gcc $(CFLAGS) ctest6.c $(LIBS) -o ctest6 -lpthread

ctest7:
			gcc $(CFLAGS) ctest7.c $(LIBS) -o ctest7 -lpthread

ctest8:
			gcc $(CFLAGS) ctest8.c $(LIBS) -o ctest8 -lpthread

ctest9:
			gcc $(CFLAGS) ctest9.c $(LIBS) -o ctest9 -lpthread


utils:
			(cd ../utils; make clean)
			(cd ../utils; make all)

clean:
			rm -f step1_test test indexer_multi ctest3 ctest4 ctest5 ctest6 cttest7 ctest9 concurrent2
