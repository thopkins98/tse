#pragma once

/* lhash.h --- 
 * 
 * 
 * Author: Agampodi I. Abeysekara
 * Created: Sat Nov 14 02:12:39 2020 (-0500)
 * Version: 
 * 
 * Description: Header file for the lhash module. 
 * 
 */

#include <stdint.h>
#include <stdbool.h>
#include <pthread.h>
#include "queue.h"

typedef struct lhash lhash_t;

/* Opens a locked hash module */

lhash_t* lhopen(void);

/* Closes a locked hash module */

void lhclose(lhash_t *lht);

/* Insert into locked hashtable */

int32_t lhput(lhash_t *lht, void *elementp, const char *key, int keylen);

/* Provides delay between lhash puts */

int32_t lhput_delay(lhash_t *lht, void *elementp, const char *key, int keylen);

/* Get item from hashtable */

//void* lhget(lhash_t *lht);

/* Get item from hashtable with delay */

//void* lhget_delay(lhash_t *lht);

/* Apply function to a locked hashtable */

void lhapply(lhash_t* ht, void (*fn)(void* elementp));

/* Search through hashtable */

void* lhsearch(lhash_t *lht, bool (*searchfn)(void *elementp, const void* keyp), const char* key, int32_t keylen);

/* Remove key from hashtable */

void* lhremove(lhash_t *lht, bool (*searchfn) (void* elementp, const void* keyp), const char* key, int32_t keylen);
/* Combine two hashtables */

//void lhconcat(lhash_t *lht1, lhash_t *lht2);
