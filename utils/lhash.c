
/* lhash.c --- 
 * 
 * 
 * Author: Agampodi I. Abeysekara
 * Created: Sat Nov 14 02:02:06 2020 (-0500)
 * Version: 
 * 
 * Description: This module allows for the implementation of a locked hash module. It uses a mutex to allocate resources and variables from processes running simultaneously by locking it from all processes other than the one currently using it. 
 * 
 */

#include <stdint.h>
#include <stdbool.h>
#include <pthread.h>
#include "queue.h"
#include "lhash.h"
#include "hash.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct lhashStruct {
	hashtable_t *h;
	pthread_mutex_t m;

} lhashStruct_t;

/* This function opens a locked hash table module */

lhash_t* lhopen(void) {
	hashtable_t* h= hopen(10);
	pthread_mutex_t mutx;
	pthread_mutex_init(&mutx, NULL);
	lhashStruct_t *lh = (lhashStruct_t *) malloc(sizeof(lhashStruct_t));
	lh->h= h;
	lh->m= mutx;
	return (lhash_t *) lh;
}

void lhclose(lhash_t *lht) {

	lhashStruct_t *tmp = (lhashStruct_t *) lht;
	pthread_mutex_lock(&tmp->m);
	hclose(tmp->h);
	pthread_mutex_unlock(&tmp->m);
	pthread_mutex_destroy(&tmp->m);
	free(tmp);

	return;

}

int32_t lhput(lhash_t *lht, void* elementp, const char *key, int keylen) {

	lhashStruct_t *tmp= (lhashStruct_t *) lht;

	if (lht == NULL ) {
		return 1;
	}
	pthread_mutex_lock(&tmp->m);
	hput(tmp->h, elementp, key, keylen);
	pthread_mutex_unlock(&tmp->m);
	return 0;

}

int32_t lhput_delay(lhash_t *lht, void* elementp, const char *key, int keylen) {
	lhashStruct_t *tmp= (lhashStruct_t *) lht;
	if (lht == NULL ) {
		return 1;
	}
	hput(tmp->h, elementp, key, keylen);
	sleep(10);
	pthread_mutex_unlock(&tmp->m);
	return 0;

}

//void* lhget(lhash_t *lht) {

//	lhashStruct_t *tmp= (lhashStruct_t *) lht;

//	void *tmpelement= NULL;
//	pthread_mutex_lock(&tmp->m);
//	tmpelement= hget(tmp->h);
//	pthread_mutex_unlock(&tmp->m);

//	return tmpelement;

//}

//void* lhget_delay(lhash_t *lht) {

//	lhashStruct_t *tmp= (hashStruct_t *) lht;
//	void* tmpelement= NULL;
//	pthread_mutex_lock(&tmp->m);
//	tmpelement= hget(&tmp->h);
//	sleep(10);
//	pthread_mutex_unlock(&tmp->m);

//}

void lhapply(lhash_t *lht, void (*fn)(void* elementp)) {

	lhashStruct_t *tmp= (lhashStruct_t *) lht;
	if (lht == NULL ) {
		printf("The hashtable is NULL.\n");
		return;
	}
	pthread_mutex_lock(&tmp->m);
	happly(tmp->h, fn);
	pthread_mutex_unlock(&tmp->m);

}
	
void* lhsearch(lhash_t *lht, bool (*searchfn) (void* elementp, const void* keyp), const char* key, int32_t keylen) {
	lhashStruct_t *tmp = (lhashStruct_t *) lht;
	if (lht == NULL ) {
		return NULL;
	}
	void *tmpelement= NULL;
	pthread_mutex_lock(&tmp->m);
	tmpelement= hsearch(tmp->h, searchfn, key, keylen);
	pthread_mutex_unlock(&tmp->m);

	return tmpelement;

}

void* lhremove(lhash_t *lht, bool (*searchfn) (void* elementp, const void* keyp), const char* key, int32_t keylen) {
	lhashStruct_t *tmp = (lhashStruct_t *) lht;
	if (lht == NULL ) {
		return NULL;
	}
	void *tmpelement= NULL;
	pthread_mutex_lock(&tmp->m);
	tmpelement= hremove(tmp->h, searchfn, key, keylen);
	pthread_mutex_unlock(&tmp->m);

	return tmpelement;

}

