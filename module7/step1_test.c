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


int main(void){

	char *p1 = "test";
	char *p2 = "a";
	char *p3 = "is";
	char *p4 = "This";
	
	lqueue_t *lq = lqopen();

	printf("Adding to queue\n");
	lqput(lq, (void *)p4);
	lqput(lq, (void *)p3);
	lqput(lq, (void *)p2);
	lqput(lq, (void *)p1);

	printf("Printing from queue\n");
	
	for (int j=0; j<4; j++){

		printf("%s\n", (char *)lqget(lq));
	}


	
	return 0;
}
