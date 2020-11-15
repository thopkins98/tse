/* test2.c --- 
1;95;0c1;95;0c1;95;0c1;95;0c1;95;0c1;95;0c1;95;0c1;95;0c1;95;0c * 
 * 
 * Author: Agampodi I. Abeysekara
 * Created: Sun Nov 15 02:04:08 2020 (-0500)
 * Version: 
 * 
 * Description: 
 * 
 */

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <pthread.h>
#include "queue.h"
#include "lhash.h"
#include "hash.h"

bool search(void* elementp, const void*searckkeyp);
//test_t* make_test(char* c, int num);

typedef struct test {
	int id;
	char key[20];
} test_t;

test_t* make_test(char* c, int num);

int main(void) {

	test_t *p1= make_test("test", 1);
	test_t *p2= make_test("test", 2);
	test_t *p3= make_test("a", 3);
	test_t *p4= make_test("is", 4);
	test_t *p5= make_test("This", 5);

	//queue_t *qp= qopen();

	printf("Adding to hashtable\n");


	//printf("%s\n", p1);
	//qput(qp, p1);
	//printf("%s\n", p2);
	//qput(qp, p2);
	//printf("%s\n", p3);
	//qput(qp, p3);
	//printf("%s\n", p4);
	//qput(qp, p4);

	lhash_t* ht= lhopen();

	printf("%s\n", p1->key);
	lhput(ht, (void *) p1, p1->key, strlen(p1->key));
	printf("%s\n", p2->key);
	lhput(ht, (void *) p2, p2->key, strlen(p2->key));
	printf("%s\n", p3->key);
	lhput(ht, (void *) p3, p3->key, strlen(p3->key));
	printf("%s\n", p4->key);
	lhput(ht, (void *) p4, p4->key, strlen(p4->key));
	printf("%s\n", p5->key);
	lhput(ht, (void *) p5, p5->key, strlen(p5->key));  

	printf("Checking if elements have been added to the queue successfully\n");
	
	test_t* res= (test_t *) lhsearch(ht, search, "This", strlen("This"));

	printf("The result is: %s with id: %d\n", res->key, res->id);

	//test_t* res2= (test_t *) hremove(ht, search, "test", strlen("test"));

	//printf("The result is: %s with id: %d\n", res2->key, res2->id);

	test_t* res2= (test_t *) lhsearch(ht, search, "is", strlen("is"));

	printf("The result is: %s with id: %d\n", res2->key, res2->id);

	test_t* res3= (test_t *) lhsearch(ht, search, "a", strlen("a"));

	printf("The result is: %s with id: %d\n", res3->key, res3->id);

	test_t* res4= (test_t *) lhsearch(ht, search, "test", strlen("test"));

	printf("The result is: %s with id: %d\n", res4->key, res4->id);

	printf("Notice that 'test' has an id of one. This is because it is the first entry of two 'test' entries. Both entries are in a queue\n");
	
	//free(p1);
	//free(p2);
	//free(p3);
	//free(p4);
	//free(p5);
	lhclose(ht);
	
}

bool search(void* elementp, const void *searchkeyp) {
	test_t* element= (test_t *) elementp;
	char* searchkey= (char *) searchkeyp;

	if (strcmp(element->key, searchkey) == 0) {
		return true;
	}

	return false;

}


test_t* make_test(char* c, int num) {

	test_t *res= (test_t *) malloc(sizeof(test_t));
	strcpy(res->key, c);
	res->id= num;

	return res;

}
