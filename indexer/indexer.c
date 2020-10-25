/* indexer.c --- 
 * 
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


int main(void) {
	printf("Hello\n");
	char dir[12]= "../pages";
	webpage_t *w1= pageload(1, "../pages");
	char *html= webpage_getURL(w1);
	printf("%s/n", html);
	webpage_delete((void *) w1);
	return 0;
}
