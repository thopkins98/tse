/* pageio.c --- 
1;95;0c1;95;0c1;95;0c1;95;0c1;95;0c1;95;0c1;95;0c1;95;0c * 
 * 
 * Author: Agampodi I. Abeysekara
 * Created: Sat Oct 24 03:26:18 2020 (-0400)
 * Version: 
 * 
 * Description:  Contains pagesave and pageload functions for the indexer.
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
#include <inttypes.h>
#include "pageio.h"




/*

This function saves a webpage to a file containing a url, depth, html length and associated hmtl.

The parameters:
pagep: a pointer to an instance of type webpage_t (the webpage fetched)
id: id assigned to the webpage
dirnm: directory where the file is saved.


 */

int32_t pagesave(webpage_t *pagep, int id, char*dirnm) {

	FILE *fp;
	char fname[12];
	sprintf(fname, "%s/%d", dirnm, id);

	fp = fopen(fname, "w+");
	fprintf(fp, "%s\n%d\n%d\n%s",webpage_getURL(pagep),webpage_getDepth(pagep),webpage_getHTMLlen(pagep),webpage_getHTML(pagep));

	fclose(fp);

	return 0;

}

/*
This method is supposed to load a saved page and return a page.

The parameters:
id: The id of the page saved. An integer.
dirname: A character pointer which contains the name of the directory that contains the page.

 */


webpage_t* pageload(int id, char* dirnm) {

	webpage_t *res=NULL;

	// the directory name will be assumed to be less than 12 characters eg: ../pages
	char fname[12];
	sprintf(fname, "%s/%d", dirnm, id);
	

	//new input to scan url, depth, html length, html
	
	FILE *input2= fopen(fname, "r");

	char url[100];

	// if statements check if the fscanf was successful
	
	if (fscanf(input2, "%s", url)!=1) {
		fprintf(stderr, "Error reading url");
		return res;
		}
	
	int depth;
	
	if (fscanf(input2, "%d", &depth) != 1) {
		fprintf(stderr, "Error reading depth");
		return res;
		
	}

	int html_len;
	
	if (fscanf(input2, "%d", &html_len)!=1) {
		fprintf(stderr, "Error reading html length");
		return res;
	}
	printf("The length of html is: %d\n", html_len);

	char c;

	// Allocating memory for html. Feel like I did something wrong from this point onwards.
	
	char *html= (char *) malloc(sizeof(char) * (html_len + 3));
	int index=0;

	while ((c=fgetc(input2)) != EOF) {

		printf("%c", c);
		html[index]=c;
		index++;
		

	} 
	
	//printf("%d\n", index);

	html[index-1]='\0';
	
	res= webpage_new(url, depth, html);
	
	fclose(input2);
	
	return res;

	
}

	
