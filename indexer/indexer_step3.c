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
	char word[100];
	int count;
} word_t;

char* NormalizeWord(char *str);
bool searchfunc(void* elementp, const void* searchkeyp);
bool s(void* p, const void* key);
void sumwords(void *ep);

//global variable
int sum=0;

int main(void) {
	webpage_t *w1= pageload(1, "../pages");


	word_t *wordsearch = NULL;
	hashtable_t *ht = hopen(200);
	
	char *result;
	int pos=0;
	while ((pos = webpage_getNextWord(w1, pos, &result)) > 0 ) {
		if (strcmp(NormalizeWord(result), "") != 0) {
		
			if ((wordsearch = (word_t *)hsearch(ht, s, result, strlen(result))) != NULL){
				wordsearch->count = wordsearch->count + 1;
				free(result);
		
			}else{
				word_t *wordpointer = (word_t *)malloc(sizeof(word_t));
				strcpy(wordpointer->word, result);
			
				wordpointer->count = 1;
				hput(ht, (void *)wordpointer, wordpointer->word, strlen(wordpointer->word));
				free(result);
			}
		
		}
	  else {
			free(result);
		  continue;
		}
		
	}
	
	//report sum
	happly(ht, sumwords);
	printf("Total Word Count: %d\n", sum);




	wordsearch = NULL;
	hclose(ht);
	webpage_delete(w1); 
	
	
	return 0;
}

void sumwords(void *ep){
	word_t *w = (word_t *)ep;
	sum=sum + w->count;
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
