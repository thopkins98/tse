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
#include "pageio.h"

//bool s(void* p, const void* key);
//int32_t pagesave(webpage_t *pagep, int id, char *dirname);

int main(void){

	printf("hello\n");

	//char *seed= "https://thayer.github.io/engs50/";

	//webpage_t *w1= webpage_new(seed, 0, NULL);
	
	//bool check= false;
	//check= webpage_fetch(w1);

	//if (check == false) {
	//exit(EXIT_FAILURE);

	//}
	
	//pagesave(w1, 1, "../pages");
	//	webpage_delete((void *) w1);
	webpage_t *w2= pageload(1, "../pages");
	
	int htmLlen= webpage_getHTMLlen(w2);
	printf("The length of html is: %d\n",htmLlen);
	
	char *html= webpage_getHTML(w2);
	printf("%s", html);
	//	pagesave(w2, 12, "../pages");
	webpage_delete((void *) w2);
	return 0;
}


