/* step1_test.c --- 
 * 
 * 
 * Author: Trevor S. Hopkins
 * Created: Tue Nov 10 16:15:38 2020 (-0500)
 * Version: 
 * 
 * Description: 
 * 
 */

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "queue.h"
#include "lqueue.h"
#include <unistd.h>

//Global locked queue;
lqueue_t *lq;


void *tfunc1(void *argp);
void *tfunc2(void *argp);

int main(void){

	pthread_t thread1, thread2;

	lq = lqopen();

	if(pthread_create(&thread1, NULL, tfunc1, NULL)!=0){
		exit(EXIT_FAILURE);
	}
	
	if(pthread_create(&thread2, NULL, tfunc2, NULL)!=0){
		exit(EXIT_FAILURE);
	}

	
	if(pthread_join(thread1, NULL)!=0){
		exit(EXIT_FAILURE);
	}
	
	if(pthread_join(thread2, NULL)!=0){
		exit(EXIT_FAILURE);
	}
	

	printf("%s\n", (char *)lqget(lq));
	printf("%s\n", (char *)lqget(lq));

	lqclose(lq);
	
	return 0;
}

void *tfunc1(void *argp){

	char *p1 = "First_process_complete";
	
	printf("Thread 1: locking queue and inserting data\n");
	lqput_delay(lq, (void *)p1);
	printf("Thread 1: queue use complete, data inserted\n");
	

	return argp;
}


void *tfunc2(void *argp){

		char *p1 = "Second_process_complete";

		printf("Thread 2: attempting to access queue\n");
		lqput(lq, (void *)p1);
		printf("Thread 2: queue accessed\n");
		

	return argp;
}

	
