#include <stdio.h>

int main(int argc, char *argv[]) {
	/*
	if(argc == 2) {
		printf("The argument supplied is %s\n", argv[1]);
	}

	else if(argc > 2) {
		printf("Too many arguments supplied.\n");
	}

	else {
		printf("One argument expected.\n");
	}
	*/

	char c;
	printf("Input an uppercase letter: \n");
	c = getchar();
	putchar(c + 32);
	putchar('\n');
	return 0;
}