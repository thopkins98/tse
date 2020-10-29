/* indexer.c --- 
1;95;0c1;95;0c1;95;0c1;95;0c1;95;0c1;95;0c1;95;0c1;95;0c1;95;0c1;95;0c * 
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
#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>



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


int main(int argc, const char* argv[]) {

	printf("usage: indexer <pagedir> <indexnm>\n");

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

	char *p;
	int num;
	errno = 0;

	long conv= strtol(argv[2], &p, 10);

	if (errno !=0 || *p != '\0' || conv > INT_MAX) {
	 printf("Invalid index name\n");
	 exit(1);
	}

	num = conv;
	
	//printf("%d\n", num);
	// Checking if the directory exists
	
	struct stat dir;
	int err = stat(argv[1], &dir);
	if (err == -1) {
		if (ENOENT == errno) {
			printf("The page directory does not exist.\n");
			exit(1);
		}
		else {
			perror("stat");
			exit(1);
		}
	}
	else {
			if(S_ISDIR(dir.st_mode)) {
				printf("------------------------------>\n");
			}
			else {
				printf("%s exists but is not a directory.\n", argv[1]);
				exit(1);
			}
	}

	//Looping through all files in the directory and adding it to the hashtable
	DIR *directory;
	struct dirent* file;
	directory= opendir(argv[1]);
	if (directory == NULL) {
		printf("Null directory.\n");
		exit(1);
	}

	//int filename=1;
	queue_t *queuesearch = NULL;
	page_t *pagesearch = NULL;
	hashtable_t *ht = hopen(200);
	word_t *wordsearch = NULL;
	//webpage_t *w1= NULL;
	int filename=1;
	while ((file=readdir(directory)) != NULL) {
		printf("Loading page\n");
		webpage_t *w1=NULL;

		// Converting filename to int
		//char *p;
		//int num;
		//long conv= strtol(file->d_name, &p, 10);
		//num=conv;
		w1= pageload(filename, (char *)  argv[1]);
	
		char *result;
		int pos=0;
		printf("Loading into index data structure.\n");
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
			filename++;
		}
		printf("Deallocating memeory for webpage\n");
		webpage_delete(w1);
	}

	//Saving index
	printf("Saving to index file  %d\n", num);
	indexsave(ht, num, "../indexdir2");
	
	//clean word structs out of hashtable and close it
	indexCleanup(ht);

	//webpage_delete(w1);
	free(directory);

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
