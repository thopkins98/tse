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

typedef struct word{
	char *word;
	queue_t *qp;
} word_t;

typedef struct page{
	int pageid;
	int count;
} page_t;

char* NormalizeWord(char *str);
bool searchfunc(void* elementp, const void* searchkeyp);
bool s(void* p, const void* key);
void sumwords(void *ep);

//global variable
int sum=0;

int main(void) {
	webpage_t *w1= pageload(1, "../pages");
	word_t *wordpointer = (word_t *)malloc(sizeof(word_t));
	word_t *wordsearch = (word_t *)malloc(sizeof(word_t));
	hashtable_t *ht = hopen(100);
	queue_t *queuep = qopen();
	page_t *pagep = (page_t *)malloc(sizeof(page_t));
	
	char *result;
	int pos=0;
	while ((pos = webpage_getNextWord(w1, pos, &result)) > 0 ) {
		if (strcmp(NormalizeWord(result), "") != 0) {
			if ((wordsearch = (word_t *)hsearch(ht, s, result, strlen(result))) != NULL){
				queuep = wordsearch->qp;
				pagep = (page_t *)qget(queuep);
				if(pagep->pageid == 1){
					pagep->count = pagep->count + 1;
					qput(queuep, (void *)pagep);
				}else{
					qput(queuep, (void *)pagep);
				}
				
				free(result);
			}else{
				wordpointer->word = result;
				pagep->pageid = 1;
				pagep->count = 1;
				qput(queuep, (void *)pagep);
				wordpointer->qp = queuep;
				hput(ht, (void *)wordpointer, wordpointer->word, strlen(wordpointer->word));
				free(result);
			}
		}
	  else {
			free(result);
		  continue;
		}
		
	}

	free(wordpointer);
	webpage_delete(w1); 

	//report sum
	happly(ht, sumwords);
	printf("Total Word Count: %d\n", sum);
	
	return 0;
}

void sumwords(void *ep){
	word_t *w = (word_t *)ep;
	page_t *p = NULL;
	queue_t *q = (queue_t *)w->qp;
	while ((p=(page_t *)qget(q) != NULL){
		p = (page_t *)qget(q);
		sum=sum + p->count;
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
