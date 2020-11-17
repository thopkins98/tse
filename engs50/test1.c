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
	
	queue_t *qp = qopen();

	printf("Adding to queue\n");
	printf("%s\n", p1);
	qput(qp, p1);
	printf("%s\n", p2);
	qput(qp, p2);
	printf("%s\n", p3);
	qput(qp, p3);
	printf("%s\n", p4);
	qput(qp, p4);

	printf("Printing from queue\n");
	
	for (int j=0; j<4; j++){

		printf("%s\n", (char *)qget(qp));
	}


	
	return 0;
}
