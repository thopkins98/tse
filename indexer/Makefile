L=../lib
U=../utils

CFLAGS=-Wall -pedantic -std=c11 -I${U} -L${L} -g
LIBS= -lutils -lcurl

# all: indexer indexer_step3 indexer_step4 indexer_step5 indexer_step6
all: clean utils iotest_6 indexer_step6

indexer:
			gcc $(CFLAGS) indexer.c $(LIBS) -o $@

indexer_step3:
			gcc $(CFLAGS) indexer_step3.c $(LIBS) -o $@

indexer_step4:
			gcc $(CFLAGS) indexer_step4.c $(LIBS) -o $@

indexer_step5:
			gcc $(CFLAGS) indexer_step5.c $(LIBS) -o $@

indexer_step6: 
			gcc $(CFLAGS) indexer_step6.c $(LIBS) -o $@

iotest_6:
			gcc $(CFLAGS) iotest_6.c $(LIBS) -o $@

indexer_step7:
			gcc $(CFLAGS) indexer_step7.c $(LIBS) -o $@

utils:
			(cd ../utils; make clean)
			(cd ../utils; make all)

clean:
		rm -f indexer indexer_step3 indexer_step4 indexer_step5 indexer_step6 iotest_6
