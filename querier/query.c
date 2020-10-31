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
		int len= strlen(buffer);

		// The text array would hold the parsed query. Used calloc which initializes pointer to zero bytes.
		
		char* text= (char *) calloc(len + 1, sizeof(char)) ;

		// Checks if the return key was pressed
		
		if (strcmp(buffer, "\n") == 0) {
			printf(">\n");
			printf(">");
			continue;
		}

		// Building the text array with the count index.
		
		int count=0;

		for (int i=0; i<len; i++) {
			char c= buffer[i];

			// Checks for spaces and tabs using ASCII codes
			
			if ((int) c == 32 || (int) c ==9) {
				continue;
			}

			// Checks for punctuation marks using ASCII codes
			
			if (((int) c >= 33 && (int) c <= 47) || ((int) c >= 58 && (int) c <= 64) || ((int) c >= 91 && (int) c <= 96) || ((int) c >= 123 && (int) c <= 126)) {
					printf("[invalid query]\n");

					//text prints letters in the buffer up to the point the punctuation was first detected so its converted to an empty string
					strcpy(text, "\0");
					break;
				}

			// Converting to lower case here
			
				text[count]= tolower(c);
				count++;
		}
		
		printf("%s", text);
		printf(">");
		free(text);
			
	}

	return 0;
}
