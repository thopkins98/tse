#pragma once

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
#include <pthread.h>
#include "queue.h"

typedef struct lqueue lqueue_t;

lqueue_t* lqopen(void);

void lqclose(lqueue_t *lqp);

int32_t lqput(lqueue_t *lqp, void *elementp);

int32_t lqput_delay(lqueue_t *lqp, void *elementp);

void* lqget(lqueue_t *lqp);

void* lqget_delay(lqueue_t *lqp);

void lqapply(lqueue_t *qp, void (*fn)(void* elementp));

void* lqsearch(lqueue_t *lqp,
							 bool (*searchfn)(void* elementp, const void* keyp),
							 const void* skeyp);

void* lqremove(lqueue_t *lqp,
							 bool (*searchfn)(void* elementp, const void* keyp),
							 const void* skeyp);

void lqconcat(lqueue_t *lq1p, lqueue_t *lq2p);
