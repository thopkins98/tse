/* crawler_step5_pgload.c --- 
1;95;0c * 
 * 
 * Author: Agampodi I. Abeysekara
 * Created: Sun Oct 25 04:13:15 2020 (-0400)
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
#include "pageio.h"

int main(void) {
	printf("hello\n");

	char dir[12]="../pages";
	webpage_t *w1= pageload(1, dir);

	char *url= webpage_getURL(w1);
	printf("%s\n", url);

	int depth= webpage_getDepth(w1);
	printf("%d\n", depth);

	int htmllen= webpage_getHTMLlen(w1);
	printf("%d\n", htmllen);

	char *html= webpage_getHTML(w1);
	printf("%s\n", html);
	pagesave(w1, 12, "../pages");

	webpage_delete((void *) w1);

	//char dir2[10];
	 
	return 0;

}
