#pragma once
/* 
 * pageio.h --- saving and loading crawler webpage files
 * 
 * Author: Stephen Taylor
 * Created: Fri Oct 19 08:30:15 2018 (-0400)
 * Version: 1.0
 * 
 * Description: pagesave saves an existing webpage to a file with a
 * numbered name (e.g. 1,2,3 etc); pageload creates a new page by
 * loading a numbered file. For pagesave, the directory must exist and
 * be writable; for loadpage it must be readable.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <unistd.h>
#include <webpage.h>
#include "lhash.h"
#include "hash.h"

typedef struct word word_t;
typedef struct page page_t;

/*
 * pagesave -- save the page in filename id in directory dirnm
 *
 * returns: 0 for success; nonzero otherwise
 *
 * The suggested format for the file is:
 *   <url>
 *   <depth>
 *   <html-length>
 *   <html>
 */
int32_t indexsave(hashtable_t *index, int id, char *dirnm);

/* 
 * pageload -- loads the numbered filename <id> in direcory <dirnm>
 * into a new webpage
 *
 * returns: non-NULL for success; NULL otherwise
 */
hashtable_t* indexload(int id, char *dirnm);


/*
 * lockindexsave -- version of indexsave that will work with a locked
 * hash table used while multithreading the indexer.
 *
 * returns: 0 for success; nonzero otherwise
 */
int32_t lockindexsave(lhash_t *index, int id, char *dirnm);


/*
 * lockindexload -- version of indexload that will work with a locked
 * hash table used while multithreading the indexer.
 *
 * returns: non-NULL for success; NULL otherwise
 */
lhash_t* lockindexload(int id, char *dirnm);