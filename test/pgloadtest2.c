/* pgloadtest2.c --- 
 * 
 * 
 * Author: Agampodi I. Abeysekara
 * Created: Sun Oct 25 05:02:15 2020 (-0400)
 * Version: 
 * 
 * Description: 
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include "pageio.h"
#include "webpage.h"
#include <string.h>

int main(void) {
	printf("hello\n");
	char dir2[10]="../pages";;
	webpage_t *w2= pageload(12, dir2);
	char *html= webpage_getHTML(w2);
	printf("%s\n", html);
	webpage_delete((void *) w2);
	return 0;
}
