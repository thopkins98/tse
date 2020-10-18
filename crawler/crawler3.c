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
int main(void){

	printf("hello/n");

	char *seed= "https://thayer.github.io/engs50/";

	webpage_t *w1= webpage_new(seed, 0, NULL);
	queue_t *pagequeue= qopen();
	hashtable_t *hasht= hopen(10);
	
	bool check= false;
	check= webpage_fetch(w1);

	if (check == false) {
		exit(EXIT_FAILURE);

	}

	int pos=0;
	char *result;
	bool internal= false;

	int counter=1;

	while ((pos= webpage_getNextURL(w1, pos, &result)) >0) {
		internal= IsInternalURL(result);
		printf("Found url: %s\n", result);
		if (internal == true) {
			printf("This URL is Internal\n");
			webpage_t *iwp= webpage_new(result, counter, NULL);
			qput(pagequeue, (void *) iwp);
		}
		else {
			printf("This URL is not Internal\n");
		}
		free(result);
	}

	return 0;



}

