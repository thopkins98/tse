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
	//char dir2[10]="../pages";;
	printf("File 1: \n");
	webpage_t *w2= pageload(1, "../pages");
	
	char *html= webpage_getHTML(w2);
	//printf("%s\n", html);
	pagesave(w2, 12, "../pages");

	printf("File 12: \n");
	webpage_t *w3 = pageload(12, "../pages");
	char *html2= webpage_getHTML(w3);
  if (strcmp(html, html2) == 0 ) {
	printf("Success");
   }
	webpage_delete( w2);
	webpage_delete( w3);
	return 0;
}
