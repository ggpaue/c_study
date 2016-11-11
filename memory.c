#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	char name[100];
	char *description;

	strcpy(name, "Zara Ali");

	description = malloc(10 * sizeof(char));

	if(description == NULL) {
		fprintf(stderr, "Error - unable to allocate required memory \n");
	} else {
		strncpy(description, "fjsdafjlskajflsajflsajf", sizeof(description));
		printf("%d\n", strlen(description));
	}
	printf("Name = %s\n", name);
	printf("Description: %s\n", description);
	  
	/*
	description = realloc(description, 100 * sizeof(char));
	if(description == NULL) {
		fprintf(stderr, "Error - unable to allocate required memory \n");
	} else {
		strcat(description, "She is in class 10th");
	}

	printf("Name = %s\n", name);
	printf("Description: %s\n", description);
	
	free(description);
	*/
}