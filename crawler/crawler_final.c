/* crawler3.c --- 
 * 
 * 
 * Author: Agampodi I. Abeysekara
 * Created: Sun Oct 18 17:31:33 2020 (-0400)
 * Version: 
 * 
 * Description: 
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "webpage.h"
#include "hash.h"
#include "queue.h"
#include <string.h>
#include <stdint.h>

bool s(void* p, const void* key);
int32_t pagesave(webpage_t *pagep, int id, char *dirname);
void crawler(char* seedURL, char* pageDirectory, int maxDepth);
void pageScanner(webpage_t* page, queue_t* toVisit, hashtable_t* visited);
void cleanHashtable(void* ep);

// usage: crawler <seedurl> <pagedir> <maxdepth>
int main(const int argc, const char *argv[]){

	//Check that three inputs are provided
	if (argc != 4){
		fprintf(stderr, "Invalid Number of Arguments\n");
		exit(EXIT_FAILURE);
	}

        char* seedURL = malloc(sizeof(char)* strlen(argv[1])+1);
        char* pageDirectory = malloc(sizeof(char)* (strlen(argv[2])+strlen("/.crawler"))+1);
	    char* pageDirectory_clean = malloc(sizeof(char)* strlen(argv[2])+1);

        strcpy(seedURL, argv[1]);
        strcpy(pageDirectory, argv[2]);
	    strcat(pageDirectory, "/.crawler");
	    strcpy(pageDirectory_clean, argv[2]);

	// Check that maxDepth is above 0
	if (atoi(argv[3]) < 0){
		fprintf(stderr, "maxDepth %u is invalid.\n", atoi(argv[2]));
		free(pageDirectory);
        free(pageDirectory_clean);
		free(seedURL);
		exit(EXIT_FAILURE);
	}
	// Check that seed URL is valid and internal
	if (!IsInternalURL(seedURL)){
		fprintf(stderr, "%s is not internal or may be invalid\n", argv[1]);
		free(pageDirectory);
        free(pageDirectory_clean);
        free(seedURL);
		exit(EXIT_FAILURE);
	}
	// Check that pageDirectory exists and is writable
	FILE* fp;
	if ((fp = fopen(pageDirectory, "w")) == NULL){
		fprintf(stderr, "%s either does not exist or is not writable\n", argv[2]);
		free(pageDirectory);
        free(pageDirectory_clean);
        free(seedURL);
		exit(EXIT_FAILURE);
	}
	fclose(fp);

	crawler(seedURL, pageDirectory_clean, atoi(argv[3]));

	free(pageDirectory);
	free(pageDirectory_clean);
    free(seedURL);

	exit(EXIT_SUCCESS);

}

void crawler(char* seedURL, char* pageDirectory, int maxDepth){
	webpage_t *w1= webpage_new(seedURL, 0, NULL);
	queue_t *pagequeue= qopen();
	hashtable_t *hasht= hopen(5);
    qput(pagequeue, w1);
    hput(hasht, (void *)w1, seedURL, strlen(seedURL));
    

    int pageID = 1;
    webpage_t* curr;
    while((curr = qget(pagequeue)) != NULL){
        if(!webpage_fetch(curr)){
			fprintf(stderr, "Unable to fetch data for %s\n", webpage_getURL(curr));
		}
        else{
            pagesave(curr, pageID, pageDirectory);
        }
        if(webpage_getDepth(curr) < maxDepth){
            pageScanner(curr, pagequeue, hasht);
        }
        pageID+=1;
    }

    happly(hasht, cleanHashtable);
	qclose(pagequeue);
    free(hasht);
 
}

void pageScanner(webpage_t* page, queue_t* toVisit, hashtable_t* visited){
    printf("Scannning %s\n", webpage_getURL(page));
    int pos=0;
    char *result;
	while ((pos= webpage_getNextURL(page, pos, &result)) >0) {
		printf("Found url: %s\n", result);
        if (!NormalizeURL(result)){
			fprintf(stderr, "could not normalize URL\n");
		} 
		else if(!IsInternalURL(result)){
			fprintf(stderr, "URL is not internal\n");
        }
		else if(hsearch(visited, s, result, strlen(result)) != NULL){
			fprintf(stderr, "URL was already visited\n");
		}
        else{
			webpage_t* newPage = webpage_new(result, webpage_getDepth(page)+1, NULL);
            qput(toVisit, (void *) newPage);
            hput(visited, (void *) newPage, result, strlen(result));
        }
        free(result);
	}
}

bool s(void* p, const void* key) {


	char *url = webpage_getURL((webpage_t *) p);
	
	if (strcmp(url, key) == 0 ) {
		return true;
	}
	return false;
}

int32_t pagesave(webpage_t *pagep, int id, char *dirname){
    printf("Saving %s\n", webpage_getURL(pagep));
	FILE *fp;
	char fname[12]; //10
	sprintf(fname, "%s/%d", dirname, id);

	fp = fopen(fname, "w+");
	fprintf(fp, "%s \n%d \n%d \n%s \n",
					webpage_getURL(pagep),
					webpage_getDepth(pagep),
					webpage_getHTMLlen(pagep),
					webpage_getHTML(pagep));

	fclose(fp);
	return 0;
}


void cleanHashtable(void* ep){
    webpage_delete((webpage_t*)ep);
}
