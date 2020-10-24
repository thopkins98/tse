/* test.c --- 
1;95;0c1;95;0c1;95;0c1;95;0c1;95;0c * 
 * 
 * Author: Agampodi I. Abeysekara
 * Created: Sat Oct 24 14:01:21 2020 (-0400)
 * Version: 
 * 
 * Description: 
 * 
 */


#include <stdlib.h>
#include <string.h>
#include <stdio.h>
int html(FILE *p, int len, char *s);

int main () {
	printf("hello");
	FILE *ptr= fopen("../pages2/1", "r");
	int d, p;
	char u[200]="";
	//	char n[200]="";
	
	fscanf(ptr, "%s", u);
	printf("%s", u);
	fscanf(ptr, "%d", &p);
	printf( "%d", p);
	fscanf(ptr, "%d", &d);
	printf("%d", d); 
	char *str = (char *) malloc(sizeof(char));
	//fscanf(ptr, "%s", str);
	//printf("%s", str);
	
	 html(ptr, d, str);
	//printf("%s", str);
	
	fclose(ptr);
	free(str);
	return 0;

}

int html(FILE *p, int len, char *s) {
	char c;
	char html[len+1];
	//s=html;
	int index=0;
	do {
		c= (char) fgetc(p);
		//if(c == ' ' || c == '\n' || c == '\0' || c == '\t') {
		//continue;
		//	}

		if (feof(p)) {
			break;
		}
		//strcat(html, &c);
		printf("%c", c);
		html[index]=c;
		index++;
	}
	while (1);

	
	//printf("%s", html);
	printf("%d", index);
	return 0;
}
