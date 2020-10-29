/* test_6.c --- 
 * 
 * 
 * Author: Robert B. Noone III
 * Created: Thu Oct 29 00:54:16 2020 (-0400)
 * Version: 
 * 
 * Description: 
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include "webpage.h"
#include "pageio.h"
#include <string.h>
#include <ctype.h>
#include "hash.h"
#include "queue.h"
#include "indexio.h"

typedef struct word{
	char word[100];
	queue_t *qp;
} word_t;

typedef struct page{
	int pageid;
	int count;
} page_t;

void indexCleanup(hashtable_t *index);
void wordDelete(void *word);

int main(void) {
    hashtable_t* indexIn = NULL;
    // Import index from file
    indexIn = indexload(1, "../indexdir");
    // Export the same index to a different directory
    indexsave(indexIn, 1, "../indexcomp");

    indexCleanup(indexIn);
    return 0;
}


void indexCleanup(hashtable_t *index){
	happly(index, wordDelete);
	hclose(index);
}

void wordDelete(void *currWord){
	qclose(((word_t*)currWord)->qp);
}