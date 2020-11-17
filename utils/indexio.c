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
#include "lhash.h"
#include "indexio.h"

//global variable
FILE *fp;

static void wordSave(void* ep);

typedef struct word{
	char word[100];
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

	char fname[20];
	sprintf(fname, "%s/%d", dirnm, id);

	fp = fopen(fname, "w+");
	happly(index, wordSave);
	

	fclose(fp);
	return 0;
}

static void wordSave(void* ep){
	//char lineentry[100];
	word_t *w = (word_t *)ep;
	char *key = w->word;
	page_t *p = NULL;

	queue_t *q = w->qp;
	fprintf(fp, "%s ", key);
	//printf("got word %s\n", key);
	while ((p=(page_t *)qget(q)) != NULL){
		//printf("Pageid: %d     WCount: %d\n", p->pageid, p->count);
		fprintf(fp, "%d %d ", p->pageid, p->count);
		free(p);
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
	
	char fname[20];
	sprintf(fname, "%s/%d", dirnm, id);
	
	FILE *input2;
	if ((input2 = fopen(fname, "r")) == NULL){
		printf("failed to open file\n");
		return NULL;
	}

	char wordp[100];
	int pageid;
	int count;
	while (!feof(input2)){
			fscanf(input2, "%s", wordp);
			word_t *wpoint = (word_t *)malloc(sizeof(word_t));
			queue_t *qp = qopen();
			strcpy(wpoint->word, wordp);
			wpoint->qp = qp;
			while(fscanf(input2, "%d %d", &pageid, &count) ==2){
				page_t *p = (page_t *)malloc(sizeof(page_t));
				p->pageid=pageid;
				p->count = count;
				qput(qp, (void *)p);
			}
			hput(ht, (void *)wpoint, wpoint->word, strlen(wpoint->word));
	}
	fclose(input2);
	return ht;

}


/*
 * lockindexsave -- version of indexsave that will work with a locked
 * hash table used while multithreading the indexer.
 *
 * returns: 0 for success; nonzero otherwise
 */
int32_t lockindexsave(lhash_t *index, int id, char *dirnm){

	char fname[20];
	sprintf(fname, "%s/%d", dirnm, id);

	fp = fopen(fname, "w+");
	lhapply(index, wordSave);
	

	fclose(fp);
	return 0;
}


/*
 * lockindexload -- version of indexload that will work with a locked
 * hash table used while multithreading the indexer.
 *
 * returns: non-NULL for success; NULL otherwise
 */
lhash_t* lockindexload(int id, char *dirnm){
	
	
	hashtable_t *ht = lhopen();
	
	char fname[20];
	sprintf(fname, "%s/%d", dirnm, id);
	
	FILE *input2;
	if ((input2 = fopen(fname, "r")) == NULL){
		printf("failed to open file\n");
		return NULL;
	}

	char wordp[100];
	int pageid;
	int count;
	while (!feof(input2)){
			fscanf(input2, "%s", wordp);
			word_t *wpoint = (word_t *)malloc(sizeof(word_t));
			queue_t *qp = qopen();
			strcpy(wpoint->word, wordp);
			wpoint->qp = qp;
			while(fscanf(input2, "%d %d", &pageid, &count) ==2){
				page_t *p = (page_t *)malloc(sizeof(page_t));
				p->pageid=pageid;
				p->count = count;
				qput(qp, (void *)p);
			}
			lhput(ht, (void *)wpoint, wpoint->word, strlen(wpoint->word));
	}
	fclose(input2);
	return ht;

}