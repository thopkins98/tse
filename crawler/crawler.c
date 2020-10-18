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
#include <string.h>
#include "webpage.h"

int main(void){

	printf("hello\n");

	const int depth = 0;
	char *seed = "https://thayer.github.io/engs50/";
	char *html1 = NULL;
	
 
	webpage_t *w1 = webpage_new("https://thayer.github.io/engs50/", 0, NULL);
	bool check = false;
	
	printf("check\n");
	
	check = webpage_fetch(w1);
	
	if (check == false) {
		exit(EXIT_FAILURE);
	}

	

	int pos=0;
	char *result;
	bool internal = false;
	
	while ((pos = webpage_getNextURL(w1, pos, &result)) > 0) {

		internal = IsInternalURL(result);
		printf("Found url: %s", result);

		if (internal == true) {
			printf(" This URL is Internal\n");
		}
		
		else {
			printf(" This URL is not Internal\n");
		}
		
	free (result);
	}

	webpage_delete((void *)w1);
	
	return 0;
}
