/* indexer.c --- 
1;95;0c * 
 * 
 * Author: Agampodi I. Abeysekara
 * Created: Sun Oct 25 11:25:16 2020 (-0400)
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


char* NormalizeWord(char *str);
bool searchfunc(void* elementp, const void* searchkeyp);
bool s(void* p, const void* key);
void sumwords(void *ep);
void indexCleanup(hashtable_t *index);
void wordDelete(void *word);


//global variable
int sum=0;

typedef struct word{
	char word[100];
	queue_t *qp;
} word_t;

typedef struct page{
	int pageid;
	int count;
} page_t;


int main(void) {
	webpage_t *w1= pageload(1, "../pages");
	word_t *wordsearch = NULL;
	queue_t *queuesearch = NULL;
	page_t *pagesearch = NULL;
	hashtable_t *ht = hopen(200);
	
	
	char *result;
	int pos=0;
	while ((pos = webpage_getNextWord(w1, pos, &result)) > 0 ) {
		if (strcmp(NormalizeWord(result), "") != 0) {
			if ((wordsearch = (word_t *)hsearch(ht, s, result, strlen(result))) != NULL){
				queuesearch = wordsearch->qp;
				pagesearch = (page_t *)qget(queuesearch);
				if(pagesearch->pageid == 1){
					pagesearch->count = pagesearch->count + 1;
					qput(queuesearch, (void *)pagesearch);
				}else{
					qput(queuesearch, (void *)pagesearch);
				}
				free(result);
			}else{
				word_t *wordpointer = (word_t *)malloc(sizeof(word_t));
				queue_t *queuep = qopen();
				page_t *pagepointer = (page_t *)malloc(sizeof(page_t));
				strcpy(wordpointer->word, result);
				pagepointer->pageid = 1;
				pagepointer->count = 1;
				qput(queuep, (void *)pagepointer);
				wordpointer->qp = queuep;
				hput(ht, (void *)wordpointer, wordpointer->word, strlen(wordpointer->word));
				free(result);
			}
		} else {
			free(result);
		  continue;
		}

	}


	indexsave(ht, 1, "../indexdir");
	
	//clean word structs out of hashtable and close it
	indexCleanup(ht);

	webpage_delete(w1);

	return 0;
}

void sumwords(void *ep){
	word_t *w = (word_t *)ep;
	page_t *p = NULL;
	queue_t *q = (queue_t *)w->qp;
	while ((p=(page_t *)qget(q)) != NULL){
	
		sum=sum + p->count;
		free(p);
	}
	return;
}

bool s(void* p, const void* key){

	word_t *searchw = (word_t*)p;
	char *w = searchw->word;

	if (strcmp(w, key) == 0){
		return true;
	}

	return false;
}
	
char* NormalizeWord(char *str) {
	int i=0;
	bool check= false;
	while (str[i] != '\0') {
		str[i]= tolower(str[i]);
		int ascii= (int) str[i];
		if (ascii >= 97 && ascii <= 122) {
			check= true;
		}
		else {
			check= false;
		}
		i++;
	}

	if (check == false || strlen(str) < 3) {
		return "";
	}
	return str;
}


void indexCleanup(hashtable_t *index){
	happly(index, wordDelete);
	hclose(index);
}

void wordDelete(void *currWord){
	qclose(((word_t*)currWord)->qp);
}
