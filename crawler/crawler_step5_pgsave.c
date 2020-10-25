/* crawler_step5_pgsave.c --- 
1;95;0c1;95;0c * 
 * 
 * Author: Agampodi I. Abeysekara
 * Created: Sun Oct 25 06:10:07 2020 (-0400)
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

bool s(void* p, const void* key);

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
	
	
	pagesave(w1, 1, "../pages");;
	webpage_delete((void *) w1);

	
	
	return 0;



}

