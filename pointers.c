#include <stdio.h>

int var = 1;

void swap(int *point_1, int *point_2) {
	int temp;
	temp = *point_1;
	*point_1 = *point_2;
	*point_2 = temp;
}

void swap2(int p, int q) {
	int temp;
	temp = p;
	p = q;
	q = temp;
}

void exchange(int *q1, int *q2, int *q3) {
	void swap(int *pt1, int *pt2);
	if(*q1 < *q2) swap(q1, q2);
	if(*q1 < *q3) swap(q1, q3);
	if(*q2 < *q3) swap(q2, q3);
}

int main() {
	/*
	int num = 10;
	printf("Values of var is: %d\n", num);
	printf("Address of value is: %p\n", &num);
	*/
	/*
	int *p;
	int var = 10;

	p = &var;
	*/

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
	/*
	char ch = 'a';
	char *pr;
	pr = &ch;

	*pr = 'b';
	printf("Value of ch: %c\n", ch);
	printf("Value of ch: %c\n", *pr);
	*/

	/*
	int a = 100, b = 10;
	int *pointer_1, *pointer_2;
	pointer_1 = &a;
	pointer_2 = &b;
	printf("a = %d, b = %d\n", a, b);
	printf("%ld, %ld\n", pointer_1, pointer_2);
	printf("*pointer1=%d, *pointer_2=%d\n", *pointer_1, *pointer_2);
	*/
	/*
	int *p1, *p2, *p, a, b;
	printf("please enter two integer number: ");
	scanf("%d,%d", &a, &b);
	//printf("a=%d,b=%d\n", a, b);

	p1 = &a;
	p2 = &b;

	swap2(a, b);
	printf("a=%d,b=%d\n", a, b);

	if(a < b) {
		//p = p1;
		//p1 = p2;
		//p2 = p;
		swap(p1, p2);
	}

	printf("a=%d,b=%d\n", a, b);
	printf("max=%d,min=%d\n", *p1, *p2);
	*/

	int a,b,c,*p1,*p2,*p3;
	printf("please enter 3 integer number:");
	scanf("%d%d%d", &a, &b, &c);
	p1=&a;
	p2=&b;
	p3=&c;
	exchange(p1,p2,p3);
	printf("the order is: %d,%d,%d\n", a, b, c);

	return 0;
}