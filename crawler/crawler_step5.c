/* crawler3.c --- 
1;95;0c * 
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
//#include "pageio.h"

bool s(void* p, const void* key);
int32_t pagesave(webpage_t *pagep, int id, char *dirname);

int main(void){

	printf("hello\n");

	char *seed= "https://thayer.github.io/engs50/";

	webpage_t *w1= webpage_new(seed, 0, NULL);
	queue_t *pagequeue= qopen();
	hashtable_t *hasht= hopen(5);
	
	bool check= false;
	check= webpage_fetch(w1);

	if (check == false) {
		exit(EXIT_FAILURE);

	}
	//	char *url= webpage_getURL(w1);
	//int num= webpage_getDepth(w1);
	//int len= webpage_getHTMLlen(w1);
	//char *html= webpage_getHTML(w1);

	//	printf("%s \n", url);
	//printf("%d \n", num);
	//printf("%d \n", len);
	//printf("%s \n", html);
	
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
			char *url= webpage_getURL(iwp);
			
			if (hsearch(hasht, s, url, strlen(url)) == NULL) {
				hput(hasht, (void *) iwp, url, strlen(url));
				qput(pagequeue, (void *) iwp);
			}
			else {
				printf("The url exists in the hashtable\n");
				webpage_delete((void *) iwp);
			}
			//			webpage_delete((void *) iwp);
			
		}
		else {
			printf("This URL is not Internal\n");
		}
		free(result);
	 
	}
	
	pagesave(w1, 1, "../pages");
	webpage_delete((void *) w1);

	//webpage_t *wbtoprint= NULL;
	char *urltoprint= NULL;

	while (pagequeue != NULL) {
		webpage_t *wbtoprint= (webpage_t *) qget(pagequeue);

		if ( wbtoprint == NULL ) {
			break;
		}

		urltoprint = webpage_getURL(wbtoprint);
		printf("%s\n", urltoprint);
		webpage_delete((void *) wbtoprint);

	}

	qclose(pagequeue);
	hclose(hasht);
	
	return 0;



}

bool s(void* p, const void* key) {


	char *url = webpage_getURL((webpage_t *) p);
	
	if (strcmp(url, key) == 0 ) {
		return true;
	}

	return false;
}

int32_t pagesave(webpage_t *pagep, int id, char *dirname){

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
