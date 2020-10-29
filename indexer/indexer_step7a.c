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

typedef struct word{
	char word[100];
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
void indexCleanup(hashtable_t *index);
void wordDelete(void *word);
bool pageSearch(void* p, const void* key);

//global variable
int sum=0;

// expected usage: ./indexer <pagedir> <indexnm>
int main(const int argc, char *argv[]){
    // Argument checks
	if ( argc != 3 ) {
		printf("Wrong number of arguments\n");
		exit(1);
	}

	if ( strcmp(argv[1], "" ) == 0 )  {
		printf("Please enter a valid directory\n");
		exit(1);
		}

	if ( strcmp(argv[2], "" ) == 0 ) {
		printf("Please enter a valid index name\n");
		exit(1);
	}

    char filetest[50];
    sprintf(filetest, "%s/.crawler", argv[1]);
    //printf("%s", filetest);
    FILE *test;
	if ((test = fopen(filetest, "r")) == NULL){
		printf("directory is not readable or was not made by a crawler\n");
        exit(1);
	}
    fclose(test);

    int fileID = 1;
    //char crawlName[30];
    //sprintf(crawlName, "%s/%d", argv[1], fileID);
    //printf("%s", crawlName);

    hashtable_t *ht = hopen(200);
    word_t *wordsearch = NULL;
    queue_t *queuesearch = NULL;
    page_t *pagesearch = NULL;

    webpage_t *w1 = NULL;
    while((w1 = pageload(fileID, argv[1])) != NULL){
        //printf("scanning %s/%d\n", argv[1], fileID);
        char *result;
        int pos=0;
        while ((pos = webpage_getNextWord(w1, pos, &result)) > 0 ) {
            if (strcmp(NormalizeWord(result), "") != 0) {
                if ((wordsearch = (word_t *)hsearch(ht, s, result, strlen(result))) != NULL){
                    //printf("found repeat\n");
                    queuesearch = wordsearch->qp;
                    pagesearch = (page_t *)qsearch(queuesearch, pageSearch, &fileID);
                    if(pagesearch != NULL){
                        pagesearch->count = pagesearch->count + 1;
                    }else{

                        page_t *newPage = (page_t *)malloc(sizeof(page_t));
                        newPage->pageid = fileID;
                        newPage->count = 1;
                        qput(queuesearch, (void *)newPage);
                    }
    
                    free(result);
                }else{
                    //printf("new word\n");
                    word_t *wordpointer = (word_t *)malloc(sizeof(word_t));
                    queue_t *queuep = qopen();
                    page_t *pagepointer = (page_t *)malloc(sizeof(page_t));
                    strcpy(wordpointer->word, result);
                    pagepointer->pageid = fileID;
                    pagepointer->count = 1;
                    qput(queuep, (void *)pagepointer);
                    wordpointer->qp = queuep;
                    hput(ht, (void *)wordpointer, wordpointer->word, strlen(wordpointer->word));
                    free(result);
                    sum +=1;
                }
            } else {
                free(result);
                continue;
            }
        }
        fileID+=1;
        webpage_delete(w1);
    }
    int indexID = atoi(argv[2]);
    //save hashtable
    indexsave(ht, indexID, "../indexdir2");
    printf("Total Word Count from pages 1-%d: %d\n", fileID-1, sum);
    //clean word structs out of hashtable and close it
    indexCleanup(ht);
    webpage_delete(w1);
    

	//printf("Total Word Count from pages 1-%d: %d\n", 2, sum);
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

bool pageSearch(void* p, const void* key){
    page_t *pageToSearch = (page_t*)p;
    int pageID = pageToSearch->pageid;
    //printf("pageID = %d key= %d\n", pageID, *(int*)key);
    if(pageID == *(int*)key){
        return true;
    }
    return false;
}