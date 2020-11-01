/* query.c --- 
1;95;0c * 
 * 
 * Author: Agampodi I. Abeysekara
 * Created: Sat Oct 31 11:47:35 2020 (-0400)
 * Version: 
 * 
 * Description: This program acts as the query interface. It prints out a parsed version of the query. 
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(void) {
	char buffer[100];
	
	printf(">");
	while(fgets(buffer, 100, stdin)) {
		if (strcmp(buffer, "\n") == 0) {
			printf(">");
		}

		char *word;
		char *ptr= buffer;

		char *word_arr[1024];
		
		int count=0;
		int punc_check=0;

		while ((word= strtok(ptr, " \t\n"))) {
			ptr= NULL;

			for (int i=0; i< strlen(word); i++) {
				char c= word[i];
			
				if (((int) c >= 33 && (int) c <= 47) || ((int) c >= 58 && (int) c <= 64) || ((int) c >= 91 && (int) c <= 96) || ((int) c >= 123 && (int) c <= 126)) {

					punc_check=1;
					break;
				}
				

			// Converting to lower case here
			
				word[i]= tolower(c);
				
			}

			if (punc_check == 1) {
				break;
			}

			word_arr[count]= word;
			count++;

		}

		
		
		if (punc_check == 1) {
			punc_check=0;
			printf("[invalid query]");
		}

		else {
			for (int i=0; i< count; i++ ) {
				printf("%s ", word_arr[i]);
			}
		}

		printf("\n");
		printf(">");
	}

	return 0;
}
