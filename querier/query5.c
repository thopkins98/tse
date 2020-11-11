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

void arrayadd(doc_t* arrmaster[10], doc_t* arrtemp[10], int minrank);
void indexCleanup(hashtable_t *index);
void wordDelete(void *currWord);
void arrayCleanup(doc_t *array[]);
void arrayInit(doc_t *array[]);

// Expected usage: query <pageDirectory> <indexFile> [-q]
int main(const int argc, char *argv[]){

    if (argc != 3){
        if (argc != 6){
            printf("Invalid arguments. Usage: query <pageDirectory> <indexFile> [-q]\n");
            exit(EXIT_FAILURE);
        }
    }

    char filetest[50];
    // Check if pageDirectory is a valid, crawler directory
    sprintf(filetest, "%s/.crawler", argv[1]);
    FILE *test;
	if ((test = fopen(filetest, "r")) == NULL){
		printf("directory is not readable or was not made by a crawler\n");
        exit(EXIT_FAILURE);
	}
    fclose(test);
    // Check if indexFile is valid
    if ((test = fopen(argv[2], "r")) == NULL){
		printf("index file is not readable or does not exist\n");
        exit(EXIT_FAILURE);
	}



    fclose(test);

    int quietFlag = 0;
    char inputFile[20];
    char outputFile[20];
    if(argc == 6){
        if(strcmp(argv[3], "-q") == 0){
            quietFlag = 1;
            strcpy(inputFile, argv[4]);
            strcpy(outputFile, argv[5]);
        }
    }

    FILE *fout;
    if(quietFlag == 1){
        fout = fopen(outputFile, "w");
    }

    //Parse index file into directory and index number
    char indexFile[20];
    strcpy(indexFile, argv[2]);
    char indexNo = indexFile[strlen(indexFile)-1];
    int indexInt;
    sscanf(&indexNo, "%d", &indexInt);
    indexFile[strlen(indexFile)-1] = '\0';
    

	static int ARR_SIZE = 100;

	doc_t *docqueue_master[ARR_SIZE];
	arrayInit(docqueue_master);

	char buffer[100];

	
	printf(">");

    FILE *inputStream;
    if (quietFlag == 1){
        inputStream = fopen(inputFile, "r");
    }
    else{
        inputStream = stdin;
    }


	while(fgets(buffer, 100, inputStream)) {
		if (strcmp(buffer, "\n") == 0) {
			printf(">");
		}

		char *word;
		char *ptr= buffer;

		char *word_arr[1024];
		
		int count=0;
		int failure=0;
	

        bool prevAndOr = true;
		
		while ((word= strtok(ptr, " \t\n"))) {
			ptr= NULL;

			for (int i=0; i< strlen(word); i++) {
				char c= word[i];
			
				//if (((int) c >= 33 && (int) c <= 47) || ((int) c >= 58 && (int) c <= 64) || ((int) c >= 91 && (int) c <= 96) || ((int) c >= 123 && (int) c <= 126)) {
				if(!isalpha(c)){
					failure=1;
					break;
				}
				

			// Converting to lower case here
			
				word[i]= tolower(c);
				
			}

			if (failure == 1) {
				break;
			}

            if((strcmp(word, "or") == 0 || strcmp(word, "and") == 0) && prevAndOr){
                failure = 1;
            }

            if(strcmp(word, "or") == 0 || strcmp(word, "and") == 0){
                prevAndOr = true;
            }
            else{
                prevAndOr = false;
            }



			word_arr[count]= word;
			count++;

		}
        if(prevAndOr){
            failure = 1;
        }


	
	 
		if (failure == 1) {
			failure=0;
			printf("[invalid query]\n");
	
		}

		else {
			for (int j=0; j< count; j++ ) {
                if (quietFlag ==1){
                    fprintf(fout, "%s ", word_arr[j]);
                }
                else{
				    printf("%s ", word_arr[j]);
                }
			}
            if (quietFlag ==1){
                fprintf(fout, "\n");
            }
            else{
                printf("\n");
            }

		
			int i=0;
			//loop over entire input string
			//printf("beginning query check\n");
			while ((i < count)) {
				doc_t *docqueue[ARR_SIZE];
				arrayInit(docqueue);
				
				int paramcount = 0;
				hashtable_t *index1 = indexload(indexInt, indexFile);


				//loop over individual strings separated by "ORs"
				//printf("looping over first and chain\n");
				while (strcmp(word_arr[i], "or") != 0){
					
						if ( strcmp(word_arr[i], "and") == 0 || strlen(word_arr[i]) < 3) {
					
							//printf("found an and\n");
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
									free(pagep);
								}
							}
                            else{
                                printf("No Results Found\n");
                            }
						}
						i = i + 1;
						if (i >= count){
							break;
						}
				}
				//printf("copying over to master array\n");
				arrayadd(docqueue_master, docqueue, paramcount);
				//printf("closing index\n");
				indexCleanup(index1);
				//hclose(index1);
				i = i + 1;
			}
 
		}
		//printf("Printing Ranks:\n");
		//print out the rankings
		for (int k = 0; k < ARR_SIZE; k++){
			if (docqueue_master[k] == NULL){
				continue;
			}else {
					//webpage_t *wp = pageload(docqueue_master[k]->docid, "../pagedir");
                    webpage_t *wp = pageload(docqueue_master[k]->docid, argv[1]);
                    if(quietFlag == 1){
                        fprintf(fout, "rank: %d: doc: %d : %s\n", docqueue_master[k]->rank, docqueue_master[k]->docid, webpage_getURL(wp));
                    }
                    else{
					    printf("rank: %d: doc: %d : %s\n", docqueue_master[k]->rank, docqueue_master[k]->docid, webpage_getURL(wp));
                    }
					free(docqueue_master[k]);
					webpage_delete(wp);
			}
			
		}
		arrayCleanup(docqueue_master);
        
        if (quietFlag == 0){
            printf("\n");
		    printf(">");
        }
        else{
            fprintf(fout, "\n");
        }
	
	}
    if(quietFlag == 1){
        fclose(inputStream);
        fclose(fout);
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

void arrayadd(doc_t* arrmaster[], doc_t* arrtemp[], int minrank){

	for (int h=0; h < 100; h++){
		if (arrtemp[h] == NULL){
			continue;
		}
		if ( (arrmaster[h] == NULL) && (arrtemp[h] != NULL) ){
			if ((arrtemp[h]->totalmatches) < minrank){
				free(arrtemp[h]);
				arrtemp[h] = NULL;
			}else {
				arrmaster[h] = arrtemp[h];
				arrtemp[h] = NULL;
			}
		}else {
			if ((arrtemp[h]->totalmatches) < minrank){
				free(arrtemp[h]);
				arrtemp[h] = NULL;
			}else {
				arrmaster[h]->rank = arrmaster[h]->rank + arrtemp[h]->rank;
				free(arrtemp[h]);
				arrtemp[h] = NULL;
			}
		}
	}
	return;
}

void indexCleanup(hashtable_t *index){
	happly(index, wordDelete);
	hclose(index);
}

void wordDelete(void *currWord){
	qclose(((word_t*)currWord)->qp);
}

void arrayCleanup(doc_t *array[]){
	for (int i=0; i < 100; i++){
		if (array[i] != NULL){
			//free(array[i]);
			array[i] = NULL;
		}
	}
	return;
}

void arrayInit(doc_t *array[]){
	for (int i=0; i < 100; i++){
		array[i] = NULL;
	}
	return;
}
