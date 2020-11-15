/* concurrent2.c --- 
1;95;0c1;95;0c * 
 * 
 * Author: Agampodi I. Abeysekara
 * Created: Sun Nov 15 04:45:51 2020 (-0500)
 * Version: 
 * 
 * Description: 
 * 
 */

#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <pthread.h>
#include "queue.h"
#include "lhash.h"
#include <unistd.h>
#include <stdlib.h>

//Global locked hashtable
lhash_t *lht;

void *tfunc1(void *argp);
void *tfunc2(void *argp);

typedef struct concurrent {
	char key[25];
	int id;
} concurrent_t;

concurrent_t* make_test(char*c , int num);

bool search(void* elementp, const void*searchkeyp);
void print(void *ep);

int main(void) {

	pthread_t thread1, thread2;

	lht= lhopen();

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

	printf("Checking for items in hashtable\n");

	//concurrent_t *res1= (concurrent_t*) lhsearch(lht, search, "First_process", strlen("First_process"));

	//if (res1 == NULL ) {
	//	printf("No result");
	//}
	//printf("The item found is: %s, with id: %d\n", res1->key, res1->id);

	//concurrent_t *res2= (concurrent_t*) lhsearch(lht, search, "Second_process", strlen("Second_process"));                 
  //printf("The item found is: %s, with id: %d\n", res2->key, res2->id); 

	lhapply(lht, print);
	lhclose(lht);

	return 0;

}


void *tfunc1(void *argp) {
	concurrent_t *p1= make_test("First_process", 1);
	concurrent_t *p2= make_test("First_process", 2);
	
	printf("Thread 1: locking hashtable and inserting data\n");

	lhput_delay(lht, (void *)p1, p1->key, strlen(p1->key));

	printf("Thread 1: Inserting same data to form a queue\n");

	lhput_delay(lht, (void *)p2, p2->key, strlen(p2->key));

	printf("Thread 1: hashtable use complete, data inserted\n");

	return argp;

}

void *tfunc2(void *argp) {

	concurrent_t *p3= make_test("Second_process", 3);

	printf("Thread 2: attempting to access hashtable\n");

	lhput_delay(lht, (void *) p3, p3->key, strlen(p3->key));

	printf("Thread 2: hashtable accessed\n");

	return argp;
}


bool search(void* elementp, const void* searchkeyp) {                          
  concurrent_t* element= (concurrent_t *) elementp;                            
  char* searchkey= (char *) searchkeyp;                                        
                                                                               
  if (strcmp(element->key, searchkey) == 0) {                                  
    return true;                                                               
  }
	return false;
}

concurrent_t* make_test(char*c , int num) {
	concurrent_t *res= (concurrent_t *) malloc(sizeof(concurrent_t));
	strcpy(res->key, c);
	res->id=num;
	return res;

}

void print(void *ep) {
	concurrent_t *res= (concurrent_t *) ep;
	printf("Key: %s, id: %d\n", res->key, res->id);
}
