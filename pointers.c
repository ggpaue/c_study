#include <stdio.h>

int var = 1;
int main() {
	/*
	int num = 10;
	printf("Values of var is: %d\n", num);
	printf("Address of value is: %p\n", &num);
	*/

	int *p;
	int var = 10;

	p = &var;


	//printf("Value of var is: %d\n", var);
	//printf("Address of var is: %p\n", p);
	/*
	printf("Address of var is: %p\n", &var);
	printf("Address of var is: %p\n", p);

	printf("Address of pointer p is: %p\n", &p);


	printf("Value of pointer p is: %p\n", p);

	printf("Value of var is: %d\n", var);
	printf("Value of var is: %d\n", *p);
	printf("Value of var is: %d\n", *(&var));
	*/

	char ch = 'a';
	char *pr;
	pr = &ch;

	*pr = 'b';
	printf("Value of ch: %c\n", ch);
	printf("Value of ch: %c\n", *pr);

	return 0;
}