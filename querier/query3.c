/* query.c --- 
1;95;0c1;95;0c1;95;0c1;95;0c1;95;0c * 
 * 
 * Author: Agampodi I. Abeysekara
 * Created: Sat Oct 31 11:47:35 2020 (-0400)
 * Version: 
 * 
 * Description: This program acts as the query interface. It prints out a parsed version of the query. 
 * 
1;95;0c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include "pageio.h"
#include "indexio.h"
#include "hash.h"
#include "queue.h"
#include "webpage.h"

bool s(void* p, const void* key);

typedef struct doc{
	int docid;
	int rank;
	int totalmatches;
}doc_t;

typedef struct word{
	char word[100];
	queue_t *qp;
}word_t;

typedef struct page{
	int pageid;
	int count;
}page_t;

int main(void) {

	//hashtable_t *index1 = indexload(1, "../indexdir2");

	//doc_t *docqueue[10];

	char buffer[100];

	
	printf(">");
	while(fgets(buffer, 100, stdin)) {
		if (strcmp(buffer, "\n") == 0) {
			printf(">");
		}

		char *word;
		char *ptr= buffer;

		char *word_arr[1024];
		
		int count=0;
		int punc_check=0;
		int paramcount = 0;
		doc_t *docqueue[10] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};
		hashtable_t *index1 = indexload(1, "../indexdir2");
		
		while ((word= strtok(ptr, " \t\n"))) {
			ptr= NULL;

			for (int i=0; i< strlen(word); i++) {
				char c= word[i];
			
				if (((int) c >= 33 && (int) c <= 47) || ((int) c >= 58 && (int) c <= 64) || ((int) c >= 91 && (int) c <= 96) || ((int) c >= 123 && (int) c <= 126)) {

					punc_check=1;
					break;
				}
				

			// Converting to lower case here
			
				word[i]= tolower(c);
				
			}

			if (punc_check == 1) {
				break;
			}

			word_arr[count]= word;
			count++;

		}


	
	 
		if (punc_check == 1) {
			punc_check=0;
			printf("[invalid query]");
	
		}

		else {
			for (int j=0; j< count; j++ ) {
				printf("%s ", word_arr[j]);
			}
			printf("\n");
		
		
			//int min= INT_MAX;
			for (int i=0; i< count; i++ ) {
				//printf("%s", word_arr[i]);
				//int min= INT_MAX;
				if ( strcmp(word_arr[i], "and") == 0 || strcmp(word_arr[i], "or") == 0 || strlen(word_arr[i]) < 3) {
					//printf("%d", strlen(word_arr[i]));
					continue;
				}
				else {

					paramcount = paramcount + 1;
					
					char *word = word_arr[i];
					word_t *wp = (word_t *)hsearch(index1, s, word, strlen(word));
					if (wp != NULL){
						queue_t *pagequeue = (queue_t *)wp->qp;
						page_t *pagep = NULL;
						while ((pagep = qget(pagequeue)) != NULL){

							if(docqueue[pagep->pageid] == NULL){
								doc_t *docp = (doc_t *)malloc(sizeof(doc_t));
								docp->docid = pagep->pageid;
								docp->rank = pagep->count;
								docp->totalmatches = 1;
								docqueue[pagep->pageid] = docp;
							} else{
								doc_t *dp = docqueue[pagep->pageid];
								dp->totalmatches = dp->totalmatches+1;
								if (dp->rank > pagep->count){
									dp->rank = pagep->count;
								}
							}
						}
					}
				}

			//printf("- %d", min);
			}
 
		}

		//print out the rankings
		for (int k = 0; k < 10; k++){
			if (docqueue[k] == NULL){
				continue;
			}else {
				if ((docqueue[k]->totalmatches) < paramcount){
					free(docqueue[k]);
				}else {
					webpage_t *wp = pageload(docqueue[k]->docid, "../pagedir");
					printf("rank: %d: doc: %d : %s\n", docqueue[k]->rank, docqueue[k]->docid, webpage_getURL(wp));
					free(docqueue[k]);
					webpage_delete(wp);
				}
			}
			
		}
		
		printf("\n");
		//rebuild the index
		hclose(index1);
	
		printf(">");
	
	}
	//hclose(index1);
	
	return 0;
}

bool s(void* p, const void* key){

	word_t *searchw = (word_t *)p;
	char *w = searchw->word;

	if (strcmp(w, key) == 0){
		return true;
	}
	return false;
}
