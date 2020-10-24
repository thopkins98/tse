/* pageio.c --- 
 * 
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

	fprintf(fp, "%s \n%d \n%d \n%s \n",
										 webpage_getURL(pagep),
										 webpage_getDepth(pagep),
										 webpage_getHTMLlen(pagep),
										 webpage_getHTML(pagep));

	fclose(fp);

	return 0;

}
