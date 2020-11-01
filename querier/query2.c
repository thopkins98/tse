/* query.c --- 
1;95;0c1;95;0c1;95;0c1;95;0c1;95;0c * 
 * 
 * Author: Agampodi I. Abeysekara
 * Created: Sat Oct 31 11:47:35 2020 (-0400)
 * Version: 
 * 
 * Description: This program acts as the query interface. It prints out a parsed version of the query. 
 * 
1;95;0c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

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
			int min= INT_MAX;
			for (int i=0; i< count; i++ ) {
				//printf("%s", word_arr[i]);
				//int min= INT_MAX;
				if ( strcmp(word_arr[i], "and") == 0 || strcmp(word_arr[i], "or") == 0 || strlen(word_arr[i]) < 3) {
					//printf("%d", strlen(word_arr[i]));
					continue;
				}
				else {
			
					char w[1024];
					int c=0;
					int id=0;
					//printf("scanning file");
					FILE *file= fopen("../indexdir/1", "r");
					while (fscanf(file, "%s %d %d \n", w, &id, &c) != EOF) {
						//printf("%d", id);
						if (strcmp(w, word_arr[i]) == 0 ) {
							printf("%s:%d ", word_arr[i], c);
							if ( c < min ) {
								min= c;
							}
						}
					}

					
					
				
					//printf("- %d", min);
					//printf("Hello");
					fclose(file);
				}
				//printf("- %d", min);
			}

			printf("- %d", min);
			
 
		}
		printf("\n");
		printf(">");
	
	}
	return 0;
}
