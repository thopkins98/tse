/* indexer_multi.c --- 
 * 
 * 
 * Author: Robert B. Noone III
 * Created: Mon Nov 16 05:25:45 2020 (-0400)
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
#include <pthread.h>
#include "hash.h"
#include "queue.h"
#include "indexio.h"
#include "lhash.h"
#include "lqueue.h"

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
void *indexer(void *crawlerDirIn);

//global variable
int sum=0;
lqueue_t *pagesToIndex;
lhash_t *ht;
pthread_mutex_t mutx;

// expected usage: ./indexer <pagedir> <indexnm> <threads>
int main(const int argc, char *argv[]){
    // Argument checks
	if ( argc != 4 ) {
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

    if(atoi(argv[3]) <= 0){
        printf("Invalid number of threads, must be 1 or more\n");
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



    // Iterate through directory and store indicies of all pages in a queue
    pagesToIndex = lqopen();
    FILE* dirCount;
    int fileID = 1; 
    char *crawlFileName = malloc(sizeof(char)*20);
    sprintf(crawlFileName, "%s/%d", argv[1], fileID);
    while((dirCount = fopen(crawlFileName, "r")) != NULL){
        int* IDtemp = malloc(sizeof(int));
        *IDtemp = fileID;
        lqput(pagesToIndex, IDtemp);
        fileID++;
        sprintf(crawlFileName, "%s/%d", argv[1], fileID);
        fclose(dirCount);
    }
    free(crawlFileName);
    //printf("Made queue of filenames\n");


    ht = lhopen(); //Open global locked hashtable
    pthread_mutex_init(&mutx, NULL);

    // Create specified number of threads
    int numThreads = atoi(argv[3]);
    pthread_t threads[numThreads];
    for(int i = 0; i < numThreads; i++){
        if(pthread_create(&threads[i], NULL, indexer, argv[1])!=0){
            exit(EXIT_FAILURE);
        }
    }
    printf("created %d threads\n", numThreads);
    // Join all threads when finished
    for(int i = 0; i < numThreads; i++){
        if(pthread_join(threads[i], NULL)!=0){
            exit(EXIT_FAILURE);
        }
    }
    printf("joined %d threads\n", numThreads);

    int indexID = atoi(argv[2]);
    //save hashtable
    lockindexsave(ht, indexID, "../indexdir");
    printf("Total Word Count from pages 1-%d: %d\n", fileID-1, sum);
    //clean word structs out of hashtable and close it
    indexCleanup(ht);
    lqclose(pagesToIndex);
    pthread_mutex_destroy(&mutx);

	return 0;
}

void *indexer(void *crawlerDirIn){
    char crawlerDir[20];
    strcpy(crawlerDir, (char*)crawlerDirIn);

    word_t *wordsearch = NULL;
    queue_t *queuesearch = NULL;
    page_t *pagesearch = NULL;


    webpage_t *w1 = NULL;

    int currFile;
    int *currFileAdd;
    while((currFileAdd = (int*)lqget(pagesToIndex)) != NULL){
        currFile = *currFileAdd;
        w1 = pageload(currFile, crawlerDir);
        //printf("scanning %s/%d\n", argv[1], fileID);
        char *result;
        int pos=0;
        while ((pos = webpage_getNextWord(w1, pos, &result)) > 0 ) {
            if (strcmp(NormalizeWord(result), "") != 0) {
                if ((wordsearch = (word_t *)lhsearch(ht, s, result, strlen(result))) != NULL){
                    //printf("found repeat\n");
                    queuesearch = wordsearch->qp;
                    pagesearch = (page_t *)qsearch(queuesearch, pageSearch, &currFile);
                    if(pagesearch != NULL){
                        pagesearch->count = pagesearch->count + 1;
                    }else{

                        page_t *newPage = (page_t *)malloc(sizeof(page_t));
                        newPage->pageid = currFile;
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
                    pagepointer->pageid = currFile;
                    pagepointer->count = 1;
                    qput(queuep, (void *)pagepointer);
                    wordpointer->qp = queuep;
                    lhput(ht, (void *)wordpointer, wordpointer->word, strlen(wordpointer->word));
                    free(result);
                    pthread_mutex_lock(&mutx);
                    sum +=1;
                    pthread_mutex_unlock(&mutx);
                }
            } else {
                free(result);
                continue;
            }
        }
        webpage_delete(w1);
        free(currFileAdd);
    }
    return crawlerDirIn;
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
	lhapply(index, wordDelete);
	lhclose(index);
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