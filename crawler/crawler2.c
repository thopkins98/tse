/* crawler.c --- 
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

int main(void){

	printf("hello\n");

	//const int depth = 0;
	char *seed = "https://thayer.github.io/engs50/";
	
	struct webpage *w1 = webpage_new(seed, 0, NULL);
	struct queue *pagequeue = qopen();
		
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
		printf("Found url: %s", result);
		if (internal == true) {
			printf(" This URL is Internal\n");
			struct webpage *page = webpage_new(result, counter, NULL);
			qput(pagequeue, (void*)page);
		}else {
			printf(" This URL is not Internal\n");
		}
		free (result);
		webpage_delete((void *)page);
	}

	webpage_delete((void *)w1);
	
	//print queue here

	struct webpage *printpage = NULL;
	char *urltoprint = NULL;
	while (pagequeue->front != NULL){
		printpage = (webpage_t *)qget(pagequeue);
		urltoprint = printpage->url;
		fprint("%s\n", urltoprint);
		webpage_delete((void *)printpage);
	}

	qclose(pagequeue);
	
	return 0;
}
