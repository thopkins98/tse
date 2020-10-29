/* 
 * pageio.c --- saving and loading crawler webpage files
 * 
 * Author: Stephen Taylor
 * Created: Fri Oct 19 08:30:15 2018 (-0400)
 * Version: 1.0
 * 
 * Description: pagesave saves an existing webpage to a file with a
 * numbered name (e.g. 1,2,3 etc); pageload creates a new page by
 * loading a numbered file. For pagesave, the directory must exist and
 * be writable; for loadpage it must be readable.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <unistd.h>
#include <webpage.h>
#include "hash.h"
#include "queue.h"
#include "indexio.h"

//global variable
FILE *fp;

static void a(void* ep);

typedef struct word{
	char *word;
	queue_t *qp;
} word_t;

typedef struct page{
	int pageid;
	int count;
} page_t;

/*
 * pagesave -- save the page in filename id in directory dirnm
 *
 * returns: 0 for success; nonzero otherwise
 *
 * The suggested format for the file is:
 *   <url>
 *   <depth>
 *   <html-length>
 *   <html>
 */
int32_t indexsave(hashtable_t *index, int id, char *dirnm){
	printf("into index save");
	char fname[100];
	sprintf(fname, "%s/%d", dirnm, id);
	printf("about to open file");
	if ((fp = fopen(fname, "w")) == NULL){
		printf("failed opening");
	}
	//fp = fopen(fname, "w+");
	printf("opened file");
	
	happly(index, a);
	

	fclose(fp);
	
	return 0;
}

static void a(void* ep){
	//char lineentry[100];
	word_t *w = (word_t *)ep;
	char *key = w->word;
	page_t *p = NULL;
	queue_t *q = w->qp;
	fprintf(fp, "%s: ", key);
	while ((p=(page_t *)qget(q)) != NULL){
		printf("Pageid: %d     WCount: %d\n", p->pageid, p->count);
		fprintf(fp, "%d/%d ", p->pageid, p->count);
	}
	fprintf(fp, "\n");

	return;
}

/* 
 * pageload -- loads the numbered filename <id> in direcory <dirnm>
 * into a new webpage
 *
 * returns: non-NULL for success; NULL otherwise
 */
	hashtable_t* indexload(int id, char *dirnm){
		
		hashtable_t *ht = hopen(200);

		char fname[12];
		sprintf(fname, "%s/%d", dirnm, id);
		
		FILE *input2= fopen(fname, "r");
		printf("opened file");

		char *wordp = NULL;
		int pageid;
		int count;
		while (fscanf(input2, "%s", wordp) != EOF){
			printf("%s", wordp);
			word_t *wpoint = (word_t *)malloc(sizeof(word_t));
			queue_t *qp = qopen();
			wpoint->word = wordp;
			wpoint->qp = qp;
			while(fscanf(input2, "%d %d", &pageid, &count) !=0){
				page_t *p = (page_t *)malloc(sizeof(page_t));
				p->pageid=pageid;
				p->count = count;
				qput(qp, (void *)p);
			}
			hput(ht, (void *)wpoint, wpoint->word, strlen(wpoint->word));
		}
		
		return ht;

	}
