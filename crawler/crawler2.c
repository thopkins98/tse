/* crawler2.c --- 
 * 
 * 
 * Author: Trevor S. Hopkins
 * Created: Tue Oct 13 16:13:13 2020 (-0400)
 * Version: 
 * 
 * Description: 
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "webpage.h"
#include "queue.h"


void printURL(void *wp);

int main(void){

	printf("hello\n");


	char *seed = "https://thayer.github.io/engs50/";
	
	webpage_t *w1 = webpage_new(seed, 0, NULL);
	queue_t *pagequeue = qopen();

	
	bool check = false;
	check = webpage_fetch(w1);

	if (check == false) {
		exit(EXIT_FAILURE);
	}

	int pos=0;
	char *result;
	bool internal = false;

	int counter = 1;
	
	
	while ((pos = webpage_getNextURL(w1, pos, &result)) > 0) {

	internal = IsInternalURL(result);
	printf("Found url: %s\n", result);
	if (internal == true) {
		printf(" This URL is Internal\n");
		webpage_t *iwp= webpage_new(result, counter, NULL);
		qput(pagequeue, (void *) iwp);
		//webpage_delete((void *) iwp);
	}else {
		printf(" This URL is not Internal\n");
	}
	free(result);
	}

	webpage_delete((void *)w1);
	
	//print queue here
	//qapply(pagequeue, printURL);
	
	webpage_t *wbtoprint= NULL;
	printf("From queue:\n");
	
	while ((wbtoprint = (webpage_t *)qget(pagequeue)) != NULL ){
	
		printf("%s\n", webpage_getURL(wbtoprint));
		webpage_delete((void *)wbtoprint);
 
	}

	qclose(pagequeue);
	
	return 0;
}


void printURL(void *wp){

	char *str= webpage_getURL( (webpage_t *) wp);
	printf("%s", str);

}
