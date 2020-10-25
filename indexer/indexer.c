/* indexer.c --- 
 * 
 * 
 * Author: Agampodi I. Abeysekara
 * Created: Sun Oct 25 11:25:16 2020 (-0400)
 * Version: 
 * 
 * Description: 
 * 
 */


#include <stdlib.h>
#include <stdio.h>
#include "webpage.h"
#include "pageio.h"
#include <string.h>
#include <ctype.h>

char* NormalizeWord(char *str);

int main(void) {
	webpage_t *w1= pageload(1, "../pages");

	char *result;
	int pos=0;
	while ((pos = webpage_getNextWord(w1, pos, &result)) > 0 ) {
		char *res= NormalizeWord(result);
		if (strcmp(res, "" ) != 0) {
			printf("%s\n", res);
		}
		else {
			continue;
		}
	}
	webpage_delete((void *) w1); 
	return 0;
}


char* NormalizeWord(char *str) {
	int i=0;
	bool check= false;
	while (str[i] != '\0') {
		str[i]= tolower(str[i]);
		int ascii= (int) str[i];
		if (ascii > 97 && ascii < 122) {
			check= true;
		}
		else {
			check= false;
		}
		i++;
	}

	if (check == false || strlen(str) < 3) {
		return "";
	}
	return str;
}
