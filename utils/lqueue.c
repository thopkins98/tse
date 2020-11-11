/* lqueue.h --- 
 * 
 * 
 * Author: Trevor S. Hopkins
 * Created: Tue Nov 10 15:22:48 2020 (-0500)
 * Version: 
 * 
 * Description: 
 * 
 */

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <pthread.h>
#include "queue.h"
#include "lqueue.h"
#include <unistd.h>

typedef struct lqueueStruct{
	queue_t *qp;
	pthread_mutex_t m;
} lqueueStruct_t;


lqueue_t* lqopen(void){

	queue_t* q = qopen();
	pthread_mutex_t mutx;
	pthread_mutex_init(&mutx, NULL);
	lqueueStruct_t *lq = (lqueueStruct_t *)malloc(sizeof(lqueueStruct_t));
	lq->qp = q;
	lq->m = mutx;

	return (lqueue_t *)lq;
}

void lqclose(lqueue_t *lqp){

	lqueueStruct_t *tmp = (lqueueStruct_t *)lqp;
	pthread_mutex_lock(&tmp->m);
	qclose(tmp->qp);
	pthread_mutex_unlock(&tmp->m);
	pthread_mutex_destroy(&tmp->m);
	free(tmp);

	return;
}

int32_t lqput(lqueue_t *lqp, void *elementp){

	lqueueStruct_t *tmp = (lqueueStruct_t *)lqp;
	
	pthread_mutex_lock(&tmp->m);
	qput(tmp->qp, elementp);
	pthread_mutex_unlock(&tmp->m);

	return 0;
}


int32_t lqput_delay(lqueue_t *lqp, void *elementp){

	lqueueStruct_t *tmp = (lqueueStruct_t *)lqp;
	
	pthread_mutex_lock(&tmp->m);
	qput(tmp->qp, elementp);
	sleep(10); //sleep for ten seconds
	pthread_mutex_unlock(&tmp->m);

	return 0;
}


void* lqget(lqueue_t *lqp){

	lqueueStruct_t *tmp = (lqueueStruct_t *)lqp;
	
	void *tmpelement = NULL;
	pthread_mutex_lock(&tmp->m);
	tmpelement = qget(tmp->qp);
	pthread_mutex_unlock(&tmp->m);

	return tmpelement;
}

void* lqget_delay(lqueue_t *lqp){

	lqueueStruct_t *tmp = (lqueueStruct_t *)lqp;
	
	void *tmpelement = NULL;
	pthread_mutex_lock(&tmp->m);
	tmpelement = qget(tmp->qp);
	sleep(10); //sleep for 10 seconds
	pthread_mutex_unlock(&tmp->m);

	return tmpelement;
}


void lqapply(lqueue_t *lqp, void (*fn)(void* elementp)){

	lqueueStruct_t *tmp = (lqueueStruct_t *)lqp;
	pthread_mutex_lock(&tmp->m);
	qapply(tmp->qp, fn);
	pthread_mutex_unlock(&tmp->m);

	return;
}

void* lqsearch(lqueue_t *lqp,
							 bool (*searchfn)(void* elementp, const void* keyp),
							 const void* skeyp){

	lqueueStruct_t *tmp = (lqueueStruct_t *)lqp;
	void *tmpelement = NULL;
	pthread_mutex_lock(&tmp->m);
	tmpelement = qsearch(tmp->qp, searchfn, skeyp);
	pthread_mutex_lock(&tmp->m);
  
	return tmpelement;
}

void* lqremove(lqueue_t *lqp,
							 bool (*searchfn)(void* elementp, const void* keyp),
							 const void* skeyp);
